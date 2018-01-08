// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define NETPBM_MONO 1
#define NETPBM_GRAY 2
#define NETPBM_RGB 3

#define NETPBM_OK 0
#define NETPBM_EOF 1
#define NETPBM_INVALID_MAGIC 2
#define NETPBM_INVALID_SIZE 3
#define NETPBM_MALLOC 4
#define NETPBM_CANNOT_OPEN 5

struct netpbm_image {
	int type;
	unsigned int width;
	unsigned int height;
	uint8_t maxval;
	uint8_t * data;
};

int netpbm_load(struct netpbm_image * image, const char * file);
int netpbm_read(struct netpbm_image * image, FILE * file);

int netpbm_save(const struct netpbm_image * image, const char * file);
int netpbm_write(const struct netpbm_image * image, FILE * file);
