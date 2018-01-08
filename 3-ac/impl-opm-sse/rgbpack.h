// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdint.h>
#include <string.h>

void rgb_pack_naive(const uint8_t * red, const uint8_t * green, const uint8_t * blue, uint8_t * rgb, size_t pixels);
void rgb_pack_sse(const uint8_t * red, const uint8_t * green, const uint8_t * blue, uint8_t * rgb, size_t pixels);

void rgb_unpack_naive(const uint8_t * rgb, uint8_t * r, uint8_t * g, uint8_t * b, size_t pixels);
void rgb_unpack_sse(const uint8_t * rgb, uint8_t * r, uint8_t * g, uint8_t * b, size_t pixels);
