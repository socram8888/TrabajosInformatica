// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "rgbpack.h"

void rgb_pack_naive(const uint8_t * r, const uint8_t * g, const uint8_t * b, uint8_t * rgb, size_t pixels) {
	for (size_t i = 0; i < pixels; i++) {
		rgb[i * 3 + 0] = r[i];
		rgb[i * 3 + 1] = g[i];
		rgb[i * 3 + 2] = b[i];
	}
}

void rgb_unpack_naive(const uint8_t * rgb, uint8_t * r, uint8_t * g, uint8_t * b, size_t pixels) {
	for (size_t i = 0; i < pixels; i++) {
		r[i] = rgb[i * 3 + 0];
		g[i] = rgb[i * 3 + 1];
		b[i] = rgb[i * 3 + 2];
	}
}
