// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "netpbm.h"
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

int netpbm_load(struct netpbm_image * image, const char * file) {
	FILE * handle = fopen(file, "rb");
	if (!handle) {
		return NETPBM_CANNOT_OPEN;
	}

	int ret = netpbm_read(image, handle);

	fclose(handle);
	return ret;
}

int netpbm_read(struct netpbm_image * image, FILE * file) {
	int c;

	c = fgetc(file);
	if (c != 'p' && c != 'P') {
		return NETPBM_INVALID_MAGIC;
	}

	int type = fgetc(file);
	bool hasmaxval;
	switch (type) {
		case '4':
			type = NETPBM_MONO;
			hasmaxval = false;
			break;

		case '5':
			type = NETPBM_GRAY;
			hasmaxval = true;
			break;

		case '6':
			type = NETPBM_RGB;
			hasmaxval = true;
			break;

		default:
			return NETPBM_INVALID_MAGIC;
	}

	if (fgetc(file) != '\n') {
		return NETPBM_INVALID_MAGIC;
	}

	do {
		c = fgetc(file);
		if (c == -1) {
			return NETPBM_EOF;
		}

		if (c == '#') {
			int c2;
			do {
				c2 = fgetc(file);
				if (c2 == -1) {
					return NETPBM_EOF;
				}
			} while (c2 != '\n');
		}
	} while (c == '#' || isspace(c));
	ungetc(c, file);

	unsigned int width;
	unsigned int height;
	uint8_t maxval = 0;
	if (hasmaxval) {
		if (fscanf(file, "%u %u %hhu%*[\n]", &width, &height, &maxval) != 3) {
			return NETPBM_INVALID_SIZE;
		}
	} else {
		if (fscanf(file, "%u %u%*[\n]", &width, &height) != 2) {
			return NETPBM_INVALID_SIZE;
		}
	}

	size_t size;
	switch (type) {
		case NETPBM_MONO:
			size = (height * width + 7) / 8;
			break;

		case NETPBM_GRAY:
			size = height * width;
			break;

		case NETPBM_RGB:
			size = 3 * height * width;
			break;
	}

	uint8_t * data;
	if (posix_memalign((void **) &data, 64, size) != 0) {
		return NETPBM_MALLOC;
	}

	if (!fread(data, size, 1, file)) {
		free(data);
		return NETPBM_EOF;
	}

	image->type = type;
	image->width = width;
	image->height = height;
	image->maxval = maxval;
	image->data = data;

	return NETPBM_OK;
}

int netpbm_save(const struct netpbm_image * image, const char * file) {
	FILE * handle = fopen(file, "wb");
	if (!handle) {
		return NETPBM_CANNOT_OPEN;
	}

	int res = netpbm_write(image, handle);

	fclose(handle);
	return res;
}

int netpbm_write(const struct netpbm_image * image, FILE * file) {
	char type;
	size_t size;
	bool hasmaxval;
	switch (image->type) {
		case NETPBM_MONO:
			type = '4';
			size = (image->height * image->width + 7) / 8;
			hasmaxval = false;
			break;

		case NETPBM_GRAY:
			type = '5';
			size = image->height * image->width;
			hasmaxval = true;
			break;

		case NETPBM_RGB:
			type = '6';
			size = image->height * image->width * 3;
			hasmaxval = true;
			break;

		default:
			return NETPBM_INVALID_MAGIC;
	}

	if (hasmaxval) {
		if (fprintf(file, "P%c\n%u %u %hhu\n", type, image->width, image->height, image->maxval) < 0) {
			return NETPBM_EOF;
		}
	} else {
		if (fprintf(file, "P%c\n%u %u\n", type, image->width, image->height) < 0) {
			return NETPBM_EOF;
		}
	}

	if (!fwrite(image->data, size, 1, file)) {
		return NETPBM_EOF;
	}

	return NETPBM_OK;
}
