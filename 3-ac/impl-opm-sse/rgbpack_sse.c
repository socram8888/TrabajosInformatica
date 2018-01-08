// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "rgbpack.h"
#include <smmintrin.h>

void rgb_pack_sse(const uint8_t * red, const uint8_t * green, const uint8_t * blue, uint8_t * rgb, size_t pixels) {
	while (pixels >= 16) {
		__m128i r = _mm_load_si128((const __m128i *) red);
		__m128i g = _mm_load_si128((const __m128i *) green);
		__m128i b = _mm_load_si128((const __m128i *) blue);

		__m128i aR = _mm_shuffle_epi8(r, _mm_set_epi8( 5, -1, -1,  4, -1, -1,  3, -1, -1,  2, -1, -1,  1, -1, -1,  0));
		__m128i aG = _mm_shuffle_epi8(g, _mm_set_epi8(-1, -1,  4, -1, -1,  3, -1, -1,  2, -1, -1,  1, -1, -1,  0, -1));
		__m128i aB = _mm_shuffle_epi8(b, _mm_set_epi8(-1,  4, -1, -1,  3, -1, -1,  2, -1, -1,  1, -1, -1,  0, -1, -1));

		_mm_store_si128((__m128i *) (rgb + 0), _mm_or_si128(aR, _mm_or_si128(aG, aB)));

		__m128i bR = _mm_shuffle_epi8(r, _mm_set_epi8(-1, 10, -1, -1,  9, -1, -1,  8, -1, -1,  7, -1, -1,  6, -1, -1));
		__m128i bG = _mm_shuffle_epi8(g, _mm_set_epi8(10, -1, -1,  9, -1, -1,  8, -1, -1,  7, -1, -1,  6, -1, -1,  5));
		__m128i bB = _mm_shuffle_epi8(b, _mm_set_epi8(-1, -1,  9, -1, -1,  8, -1, -1,  7, -1, -1,  6, -1, -1,  5, -1));

		_mm_store_si128((__m128i *) (rgb + 16), _mm_or_si128(bR, _mm_or_si128(bG, bB)));

		__m128i cR = _mm_shuffle_epi8(r, _mm_set_epi8(-1, -1, 15, -1, -1, 14, -1, -1, 13, -1, -1, 12, -1, -1, 11, -1));
		__m128i cG = _mm_shuffle_epi8(g, _mm_set_epi8(-1, 15, -1, -1, 14, -1, -1, 13, -1, -1, 12, -1, -1, 11, -1, -1));
		__m128i cB = _mm_shuffle_epi8(b, _mm_set_epi8(15, -1, -1, 14, -1, -1, 13, -1, -1, 12, -1, -1, 11, -1, -1, 10));

		_mm_store_si128((__m128i *) (rgb + 32), _mm_or_si128(cR, _mm_or_si128(cG, cB)));

		red += 16;
		green += 16;
		blue += 16;
		rgb += 48;
		pixels -= 16;
	}

	rgb_pack_naive(red, green, blue, rgb, pixels);
}

void rgb_unpack_sse(const uint8_t * rgb, uint8_t * red, uint8_t * green, uint8_t * blue, size_t pixels) {
	while (pixels >= 16) {
		__m128i rgbA = _mm_load_si128(((const __m128i *) rgb) + 0);
		__m128i rgbB = _mm_load_si128(((const __m128i *) rgb) + 1);
		__m128i rgbC = _mm_load_si128(((const __m128i *) rgb) + 2);

		__m128i rA = _mm_shuffle_epi8(rgbA, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, 12,  9,  6,  3,  0));
		__m128i rB = _mm_shuffle_epi8(rgbB, _mm_set_epi8(-1, -1, -1, -1, -1, 14, 11,  8,  5,  2, -1, -1, -1, -1, -1, -1));
		__m128i rC = _mm_shuffle_epi8(rgbC, _mm_set_epi8(13, 10,  7,  4,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1));

		_mm_store_si128((__m128i *) red, _mm_or_si128(rA, _mm_or_si128(rB, rC)));

		__m128i gA = _mm_shuffle_epi8(rgbA, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 10,  7,  4,  1));
		__m128i gB = _mm_shuffle_epi8(rgbB, _mm_set_epi8(-1, -1, -1, -1, -1, 15, 12,  9,  6,  3,  0, -1, -1, -1, -1, -1));
		__m128i gC = _mm_shuffle_epi8(rgbC, _mm_set_epi8(14, 11,  8,  5,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1));

		_mm_store_si128((__m128i *) green, _mm_or_si128(gA, _mm_or_si128(gB, gC)));

		__m128i bA = _mm_shuffle_epi8(rgbA, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, 11,  8,  5,  2));
		__m128i bB = _mm_shuffle_epi8(rgbB, _mm_set_epi8(-1, -1, -1, -1, -1, -1, 13, 10,  7,  4,  1, -1, -1, -1, -1, -1));
		__m128i bC = _mm_shuffle_epi8(rgbC, _mm_set_epi8(15, 12,  9,  6,  3,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1));

		_mm_store_si128((__m128i *) blue, _mm_or_si128(bA, _mm_or_si128(bB, bC)));

		red += 16;
		green += 16;
		blue += 16;
		rgb += 48;
		pixels -= 16;
	}

	rgb_unpack_naive(rgb, red, green, blue, pixels);
}
