
#include "xmalloc.h"
#include "netpbm.h"
#include "rgbpack.h"
#include "plhaar.h"
#include "stopwatch.h"
#include <stdlib.h>
#include <getopt.h>

#define CLOCK CLOCK_MONOTONIC_RAW

static char * me = NULL;

void usage() {
	fprintf(stderr,
		"Usage: %s -i infile [-s] [-m]\n"
		"\n"
		"-i infile: input image. Must be a PGM or PPM image\n"
		"-n iters : Iterations to execute\n"
		"-s       : Use AVX extensions\n"
		"-m       : Use OpenMP\n"
		"-t       : Display timings\n"
		, me
	);
}

int main(int argc, char ** argv) {
	me = argv[0];

	int opt;
	char * infile = NULL;
	int iters = 0;
	bool usesse = false;
	bool useopenmp = false;
	bool timing = false;
	while ((opt = getopt(argc, argv, "i:n:smt")) != -1) {
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

			case 'm':
				useopenmp = true;
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

	stopwatch_t loadWatch, saveWatch, preprocessWatch, processWatch;
	stopwatch_init(&loadWatch, CLOCK);
	stopwatch_init(&saveWatch, CLOCK);
	stopwatch_init(&preprocessWatch, CLOCK);
	stopwatch_init(&processWatch, CLOCK);

	stopwatch_start(&loadWatch);

	struct netpbm_image img;
	if (netpbm_load(&img, infile) != NETPBM_OK) {
		printf("Could not load picture\n");
		return 1;
	}

	stopwatch_switch(&loadWatch, &preprocessWatch);

	size_t channelCount;
	uint8_t * channelData[3];
	switch (img.type) {
		case NETPBM_GRAY:
			channelCount = 1;
			channelData[0] = img.data;
			break;

		case NETPBM_RGB:
			channelCount = 3;
			channelData[0] = xmalign(img.width * img.height, 16);
			channelData[1] = xmalign(img.width * img.height, 16);
			channelData[2] = xmalign(img.width * img.height, 16);

			if (usesse) {
				rgb_unpack_sse(img.data, channelData[0], channelData[1], channelData[2], img.width * img.height);
			} else {
				rgb_unpack_naive(img.data, channelData[0], channelData[1], channelData[2], img.width * img.height);
			}

			break;

		default:
			fprintf(stderr, "Unsupported image format\n");
			return 3;
	}

	stopwatch_switch(&preprocessWatch, &processWatch);

	size_t dwtSize = (img.width / 2) * (img.height / 2);
	uint8_t * avg = xmalign(dwtSize, 16);
	uint8_t * horizontal = xmalign(dwtSize, 16);
	uint8_t * vertical = xmalign(dwtSize, 16);
	uint8_t * diagonal = xmalign(dwtSize, 16);

	for (int iter = 0; iter < iters; iter++) {
		for (size_t channel = 0; channel < channelCount; channel++) {

			if (usesse) {
				if (useopenmp) {
					plhaar2d_transform_sse_mp(channelData[channel], img.width, img.height, avg, horizontal, vertical, diagonal);
				} else {
					plhaar2d_transform_sse(channelData[channel], img.width, img.height, avg, horizontal, vertical, diagonal);
				}
			} else {
				if (useopenmp) {
					plhaar2d_transform_naive_mp(channelData[channel], img.width, img.height, avg, horizontal, vertical, diagonal);
				} else {
					plhaar2d_transform_naive(channelData[channel], img.width, img.height, avg, horizontal, vertical, diagonal);
				}
			}

			stopwatch_switch(&processWatch, &saveWatch);

			struct netpbm_image sub;
			char path[256];
			sub.type = NETPBM_GRAY;
			sub.width = img.width / 2;
			sub.height = img.height / 2;
			sub.maxval = 255;

			snprintf(path, sizeof(path), "%i.%i.avg.pgm", iter, channel);
			sub.data = avg;
			netpbm_save(&sub, path);

			snprintf(path, sizeof(path), "%i.%i.hor.pgm", iter, channel);
			sub.data = horizontal;
			netpbm_save(&sub, path);

			snprintf(path, sizeof(path), "%i.%i.ver.pgm", iter, channel);
			sub.data = vertical;
			netpbm_save(&sub, path);

			snprintf(path, sizeof(path), "%i.%i.dia.pgm", iter, channel);
			sub.data = diagonal;
			netpbm_save(&sub, path);

			stopwatch_switch(&saveWatch, &processWatch);

			uint8_t * x = avg;
			avg = channelData[channel];
			channelData[channel] = x;
		}

		img.width /= 2;
		img.height /= 2;
	}

	stopwatch_stop(&processWatch);

	if (timing) {
		printf("Load:       %llu.%09li\n", (long long unsigned int) loadWatch.elapsed.tv_sec, loadWatch.elapsed.tv_nsec);
		printf("Preprocess: %llu.%09li\n", (long long unsigned int) preprocessWatch.elapsed.tv_sec, preprocessWatch.elapsed.tv_nsec);
		printf("Process:    %llu.%09li\n", (long long unsigned int) processWatch.elapsed.tv_sec, processWatch.elapsed.tv_nsec);
		printf("Save:       %llu.%09li\n", (long long unsigned int) saveWatch.elapsed.tv_sec, saveWatch.elapsed.tv_nsec);
	}
}
