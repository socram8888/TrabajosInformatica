// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "stopwatch.h"
#include <string.h>

void stopwatch_init(stopwatch_t * stopwatch, clockid_t clock) {
	memset(&stopwatch->elapsed, 0, sizeof(stopwatch->elapsed));
	stopwatch->clock = clock;
}

void stopwatch_start(stopwatch_t * stopwatch) {
	clock_gettime(stopwatch->clock, &stopwatch->start);
}

void stopwatch_stop(stopwatch_t * stopwatch) {
	struct timespec now;
	clock_gettime(stopwatch->clock, &now);

	now.tv_sec -= stopwatch->start.tv_sec;
	now.tv_nsec -= stopwatch->start.tv_nsec;
	if (now.tv_nsec < 0) {
		now.tv_nsec += 1000000000;
		now.tv_sec--;
	}

	stopwatch->elapsed.tv_sec += now.tv_sec;
	stopwatch->elapsed.tv_nsec += now.tv_nsec;
	if (stopwatch->elapsed.tv_nsec > 1000000000) {
		stopwatch->elapsed.tv_nsec -= 1000000000;
		stopwatch->elapsed.tv_sec++;
	}
}

void stopwatch_switch(stopwatch_t * watchToStop, stopwatch_t * watchToStart) {
	// TODO: use a single clock_gettime call?
	stopwatch_stop(watchToStop);
	stopwatch_start(watchToStart);
}
