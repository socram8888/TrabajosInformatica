// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <string.h>
#include <stdlib.h>

inline void * xmalloc(size_t size) {
	void * buf = malloc(size);
	if (buf == NULL && size > 0) {
		exit(1);
	}
	return buf;
}

inline void * xmalign(size_t size, size_t align) {
	void * buf = NULL;
	int ret = posix_memalign(&buf, align, size);
	if (ret != 0 && size > 0) {
		exit(1);
	}
	return buf;
}
