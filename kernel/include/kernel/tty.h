/*
 * rodent operating system
 * Copyright (C) 2026  obrigani team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_ADDRESS 0xB8000

extern size_t term_row;
extern size_t term_col;
extern uint8_t term_color;
extern uint16_t* term_buffer;

void init_term(void);
void term_set_color(uint8_t color);
void term_write(const char* data, size_t size);
void term_print(const char* data);
