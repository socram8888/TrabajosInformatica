
#ifndef HAVE_PACKET_H
#define HAVE_PACKET_H

#include <stdint.h>
#include <stdio.h>

#pragma pack(1)

#define PACKET_VERSION 2

#define PACKET_TYPE_LOGIN 0
typedef struct {
	uint32_t version;
} packet_login_t;

#define PACKET_TYPE_ACCEPT 1
typedef struct {
	uint8_t zone;
	uint16_t id;
	uint16_t neighbors;
	uint16_t ticks;
	uint32_t timeout;
	uint32_t txdelay;
} packet_accept_t;

#define PACKET_TYPE_ACCACK 2
typedef struct {
	uint8_t zone;
	uint16_t id;
} packet_accack_t;

#define PACKET_TYPE_START 3
typedef struct {
} packet_start_t;

#define PACKET_TYPE_POSITION 4
typedef struct {
	uint8_t zone;
	uint16_t id;
	uint16_t tick;
	uint32_t x;
	uint32_t y;
	uint32_t z;
} packet_position_t;

#define PACKET_TYPE_POSACK 5
typedef struct {
	uint8_t zone;
	uint16_t id;
	uint16_t tick;
	uint16_t neighbor;
	uint16_t neightick;
} packet_posack_t;

#define PACKET_TYPE_STATS 6
typedef struct {
	uint8_t zone;
	uint16_t id;
	uint16_t ticks;
	uint32_t posrcv;
	uint32_t ackrcv;
	uint32_t itmin;
	uint32_t itavg;
	uint32_t itmax;
} packet_stats_t;

#define PACKET_TYPE_STATACK 7
typedef struct {
} packet_statack_t;

typedef struct {
	uint8_t type;
	union {
		packet_login_t login;
		packet_accept_t accept;
		packet_accack_t accack;
		packet_start_t start;
		packet_position_t position;
		packet_posack_t posack;
		packet_stats_t stats;
		packet_statack_t statack;
	};
	uint8_t dummy;
} packet_t;

#pragma pack()

const char * packet_name(const packet_t * packet);
void packet_print(const packet_t * packet, FILE * out);

#endif
