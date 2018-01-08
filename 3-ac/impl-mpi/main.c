
#include "xmalloc.h"
#include "netpbm.h"
#include "plhaar.h"
#include "stopwatch.h"
#include <stdlib.h>
#include <getopt.h>
#include <mpi.h>

#define CLOCK CLOCK_MONOTONIC_RAW

static char * me = NULL;

void usage() {
	fprintf(stderr,
		"Usage: %s -i infile [-s] [-m]\n"
		"\n"
		"-i infile: input image. Must be a PGM or PPM image\n"
		"-n iters : Iterations to execute\n"
		"-s       : Use AVX extensions\n"
		"-t       : Display timings\n"
		, me
	);
}

int main(int argc, char ** argv) {
	me = argv[0];

	stopwatch_t initWatch;
	stopwatch_init(&initWatch, CLOCK);
	stopwatch_start(&initWatch);

	stopwatch_t loadWatch, saveWatch, processWatch, scatterWatch, gatherWatch;
	stopwatch_init(&loadWatch, CLOCK);
	stopwatch_init(&saveWatch, CLOCK);
	stopwatch_init(&processWatch, CLOCK);
	stopwatch_init(&scatterWatch, CLOCK);
	stopwatch_init(&gatherWatch, CLOCK);

	MPI_Init(NULL, NULL);

	int worldSize, worldRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &worldRank);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

	int iters = 0;
	bool usesse = false;
	bool timing = false;

	struct netpbm_image img;
	if (worldRank == 0) {
		int opt;
		char * infile = NULL;

		while ((opt = getopt(argc, argv, "i:n:st")) != -1) {
			switch (opt) {
				case 'i':
					infile = optarg;
					break;

				case 'n':
					iters = strtol(optarg, NULL, 0);
					break;

				case 's':
					usesse = true;
					break;

				case 't':
					timing = true;
					break;

				default:
					usage();
					return 2;
			}
		}

		if (infile == NULL || iters < 1) {
			usage();
			return 2;
		}

		stopwatch_switch(&initWatch, &loadWatch);

		if (netpbm_load(&img, infile) != NETPBM_OK) {
			printf("Could not load picture\n");
			return 1;
		}

		stopwatch_switch(&loadWatch, &initWatch);
	}

	MPI_Bcast(&img.width, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD); // Send width
	MPI_Bcast(&img.height, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD); // Send height
	MPI_Bcast(&iters, 1, MPI_INT, 0, MPI_COMM_WORLD); // Send number of iterations
	MPI_Bcast(&usesse, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD); // Send if we must use SSE

	size_t chunkSize = (img.height / worldSize) * img.width;
	uint8_t * chunk = xmalign(chunkSize, 16);
	uint8_t * chunkAvg = xmalign(chunkSize / 4, 16);
	uint8_t * chunkHorizontal = xmalign(chunkSize / 4, 16);
	uint8_t * chunkVertical = xmalign(chunkSize / 4, 16);
	uint8_t * chunkDiagonal = xmalign(chunkSize / 4, 16);

	stopwatch_switch(&initWatch, &scatterWatch);
	MPI_Scatter(img.data, chunkSize, MPI_BYTE, chunk, chunkSize, MPI_BYTE, 0, MPI_COMM_WORLD);
	stopwatch_switch(&scatterWatch, &processWatch);

	char path[256];
	for (int iter = 0; iter < iters; iter++) {
		size_t chunkLines = img.height / worldSize;
		size_t chunkSize = chunkLines * img.width;

		if (chunkLines % 2 == 1) {
			fprintf(stderr, "Cannot continue: height is not a multiple of two\n");
			return 1;
		}

		if (usesse) {
			plhaar2d_transform_sse(chunk, img.width, chunkLines, chunkAvg, chunkHorizontal, chunkVertical, chunkDiagonal);
		} else {
			plhaar2d_transform_naive(chunk, img.width, chunkLines, chunkAvg, chunkHorizontal, chunkVertical, chunkDiagonal);
		}

		img.width /= 2;
		img.height /= 2;

		if (worldRank == 0) {
			stopwatch_switch(&processWatch, &gatherWatch);
			// fprintf(stderr, "* Gather %016llX-%016llX %016llX-%016llX *\n", chunkHorizontal, chunkHorizontal + chunkSize - 1, img.data, img.data + chunkSize * worldSize - 1);
			MPI_Gather(chunkHorizontal, chunkSize / 4, MPI_BYTE, img.data, chunkSize / 4, MPI_BYTE, 0, MPI_COMM_WORLD);

			stopwatch_switch(&gatherWatch, &saveWatch);
			snprintf(path, sizeof(path), "%i.hor.pgm", iter);
			netpbm_save(&img, path);

			stopwatch_switch(&saveWatch, &gatherWatch);
			MPI_Gather(chunkVertical, chunkSize / 4, MPI_BYTE, img.data, chunkSize / 4, MPI_BYTE, 0, MPI_COMM_WORLD);

			stopwatch_switch(&gatherWatch, &saveWatch);
			snprintf(path, sizeof(path), "%i.ver.pgm", iter);
			netpbm_save(&img, path);

			stopwatch_switch(&saveWatch, &gatherWatch);
			MPI_Gather(chunkDiagonal, chunkSize / 4, MPI_BYTE, img.data, chunkSize / 4, MPI_BYTE, 0, MPI_COMM_WORLD);

			stopwatch_switch(&gatherWatch, &saveWatch);
			snprintf(path, sizeof(path), "%i.dia.pgm", iter);
			netpbm_save(&img, path);

			stopwatch_switch(&saveWatch, &processWatch);
		} else {
			stopwatch_switch(&processWatch, &gatherWatch);
			MPI_Gather(chunkHorizontal, chunkSize / 4, MPI_BYTE, NULL, 0, MPI_BYTE, 0, MPI_COMM_WORLD);
			MPI_Gather(chunkVertical, chunkSize / 4, MPI_BYTE, NULL, 0, MPI_BYTE, 0, MPI_COMM_WORLD);
			MPI_Gather(chunkDiagonal, chunkSize / 4, MPI_BYTE, NULL, 0, MPI_BYTE, 0, MPI_COMM_WORLD);
			stopwatch_switch(&gatherWatch, &processWatch);
		}

		uint8_t * x = chunk;
		chunk = chunkAvg;
		chunkAvg = x;

	}

	stopwatch_switch(&processWatch, &gatherWatch);
	MPI_Gather(chunk, chunkSize / 4, MPI_BYTE, img.data, chunkSize / 4, MPI_BYTE, 0, MPI_COMM_WORLD);

	stopwatch_switch(&gatherWatch, &saveWatch);
	snprintf(path, sizeof(path), "%i.avg.pgm", iters);
	netpbm_save(&img, path);

	stopwatch_stop(&saveWatch);

	if (worldRank == 0 && timing) {
		printf("Init:       %llu.%09li\n", (long long unsigned int) initWatch.elapsed.tv_sec, initWatch.elapsed.tv_nsec);
		printf("Load:       %llu.%09li\n", (long long unsigned int) loadWatch.elapsed.tv_sec, loadWatch.elapsed.tv_nsec);
		printf("Scatter:    %llu.%09li\n", (long long unsigned int) scatterWatch.elapsed.tv_sec, scatterWatch.elapsed.tv_nsec);
		printf("Process:    %llu.%09li\n", (long long unsigned int) processWatch.elapsed.tv_sec, processWatch.elapsed.tv_nsec);
		printf("Gather:     %llu.%09li\n", (long long unsigned int) gatherWatch.elapsed.tv_sec, gatherWatch.elapsed.tv_nsec);
		printf("Save:       %llu.%09li\n", (long long unsigned int) saveWatch.elapsed.tv_sec, saveWatch.elapsed.tv_nsec);
	}

	MPI_Finalize();

	return 0;
}
