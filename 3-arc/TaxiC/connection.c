
#include "connection.h"
#include "select.h"

#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

// +1 to account for extra type byte
static const size_t PACKET_SIZES[] = {
	1 + sizeof(packet_login_t),
	1 + sizeof(packet_accept_t),
	1 + sizeof(packet_accack_t),
	1 + sizeof(packet_start_t),
	1 + sizeof(packet_position_t),
	1 + sizeof(packet_posack_t),
	1 + sizeof(packet_stats_t),
	1 + sizeof(packet_statack_t)
};

bool connection_server(connection_t * conn, unsigned short port) {
	struct sockaddr_in localaddr;
	memset(&localaddr, 0, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = INADDR_ANY;
	localaddr.sin_port = htons(port);

	conn->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (conn->fd < 0) {
		conn->err = CONNERR_SOCKET;
		conn->errdata = errno;
		return false;
	}

	if (bind(conn->fd, (struct sockaddr *) &localaddr, sizeof(localaddr)) < 0) {
		conn->err = CONNERR_BIND;
		conn->errdata = errno;
		close(conn->fd);
		return false;
	}

	if (!fd_blocking(conn->fd, false)) {
		conn->err = CONNERR_NONBLOCK;
		conn->errdata = errno;
		return false;
	}

	conn->list_head = NULL;
	conn->list_cur = NULL;
	conn->list_prev = NULL;

	conn->err = CONNERR_NONE;
	conn->debugfile = NULL;

	return true;
}

bool connection_client(connection_t * conn, in_addr_t server, unsigned short port) {
	struct sockaddr_in localaddr;
	memset(&localaddr, 0, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = INADDR_ANY;
	localaddr.sin_port = 0;

	conn->fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (conn->fd < 0) {
		conn->err = CONNERR_SOCKET;
		conn->errdata = errno;
		return false;
	}

	if (bind(conn->fd, (struct sockaddr *) &localaddr, sizeof(localaddr)) < 0) {
		conn->err = CONNERR_BIND;
		conn->errdata = errno;
		close(conn->fd);
		return false;
	}

	if (!fd_blocking(conn->fd, false)) {
		conn->err = CONNERR_NONBLOCK;
		conn->errdata = errno;
		return false;
	}

	conn->list_head = NULL;
	conn->list_cur = NULL;
	conn->list_prev = NULL;

	conn->err = CONNERR_NONE;
	conn->debugfile = NULL;

	memset(&conn->partner_addr, 0, sizeof(conn->partner_addr));
	conn->partner_addr.sin_family = AF_INET;
	conn->partner_addr.sin_addr.s_addr = server;
	conn->partner_addr.sin_port = htons(port);

	return true;
}

bool connection_send(connection_t * conn, const packet_t * packet) {
	// Check that packet ID does not reference an out-of-bounds element in the array
	assert(packet->type < ARRAY_LENGTH(PACKET_SIZES));

	// Extra check to ensure we've sent all the bytes for the packet
	if (sendto(conn->fd, packet, PACKET_SIZES[packet->type], 0, (struct sockaddr *) &conn->partner_addr, sizeof(conn->partner_addr)) != PACKET_SIZES[packet->type]) {
		conn->err = CONNERR_SEND;
		conn->errdata = errno;
		return false;
	}

	if (conn->debugfile != NULL) {
		fprintf(conn->debugfile, ">>>>>>>> SENT >>>>>>>>\n");
		packet_print(packet, conn->debugfile);
		fprintf(conn->debugfile, ">>>>>>>>>>>>>>>>>>>>>>\n");
	}

	return true;
}

bool connection_receive(connection_t * conn, packet_t ** packet, struct timeval * timeout) {
	if (conn->list_cur != NULL) {
		*packet = &conn->list_cur->packet;
		return true;
	}

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(conn->fd, &fds);

	switch (select_timed(conn->fd + 1, &fds, NULL, NULL, timeout)) {
		case -1:
			conn->err = CONNERR_SELECT;
			conn->errdata = errno;
			return false;

		case 0:
			conn->err = CONNERR_TIMEOUT;
			return false;
	}

	socklen_t addrlen = sizeof(conn->partner_addr);
	ssize_t packetsize = recvfrom(conn->fd, &conn->last_packet, sizeof(packet_t), 0, (struct sockaddr *) &conn->partner_addr, &addrlen);
	if (packetsize < 1) {
		conn->err = CONNERR_RECV;
		conn->errdata = errno;
		return false;
	}

	if (conn->last_packet.type >= ARRAY_LENGTH(PACKET_SIZES)) {
		conn->err = CONNERR_PACKID;
		return false;
	}

	if (packetsize != PACKET_SIZES[conn->last_packet.type]) {
		conn->err = CONNERR_PACKLEN;
		conn->errdata = packetsize;
		return false;
	}

	if (conn->debugfile != NULL) {
		fprintf(conn->debugfile, "<<<<<< RECEIVED <<<<<<\n");
		packet_print(&conn->last_packet, conn->debugfile);
		fprintf(conn->debugfile, "<<<<<<<<<<<<<<<<<<<<<<\n");
	}

	*packet = &conn->last_packet;

	return true;
}

void connection_discard(connection_t * conn) {
	if (conn->list_cur != NULL) {
		struct packet_list * newCur = conn->list_cur->next;
		free(conn->list_cur);
		conn->list_cur = newCur;

		if (conn->list_prev == NULL) {
			conn->list_head = newCur;
		} else {
			conn->list_prev->next = newCur;
		}
	}
}

void connection_revise(connection_t * conn) {
	conn->list_cur = conn->list_head;
	conn->list_prev = NULL;
}

void connection_accept(connection_t * conn) {
	connection_discard(conn);
	connection_revise(conn);
}

void connection_save(connection_t * conn) {
	if (conn->list_cur == NULL) {
		struct packet_list * node = malloc(sizeof(struct packet_list));
		memcpy(&node->packet, &conn->last_packet, sizeof(packet_t));
		node->next = conn->list_head;
		conn->list_head = node;
	} else {
		conn->list_prev = conn->list_cur;
		conn->list_cur = conn->list_cur->next;
	}
}

void connection_close(connection_t * conn) {
	close(conn->fd);

	struct packet_list * cur = conn->list_head;
	while (cur != NULL) {
		struct packet_list * next = cur->next;
		free(cur);
		cur = next;
	}
}

void connection_error(connection_t * conn, FILE * f) {
	switch (conn->err) {
		case CONNERR_NONE:
			fprintf(f, "success");
			return;

		case CONNERR_SOCKET:
			fprintf(f, "socket() failed (%s)", strerror(conn->errdata));
			return;

		case CONNERR_BIND:
			fprintf(f, "bind() failed (%s)", strerror(conn->errdata));
			return;

		case CONNERR_NONBLOCK:
			fprintf(f, "fd_blocking() failed (%s)", strerror(conn->errdata));
			return;

		case CONNERR_RECV:
			fprintf(f, "recvfrom() failed (%s)", strerror(conn->errdata));
			return;

		case CONNERR_SELECT:
			fprintf(f, "select() failed (%s)", strerror(conn->errdata));
			return;

		case CONNERR_TIMEOUT:
			fprintf(f, "recvfrom() timed out");
			return;

		case CONNERR_SEND:
			fprintf(f, "sendto() failed (%s)", strerror(conn->errdata));
			return;
	
		case CONNERR_PACKID:
			fprintf(f, "invalid packet with ID 0x%02X", conn->last_packet.type);
			return;

		case CONNERR_PACKLEN:
			fprintf(f, "received packet %s with %d bytes instead of %d", packet_name(&conn->last_packet), conn->errdata, (int) PACKET_SIZES[conn->last_packet.type]);
			return;
	}

	assert(0);
}

bool connection_dead(connection_t * conn) {
	switch (conn->err) {
		case CONNERR_SOCKET:
		case CONNERR_BIND:
		case CONNERR_RECV:
		case CONNERR_SELECT:
		case CONNERR_SEND:
			return true;

		case CONNERR_NONE:
		case CONNERR_TIMEOUT:
		case CONNERR_PACKID:
		case CONNERR_PACKLEN:
			return false;
	}

	assert(0);
	return true;
}

void connection_debug(connection_t * conn, FILE * debugfile) {
	conn->debugfile = debugfile;
}

bool connection_cmp(connection_t * a, connection_t * b) {
	return memcmp(&a->partner_addr, &b->partner_addr, sizeof(a->partner_addr)) == 0 ? true : false;
}
