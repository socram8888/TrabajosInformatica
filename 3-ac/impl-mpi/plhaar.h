// Copyright (c) 2016 Marcos Vives Del Sol, Cristian Milá Pallás
// SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <stdint.h>
#include <string.h>

void plhaar2d_transform_naive(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal);
void plhaar2d_transform_sse(const uint8_t * values, size_t width, size_t height, uint8_t * avg, uint8_t * horizontal, uint8_t * vertical, uint8_t * diagonal);
