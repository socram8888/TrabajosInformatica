
#include "select.h"

#include <unistd.h>
#include <fcntl.h>

#if defined(__linux__)
	int select_timed(int nfds, fd_set * readfds, fd_set * writefds, fd_set * errorfds, struct timeval * timeout) {
		return select(nfds, readfds, writefds, errorfds, timeout);
	}
#else

#include <string.h>
#include <sys/time.h>

	int select_timed(int nfds, fd_set * readfds, fd_set * writefds, fd_set * errorfds, struct timeval * timeout) {
		if (timeout == NULL) {
			return select(nfds, readfds, writefds, errorfds, timeout);
		}

		struct timeval start, finish;
		gettimeofday(&start, NULL);

		int ret = select(nfds, readfds, writefds, errorfds, timeout);
		if (ret == 0) {
			timerclear(timeout);
			return 0;
		}

		gettimeofday(&finish, NULL);
		timersub(&finish, &start, &finish);
		timersub(timeout, &finish, timeout);
		if (timeout->tv_sec < 0 || timeout->tv_usec < 0) {
			timerclear(timeout);
		}

		return ret;
	}
#endif

bool fd_blocking(int fd, bool blocking) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
		return false;
    }

	if (blocking) {
		flags &= ~O_NONBLOCK;
	} else {
		flags |= O_NONBLOCK;
	}

	return fcntl(fd, F_SETFL, flags) == 0;
}
