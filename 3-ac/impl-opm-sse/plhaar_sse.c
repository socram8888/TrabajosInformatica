// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#include "plhaar.h"
#include <smmintrin.h>

#define PLHAAR(valuesA, valuesB, lowpass, highpass) do { \
	__m128i s = _mm_cmplt_epi8(valuesA, _mm_setzero_si128()); \
	__m128i t = _mm_cmplt_epi8(valuesB, _mm_setzero_si128()); \
	\
	valuesA = _mm_sub_epi8(valuesA, s); \
	valuesB = _mm_sub_epi8(valuesB, t); \
	\
	__m128i ifA = _mm_sub_epi8(valuesA, valuesB); \
	__m128i aLessZero = _mm_xor_si128(s, _mm_cmplt_epi8(ifA, _mm_setzero_si128())); \
	__m128i ifB = _mm_blendv_epi8(valuesA, valuesB, aLessZero); \
	\
	__m128i ifNotB = _mm_add_epi8(valuesB, valuesA); \
	__m128i minusB = _mm_sub_epi8(_mm_setzero_si128(), valuesB); \
	__m128i bLessZero = _mm_xor_si128(t, _mm_cmplt_epi8(ifNotB, _mm_setzero_si128())); \
	__m128i ifNotA = _mm_blendv_epi8(minusB, valuesA, bLessZero); \
	\
	__m128i positive = _mm_xor_si128(s, t); \
	highpass = _mm_add_epi8(_mm_blendv_epi8(ifA, ifNotA, positive), s); \
	lowpass = _mm_add_epi8(_mm_blendv_epi8(ifB, ifNotB, positive), t); \
} while (0);

#define DEINTERLEAVE(a, b, x, y) do { \
	x = _mm_or_si128( \
		_mm_shuffle_epi8(a, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 14, 12, 10,  8,  6,  4,  2,  0)), \
		_mm_shuffle_epi8(b, _mm_set_epi8(14, 12, 10,  8,  6,  4,  2,  0, -1, -1, -1, -1, -1, -1, -1, -1)) \
	); \
	y = _mm_or_si128( \
		_mm_shuffle_epi8(a, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 15, 13, 11,  9,  7,  5,  3,  1)), \
		_mm_shuffle_epi8(b, _mm_set_epi8(15, 13, 11,  9,  7,  5,  3,  1, -1, -1, -1, -1, -1, -1, -1, -1)) \
	); \
} while (0);

#define CODE \
	for (size_t y = 0; y < height; y += 2) { \
		for (size_t x = 0; x < width; x += 32) { \
			__m128i upperLeft = _mm_load_si128((const __m128i *) (values + (y + 0) * width + x + 0)); \
			__m128i upperRight = _mm_load_si128((const __m128i *) (values + (y + 0) * width + x + 16)); \
			__m128i lowerLeft = _mm_load_si128((const __m128i *) (values + (y + 1) * width + x + 0)); \
			__m128i lowerRight = _mm_load_si128((const __m128i *) (values + (y + 1) * width + x + 16)); \
			\
			upperLeft = _mm_add_epi8(upperLeft, _mm_set1_epi8(-128)); \
			upperRight = _mm_add_epi8(upperRight, _mm_set1_epi8(-128)); \
			lowerLeft = _mm_add_epi8(lowerLeft, _mm_set1_epi8(-128)); \
			lowerRight = _mm_add_epi8(lowerRight, _mm_set1_epi8(-128)); \
			\
			__m128i upperEven, upperOdd, lowerEven, lowerOdd; \
			DEINTERLEAVE(upperLeft, upperRight, upperEven, upperOdd); \
			DEINTERLEAVE(lowerLeft, lowerRight, lowerEven, lowerOdd); \
			\
			__m128i upperL, upperH, lowerL, lowerH; \
			PLHAAR(upperEven, upperOdd, upperL, upperH); \
			PLHAAR(lowerEven, lowerOdd, lowerL, lowerH); \
			\
			__m128i hh, hl, lh, ll; \
			PLHAAR(upperL, lowerL, ll, lh); \
			PLHAAR(upperH, lowerH, hl, hh); \
			\
			ll = _mm_sub_epi8(ll, _mm_set1_epi8(-128)); \
			lh = _mm_sub_epi8(lh, _mm_set1_epi8(-128)); \
			hl = _mm_sub_epi8(hl, _mm_set1_epi8(-128)); \
			hh = _mm_sub_epi8(hh, _mm_set1_epi8(-128)); \
			\
			size_t offset = y / 2 * width / 2 + x / 2; \
			_mm_store_si128((__m128i *) (avg + offset), ll); \
			_mm_store_si128((__m128i *) (horizontal + offset), lh); \
			_mm_store_si128((__m128i *) (vertical + offset), hl); \
			_mm_store_si128((__m128i *) (diagonal + offset), hh); \
		} \
	}

void plhaar2d_transform_sse(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal) {
	CODE
}

void plhaar2d_transform_sse_mp(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal) {
	#pragma omp parallel for collapse(2) schedule(static)
	CODE
}
