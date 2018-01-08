/*
 * Servidor para el proyecto de ARC
 * Version 1
 */

#define _BSD_SOURCE /* timeradd, timersub, timerclear, timerisset */
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "connection.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct{
	connection_t conexionConTaxi;
	bool hasAckdAccept;
	bool hasSentStats;
} gestion_taxi_t;


int server(unsigned short port, int demarcaciones, int taxPorDemarcacion, int iters, int timeout_millis, int txdelay_millis, bool debug) {
	connection_t conn;
	packet_t outgoing;
	packet_t * incoming;

	if (!connection_server(&conn, port)) {
		fprintf(stderr, "Unable to spawn server on port %u: ", port);
		connection_error(&conn, stderr);
		fprintf(stderr, "\n");
		return 1;
	}

	if (debug) {
		connection_debug(&conn, stderr);
	}

	gestion_taxi_t * taxis = calloc(demarcaciones * taxPorDemarcacion, sizeof(gestion_taxi_t));
	if (taxis == NULL) {
		fprintf(stderr, "Failed to allocate memory for taxi stats structure: %s\n", strerror(errno));
		return 1;
	}

	fprintf(stderr, "Waiting for clientes at port: [%d]\n", port);
	int connected = 0;
	int pendingAccAck = demarcaciones * taxPorDemarcacion;
	while (pendingAccAck > 0) {
		if (!connection_receive(&conn, &incoming, NULL)) { /* TODO: check how to safely implement a timeout here */
			fprintf(stderr, "Error receiving login packet: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			if (connection_dead(&conn)) {
				connection_close(&conn);
				free(taxis);
				return 1;
			}

			continue;
		}

		bool duplicate = false;
		int pos;
		switch (incoming->type) {
			case PACKET_TYPE_LOGIN:
				if (incoming->login.version != PACKET_VERSION) {
					fprintf(stderr, "Got LOGIN with version %08X but server version is %08X\n", incoming->login.version, PACKET_VERSION);
					connection_discard(&conn);
					continue;
				}
				connection_accept(&conn);

				for (pos = 0; pos < connected; pos++) {
					if (connection_cmp(&taxis[pos].conexionConTaxi, &conn)) {
						duplicate = true;
						fprintf(stderr, "Got duplicated login packet from taxi %d-%d. Re-sending acknowledgement\n", pos / taxPorDemarcacion, pos % taxPorDemarcacion);
						break;
					}
				}

				if (!duplicate) {
					if (connected == taxPorDemarcacion * demarcaciones) {
						fprintf(stderr, "Received new LOGIN but all taxis have been already registered\n");
						continue;
					}

					fprintf(stderr, "Registered new taxi %d-%d\n", connected / taxPorDemarcacion, connected % taxPorDemarcacion);
					memcpy(&taxis[connected].conexionConTaxi, &conn, sizeof(conn));
					connected++;
				}

				outgoing.type = PACKET_TYPE_ACCEPT;
				outgoing.accept.zone = pos / taxPorDemarcacion;
				outgoing.accept.id = pos % taxPorDemarcacion;
				outgoing.accept.neighbors = taxPorDemarcacion - 1;
				outgoing.accept.ticks = iters;
				outgoing.accept.timeout = timeout_millis;
				outgoing.accept.txdelay = txdelay_millis;
				if (!connection_send(&conn, &outgoing)) {
					fprintf(stderr, "Error replying to login packet: ");
					connection_error(&conn, stderr);
					fprintf(stderr, "\n");
					connection_close(&conn);
					free(taxis);
					return 1;
				}

				break;

			case PACKET_TYPE_ACCACK:
				if (incoming->accack.zone >= demarcaciones || incoming->accack.id >= taxPorDemarcacion) {
					fprintf(stderr, "Received illegal accept acknowledgement from taxi %u-%u\n", incoming->accack.zone, incoming->accack.id);
					connection_discard(&conn);
					continue;
				}
				connection_accept(&conn);

				gestion_taxi_t * taxi = &taxis[incoming->accack.zone * taxPorDemarcacion + incoming->accack.id];
				if (!taxi->hasAckdAccept) {
					taxi->hasAckdAccept = true;
					pendingAccAck--;
				}
				break;

			default:
				connection_discard(&conn);
				fprintf(stderr, "Unexpected packet %s during login phase. Discarding.\n", packet_name(incoming));
				continue;
		}
	}

	outgoing.type = PACKET_TYPE_START;
	for (int pos = 0; pos < demarcaciones * taxPorDemarcacion; pos++) {
		if (!connection_send(&taxis[pos].conexionConTaxi, &outgoing)) {
			fprintf(stderr, "Error sending start packet: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");
			connection_close(&conn);
			free(taxis);
			return 1;
		}
	}

	int statsRcv = 0;
	struct timeval defaulttimeout = { (timeout_millis * 2) / 1000, ((timeout_millis * 2) % 1000) * 1000 };
	struct timeval timeout = defaulttimeout;
	while (statsRcv < demarcaciones * taxPorDemarcacion) {
		if (!connection_receive(&conn, &incoming, NULL)) {
			fprintf(stderr, "Error receiving packet in main loop: ");
			connection_error(&conn, stderr);
			fprintf(stderr, "\n");

			if (conn.err == CONNERR_TIMEOUT) {
				break;
			}

			if (connection_dead(&conn)) {
				connection_close(&conn);
				free(taxis);
				return 1;
			}

			continue;
		}

		gestion_taxi_t * taxi;
		switch (incoming->type) {
			case PACKET_TYPE_ACCACK:
				outgoing.type = PACKET_TYPE_START;
				if (!connection_send(&conn, &outgoing)) {
					fprintf(stderr, "Failed to send start packet in main loop: ");
					connection_error(&conn, stderr);
					fprintf(stderr, "\n");
					connection_close(&conn);
					return 1;
				}
				timeout = defaulttimeout;
				break;

			case PACKET_TYPE_POSITION:
				if (incoming->position.zone > demarcaciones || incoming->position.id > taxPorDemarcacion) {
					fprintf(stderr, "Received position from illegal taxi %u-%u\n", outgoing.position.zone, outgoing.position.id);
					connection_discard(&conn);
					continue;
				}

				for (int neighbor = 0; neighbor < taxPorDemarcacion; neighbor++) {
					if (neighbor == incoming->position.id) {
						continue;
					}

					if (!connection_send(&taxis[incoming->position.zone * taxPorDemarcacion + neighbor].conexionConTaxi, incoming)) {
						fprintf(stderr, "Error forwarding position packet: ");
						connection_error(&taxis[incoming->position.zone * taxPorDemarcacion + neighbor].conexionConTaxi, stderr);
						fprintf(stderr, "\n");
						connection_close(&conn);
						free(taxis);
						return 1;
					}
				}
				timeout = defaulttimeout;
				connection_accept(&conn);
				break;

			case PACKET_TYPE_POSACK:
				if (incoming->posack.zone > demarcaciones || incoming->posack.id > taxPorDemarcacion) {
					fprintf(stderr, "Received acknowledgement from illegal taxi %u-%u\n", incoming->posack.zone, incoming->posack.id);
					break;
				}

				if (incoming->posack.neighbor > taxPorDemarcacion) {
					fprintf(stderr, "Received acknowledgement from %u-%u targeting out-of-bounds taxi %u-%u\n", incoming->posack.zone, incoming->posack.id, incoming->posack.zone, incoming->posack.neighbor);
					break;
				}

				taxi = &taxis[incoming->posack.zone * taxPorDemarcacion + incoming->posack.neighbor];
				if (!connection_send(&taxi->conexionConTaxi, incoming)) {
					fprintf(stderr, "Error forwarding acknowledgement packet: ");
					connection_error(&taxi->conexionConTaxi, stderr);
					fprintf(stderr, "\n");
					connection_close(&conn);
					free(taxis);
					return 1;
				}
				timeout = defaulttimeout;
				connection_accept(&conn);
				break;

			case PACKET_TYPE_STATS:
				taxi = &taxis[incoming->stats.zone * taxPorDemarcacion + incoming->stats.id];
				if (!taxi->hasSentStats) {
					printf("%u, %u, %u, %u, %u, %u, %u, %u\n",
						incoming->stats.zone,
						incoming->stats.id,
						incoming->stats.ticks,
						incoming->stats.posrcv,
						incoming->stats.ackrcv,
						incoming->stats.itmin,
						incoming->stats.itavg,
						incoming->stats.itmax
					);
					taxi->hasSentStats = true;
					statsRcv++;
				}

				outgoing.type = PACKET_TYPE_STATACK;
				if (!connection_send(&taxi->conexionConTaxi, &outgoing)) {
					fprintf(stderr, "Error sending stats acknowledgement packet: ");
					connection_error(&taxi->conexionConTaxi, stderr);
					fprintf(stderr, "\n");
					connection_close(&conn);
					free(taxis);
					return 1;
				}

				timeout = defaulttimeout;
				connection_accept(&conn);
				break;

			default:
				fprintf(stderr, "Unexpected packet %s during main loop\n", packet_name(incoming));
				connection_discard(&conn);
				continue;
		}
	}

	// TODO: Interpretar estadísticas
	return 0;
}

int main(int argc, char ** argv) {
	if (argc != 8) {
		fprintf(stderr, "Usage: %s port[1-65535] iters zones[>0] clients_per_zone[1-65535] timeout_millis txdelay_millis debug\n", argv[0]);
		return 1;
	}

	int port = strtol(argv[1], NULL, 0);
	if (port < 1 || port > 65535) {
		fprintf(stderr, "Invalid port\n");
		return 1;
	}

	int iters = strtol(argv[2], NULL, 0);
	if (iters < 1) {
		fprintf(stderr, "Invalid iteration count\n");
		return 1;
	}

	int zones = strtol(argv[3], NULL, 0);
	if (zones < 1) {
		fprintf(stderr, "Invalid zone count\n");
		return 1;
	}

	int clients_per_zone = strtol(argv[4], NULL, 0);
	if (clients_per_zone < 1 || clients_per_zone > 65535) {
		fprintf(stderr, "Invalid amount of clients per zone\n");
		return 1;
	}

	int timeout_millis = strtol(argv[5], NULL, 0);
	if (timeout_millis < 1) {
		fprintf(stderr, "Invalid millisecond timeout\n");
		return 1;
	}

	int delay_millis = strtol(argv[6], NULL, 0);
	if (delay_millis < 1) {
		fprintf(stderr, "Invalid millisecond delay\n");
		return 1;
	}

	bool debug = strcmp(argv[7], "yes") == 0 || strcmp(argv[7], "true") == 0;

	return server(port, zones, clients_per_zone, iters, timeout_millis, delay_millis, debug);
}
