
#ifndef HAVE_CONNECTION_H
#define HAVE_CONNECTION_H

#include "packet.h"
#include <sys/time.h>
#include <netinet/in.h>
#include <stdbool.h>

enum {
	CONNERR_NONE,
	CONNERR_SOCKET,
	CONNERR_BIND,
	CONNERR_NONBLOCK,
	CONNERR_RECV,
	CONNERR_SELECT,
	CONNERR_TIMEOUT,
	CONNERR_SEND,
	CONNERR_PACKID,
	CONNERR_PACKLEN
};

struct packet_list;
struct packet_list {
	packet_t packet;
	struct packet_list * next;
};

typedef struct {
	int fd;
	struct sockaddr_in partner_addr;

	packet_t last_packet;
	struct packet_list * list_head;
	struct packet_list * list_cur;
	struct packet_list * list_prev;

	int err;
	int errdata;

	FILE * debugfile;
} connection_t;

bool connection_server(connection_t * conn, unsigned short port);
bool connection_client(connection_t * conn, in_addr_t server, unsigned short port);

bool connection_send(connection_t * conn, const packet_t * packet);

bool connection_receive(connection_t * conn, packet_t ** packet, struct timeval * timeout);
void connection_revise(connection_t * conn);
void connection_discard(connection_t * conn);
void connection_accept(connection_t * conn);
void connection_save(connection_t * conn);

void connection_close(connection_t * conn);

void connection_error(connection_t * conn, FILE * f);
bool connection_dead(connection_t * conn);

void connection_debug(connection_t * conn, FILE * file);

bool connection_cmp(connection_t * a, connection_t * b);

#endif
