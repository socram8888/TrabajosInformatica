
#include "packet.h"
#include <assert.h>

const char * packet_name(const packet_t * packet) {
	switch (packet->type) {
		case PACKET_TYPE_LOGIN:
			return "LOGIN";
		case PACKET_TYPE_ACCEPT:
			return "ACCEPT";
		case PACKET_TYPE_ACCACK:
			return "ACCACK";
		case PACKET_TYPE_START:
			return "START";
		case PACKET_TYPE_POSITION:
			return "POSITION";
		case PACKET_TYPE_POSACK:
			return "POSACK";
		case PACKET_TYPE_STATS:
			return "STATS";
		case PACKET_TYPE_STATACK:
			return "STATACK";
	}

	assert(0);
	return NULL;
}

void packet_print(const packet_t * packet, FILE * out) {
	switch (packet->type) {
		case PACKET_TYPE_LOGIN:
			fprintf(out,
				"LOGIN {\n"
				"	version   = %u\n"
				"}\n",
				packet->login.version
			);
			return;

		case PACKET_TYPE_ACCEPT:
			fprintf(out,
				"ACCEPT {\n"
				"	zone      = %u\n"
				"	id        = %u\n"
				"	neighbors = %u\n"
				"	ticks     = %u\n"
				"	timeout   = %u\n"
				"	txdelay   = %u\n"
				"}\n",
				packet->accept.zone,
				packet->accept.id,
				packet->accept.neighbors,
				packet->accept.ticks,
				packet->accept.timeout,
				packet->accept.txdelay
			);
			return;

		case PACKET_TYPE_ACCACK:
			fprintf(out,
				"ACCACK {\n"
				"	zone      = %u\n"
				"	id        = %u\n"
				"}\n",
				packet->accack.zone,
				packet->accack.id
			);
			return;

		case PACKET_TYPE_START:
			fprintf(out,
				"START {\n"
				"}\n"
			);
			return;

		case PACKET_TYPE_POSITION:
			fprintf(out,
				"POSITION {\n"
				"	zone      = %u\n"
				"	id        = %u\n"
				"	tick      = %u\n"
				"	x         = %u\n"
				"	y         = %u\n"
				"	z         = %u\n"
				"}\n",
				packet->position.zone,
				packet->position.id,
				packet->position.tick,
				packet->position.x,
				packet->position.y,
				packet->position.z
			);
			return;

		case PACKET_TYPE_POSACK:
			fprintf(out,
				"POSACK {\n"
				"	zone      = %u\n"
				"	id        = %u\n"
				"	tick      = %u\n"
				"	neighbor  = %u\n"
				"	neightick = %u\n"
				"}\n",
				packet->posack.zone,
				packet->posack.id,
				packet->posack.tick,
				packet->posack.neighbor,
				packet->posack.neightick
			);
			return;

		case PACKET_TYPE_STATS:
			fprintf(out,
				"STATS {\n"
				"	zone      = %u\n"
				"	id        = %u\n"
				"	ticks     = %u\n"
				"	posrcv    = %u\n"
				"	ackrcv    = %u\n"
				"	itmin     = %u\n"
				"	itavg     = %u\n"
				"	itmax     = %u\n"
				"}\n",
				packet->stats.zone,
				packet->stats.id,
				packet->stats.ticks,
				packet->stats.posrcv,
				packet->stats.ackrcv,
				packet->stats.itmin,
				packet->stats.itavg,
				packet->stats.itmax
			);
			return;

		case PACKET_TYPE_STATACK:
			fprintf(out,
				"STATACK {\n"
				"}\n"
			);
			return;
	}

	assert(0);
}
