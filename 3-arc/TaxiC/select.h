
#ifndef HAVE_SELECT_TIMED_H
#define HAVE_SELECT_TIMED_H

#define _BSD_SOURCE /* timer_sub, timer_clear */

#include <sys/select.h>
#include <stdbool.h>

int select_timed(int nfds, fd_set * readfds, fd_set * writefds, fd_set * errorfds, struct timeval * timeout);
bool fd_blocking(int fd, bool blocking);

#endif
