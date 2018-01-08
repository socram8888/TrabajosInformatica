// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "plhaar.h"

inline void plhaar_int(uint8_t a, uint8_t b, uint8_t * l, uint8_t * h) {
	const uint8_t c = 128;
	const uint8_t s = (a < c), t = (b < c);

	a += s; b += t; 		// asymmetry: nudge origin to (+0,+0)
	if (s == t) { 			// A * B > 0?
		a -= b - c; 		// H = A - B
		if ((a < c) == s) { // |A| > |B|?
			b += a - c;		// L = A (replaces L = B)
		}
	} else {				// A * B < 0
		b += a - c;			// L = A + B
		if ((b < c) == t) {	// |B| > |A|?
			a -= b - c;		// H = -B (replaces H = A)
		}
	}
	a -= s; b -= t;			// asymmetry: restore origin
	*l = b; *h = a;			// store result
}

#define CODE \
	for (size_t y = 0; y < height; y += 2) { \
		for (size_t x = 0; x < width; x += 2) { \
			/* \
			 * Load four pixels into local thread-private variables. \
			 */ \
			uint8_t topLeft     = values[(x + 0) + (y + 0) * width]; \
			uint8_t topRight    = values[(x + 1) + (y + 0) * width]; \
			uint8_t bottomLeft  = values[(x + 0) + (y + 1) * width]; \
			uint8_t bottomRight = values[(x + 1) + (y + 1) * width]; \
			\
			/* \
			 * Compute PLHaar horizontally. \
			 * Top left with top right, and bottom left with bottom right. \
			 */ \
			uint8_t topLowpass, topHighpass, bottomLowpass, bottomHighpass; \
			plhaar_int(topLeft,    topRight,    &topLowpass,    &topHighpass); \
			plhaar_int(bottomLeft, bottomRight, &bottomLowpass, &bottomHighpass); \
			\
			/* \
			 * Now compute PLHaar vertically. \
			 * Lowpass from top row with lowpass from bottom row, and highpass from top row with highpass from bottom row. \
			 * The output is written to average, horizontal, vertical and diagonal. \
			 */ \
			size_t offset = y / 2 * width / 2 + x / 2; \
			plhaar_int(topLowpass,  bottomLowpass,  avg + offset, horizontal + offset); \
			plhaar_int(topHighpass, bottomHighpass, vertical + offset, diagonal + offset); \
		} \
	}

void plhaar2d_transform_naive(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal) {
	CODE
}

void plhaar2d_transform_naive_mp(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal) {
	#pragma omp parallel for \
	collapse(2) \
	schedule(static) \
	shared(values, width, height, avg, horizontal, vertical, diagonal)
	CODE
}
