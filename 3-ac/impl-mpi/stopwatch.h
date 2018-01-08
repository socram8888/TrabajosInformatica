// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <time.h>

typedef struct {
	struct timespec elapsed;
	struct timespec start;
	clockid_t clock;
} stopwatch_t;

void stopwatch_init(stopwatch_t * stopwatch, clockid_t clock);
void stopwatch_start(stopwatch_t * stopwatch);
void stopwatch_stop(stopwatch_t * stopwatch);
void stopwatch_switch(stopwatch_t * watchToStop, stopwatch_t * watchToStart);
