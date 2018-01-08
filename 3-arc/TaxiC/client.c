
#define _BSD_SOURCE /* timeradd, timersub, timerclear, timerisset */
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "connection.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct client_config {
	in_addr_t serverip;
	unsigned short port;
	int verbose;
};

#define DEBUG_INFO 1
#define DEBUG_VARS 2
#define DEBUG_STREAM 3

void * client(void * voidcfg) {
	struct client_config * cfg = (struct client_config *) voidcfg;

	connection_t conn;
	packet_t outgoing;
	packet_t * incoming;

	if (!connection_client(&conn, cfg->serverip, cfg->port)) {
		fprintf(stderr, "Failed to create connection: ");
		connection_error(&conn, stderr);
		fprintf(stderr, "\n");
		connection_close(&conn);
		return NULL;
	}

	if (cfg->verbose >= DEBUG_STREAM) {
		connection_debug(&conn, stderr);
	}

	while (1) {
		outgoing.type = PACKET_TYPE_LOGIN;
		outgoing.login.version = PACKET_VERSION;
		if (!connection_send(&conn, &outgoing)) {
			fprintf(stderr, "Failed to send login: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");
			connection_close(&conn);
			return NULL;
		}

		struct timeval tv = { 3, 0 };
		if (!connection_receive(&conn, &incoming, &tv)) {
			fprintf(stderr, "Error receiving acceptation: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			if (connection_dead(&conn)) {
				connection_close(&conn);
				return NULL;
			}
			continue;
		}

		if (incoming->type != PACKET_TYPE_ACCEPT) {
			if (cfg->verbose >= DEBUG_INFO) {
				fprintf(stderr, "Received unexpected packet (%s). Saving.\n", packet_name(incoming));
			}
			connection_save(&conn);
			continue;
		}

		break;
	}

	uint8_t zone = incoming->accept.zone;
	uint16_t ownId = incoming->accept.id;
	uint16_t neighbors = incoming->accept.neighbors;
	uint16_t ticks = incoming->accept.ticks;
	uint32_t timeout_millis = incoming->accept.timeout;
	uint32_t send_delay = incoming->accept.txdelay;
	unsigned int randomseed = time(NULL) + zone * 65536 + ownId;
	connection_accept(&conn);

	if (cfg->verbose >= DEBUG_INFO) {
		fprintf(stderr, "[%02d-%04d] Registered successfully. Got %d neighbors.\n", zone, ownId, neighbors);
	}

	while (1) {
		outgoing.type = PACKET_TYPE_ACCACK;
		outgoing.accack.zone = zone;
		outgoing.accack.id = ownId;
		if (!connection_send(&conn, &outgoing)) {
			fprintf(stderr, "Error sending accept acknowledgement: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");
			connection_close(&conn);
			return NULL;
		}

		struct timeval tv = { 3, 0 };
		if (!connection_receive(&conn, &incoming, &tv)) {
			fprintf(stderr, "Error receiving start: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			if (connection_dead(&conn)) {
				connection_close(&conn);
				return NULL;
			}
			continue;
		}

		if (incoming->type != PACKET_TYPE_START) {
			if (cfg->verbose >= DEBUG_INFO) {
				fprintf(stderr, "[%02d-%04d] Received unexpected packet (%s). Saving.\n", zone, ownId, packet_name(incoming));
			}
			connection_save(&conn);
			continue;
		}
		connection_accept(&conn);

		break;
	}

	if (cfg->verbose >= DEBUG_INFO) {
		fprintf(stderr, "[%02d-%04d] Starting simulation. Timeout: %u\n", zone, ownId, timeout_millis);
	}

	uint32_t totalPos = 0;
	uint32_t totalAck = 0;
	uint32_t itmin = ~0;
	uint32_t itmax = 0;
	uint64_t itsum = 0;

	struct timeval timeoutval = {
		.tv_sec = timeout_millis / 1000,
		.tv_usec = (timeout_millis % 1000) * 1000
	};

	struct timeval * curtimeout;
	struct timeval sendtime;
	struct timeval receivetime;
	struct timeval activitytime = { 0 };
	int tickAck;

#	define PHASE_NEWTICK 0
#	define PHASE_SEND 1
#	define PHASE_RECEIVE 2
	int phase = PHASE_NEWTICK;
	int tick = -1;

	while (1) {
		if (phase == PHASE_NEWTICK) {
			if (tick == ticks) {
				break;
			}

			if (timerisset(&activitytime)) {
				uint32_t itermicros = timeout_millis * 1000 - activitytime.tv_sec * 1000000 - activitytime.tv_usec;
				if (cfg->verbose >= DEBUG_INFO) {
					fprintf(stderr, "[%02u-%04u] Iteration %u time: %ums\n", zone, ownId, tick, itermicros);
				}
				itmin = min(itermicros, itmin);
				itmax = max(itermicros, itmax);
				itsum += itermicros;
				timerclear(&activitytime);
			}

			tick++;
			receivetime = timeoutval;
			connection_revise(&conn);
			if (cfg->verbose >= DEBUG_INFO) {
				fprintf(stderr, "[%02u-%04u] Entering iteration %u\n", zone, ownId, tick);
			}

			if (tick == ticks) {
				curtimeout = &receivetime;
				phase = PHASE_RECEIVE;
			} else {
				unsigned int random_send_delay = rand_r(&randomseed) % send_delay;
				if (cfg->verbose >= DEBUG_VARS) {
					fprintf(stderr, "[%02u-%04u] TX delay: %ums\n", zone, ownId, random_send_delay);
				}
				sendtime.tv_sec = random_send_delay / 1000;
				sendtime.tv_usec = (random_send_delay % 1000) * 1000;
				curtimeout = &sendtime;
				phase = PHASE_SEND;
			}
		}

		if (cfg->verbose >= DEBUG_VARS) {
			fprintf(stderr, "[%02u-%04u] RX enter %u.%06u\n", zone, ownId, (unsigned int) curtimeout->tv_sec, (unsigned int) curtimeout->tv_usec);
		}
		if (!connection_receive(&conn, &incoming, curtimeout)) {
			if (conn.err != CONNERR_TIMEOUT) {
				fprintf(stderr, "[%02d-%04d] Error receiving packet in main loop: ", zone, ownId);
				connection_error(&conn, stderr);
				fprintf(stderr, "\n");

				if (connection_dead(&conn)) {
					connection_close(&conn);
					return NULL;
				}

				continue;
			}

			switch (phase) {
				case PHASE_SEND:
					if (cfg->verbose >= DEBUG_INFO) {
						fprintf(stderr, "[%02u-%04u] Start RECEIVE\n", zone, ownId);
					}
					outgoing.type = PACKET_TYPE_POSITION;
					outgoing.position.zone = zone;
					outgoing.position.id = ownId;
					outgoing.position.tick = tick;
					outgoing.position.x = 0xEFBEADDE;
					outgoing.position.y = 0xBEBAFECA;
					outgoing.position.z = 0x0DD001C0;

					if (!connection_send(&conn, &outgoing)) {
						fprintf(stderr, "[%02d-%04d] Could not send own position: ", zone, ownId);
						connection_error(&conn, stderr);
						fprintf(stderr, "\n");
						connection_close(&conn);
						return NULL;
					}

					phase = PHASE_RECEIVE;
					tickAck = 0;
					curtimeout = &receivetime;
					break;

				case PHASE_RECEIVE:
					if (cfg->verbose >= DEBUG_INFO) {
						fprintf(stderr, "[%02u-%04u] Finished RECEIVE\n", zone, ownId);
					}
					phase = PHASE_NEWTICK;
					break;
			}

			continue;
		}
		if (cfg->verbose >= DEBUG_VARS) {
			fprintf(stderr, "[%02u-%04u] RX leave %u.%06u\n", zone, ownId, (unsigned int) curtimeout->tv_sec, (unsigned int) curtimeout->tv_usec);
		}

		switch (incoming->type) {
			case PACKET_TYPE_POSITION:
				if (incoming->position.tick > tick) {
					if (cfg->verbose >= DEBUG_VARS) {
						fprintf(stderr, "[%02d-%04d] Got position from tick %u but I am in tick %u. Saving.\n", zone, ownId, incoming->position.tick, tick);
					}
					connection_save(&conn);
					break;
				}

				outgoing.type = PACKET_TYPE_POSACK;
				outgoing.posack.zone = zone;
				outgoing.posack.id = ownId;
				outgoing.posack.tick = incoming->position.tick;
				outgoing.posack.neighbor = incoming->position.id;
				outgoing.posack.neightick = tick;

				if (!connection_send(&conn, &outgoing)) {
					fprintf(stderr, "[%02d-%04d] Could not send position acknowledgement: ", zone, ownId);
					connection_error(&conn, stderr);
					fprintf(stderr, "\n");

					connection_close(&conn);
					return NULL;
				}

				connection_accept(&conn);
				totalPos++;
				break;

			case PACKET_TYPE_POSACK:
				if (incoming->posack.tick != tick || incoming->posack.tick == ticks) {
					fprintf(stderr, "[%02d-%04d] Got acknowledgement from tick %u but I am in tick %u. Discarding.\n", zone, ownId, incoming->posack.tick, tick);
					connection_discard(&conn);
					break;
				}

				if (phase != PHASE_RECEIVE) {
					fprintf(stderr, "[%02d-%04d] Got acknowledgement while not in receive phase.\n", zone, ownId);
					connection_discard(&conn);
					break;
				}

				connection_accept(&conn);
				activitytime = receivetime;
				totalAck++;
				tickAck++;

				if (tickAck == neighbors) {
					phase = PHASE_NEWTICK;
				}
				break;

			default:
				fprintf(stderr, "[%02d-%04d] Received unexpected packet (%s). Discarding.\n", zone, ownId, packet_name(incoming));
				connection_discard(&conn);
		}
	}

	outgoing.type = PACKET_TYPE_STATS;
	outgoing.stats.zone = zone;
	outgoing.stats.id = ownId;
	outgoing.stats.ticks = ticks;
	outgoing.stats.posrcv = totalPos;
	outgoing.stats.ackrcv = totalAck;
	outgoing.stats.itmin = itmin;
	outgoing.stats.itavg = (ticks != 0 ? itsum / ticks : ~0);
	outgoing.stats.itmax = itmax;

	while (1) {
		if (!connection_send(&conn, &outgoing)) {
			fprintf(stderr, "[%02d-%04d] Could not send stats: ", zone, ownId);
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			connection_close(&conn);
			return NULL;
		}

		struct timeval tv = { 3, 0 };
		if (!connection_receive(&conn, &incoming, &tv)) {
			fprintf(stderr, "Error receiving stats acknowledgement: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			if (connection_dead(&conn)) {
				connection_close(&conn);
				return NULL;
			}
			continue;
		}

		if (incoming->type != PACKET_TYPE_STATACK) {
			if (cfg->verbose >= DEBUG_INFO) {
				fprintf(stderr, "[%02d-%04d] Received unexpected packet (%s). Saving.\n", zone, ownId, packet_name(incoming));
			}
			connection_discard(&conn);
			continue;
		}
		connection_accept(&conn);

		break;
	}

	connection_close(&conn);
	return NULL;
}

int main(int argc, char ** argv) {
	struct client_config cfg;

	if (argc != 5) {
		fprintf(stderr, "Usage: %s clientCount server port verbosity\n", argv[0]);
		return 1;
	}

	int count = strtol(argv[1], NULL, 0);
	if (count < 1) {
		fprintf(stderr, "Invalid client count\n");
		return 1;
	}

	if (inet_pton(AF_INET, argv[2], &cfg.serverip) == 0) {
		fprintf(stderr, "Invalid server address\n");
		return 1;
	}

	cfg.port = strtol(argv[3], NULL, 0);
	if (cfg.port < 1 || cfg.port > 65535) {
		fprintf(stderr, "Invalid port\n");
		return 1;
	}

	cfg.verbose = strtol(argv[4], NULL, 0);

	char addrtxt[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &cfg.serverip, addrtxt, sizeof(addrtxt));
	printf("Launching %d clients, targetting server %s:%d, verbosity %d.", count, addrtxt, cfg.port, cfg.verbose);

	pthread_t * threads = (pthread_t *) calloc(count, sizeof(pthread_t));
	if (threads == NULL) {
		perror("calloc");
		return 1;
	}

	for (int i = 0; i < count; i++) {
		int ret = pthread_create(threads + i, NULL, client, &cfg);
		if (ret) {
			fprintf(stderr, "Error pthread_create: %d\n", ret);
			break;
		}
	}

	for (int i = 0; i < count; i++) {
		printf("Wait %d: ", i);
		pthread_join(threads[i], NULL);
		printf("done\n");
	}

	free(threads);
	return 0;
}
