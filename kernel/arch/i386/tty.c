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

#include "vga.h"

#include <kernel/tty.h>
#include <stdint.h>
#include <string.h>

size_t term_row;
size_t term_col;
uint8_t term_color;
uint16_t* term_buffer = (uint16_t*)VGA_ADDRESS;

void init_term(void)
{
  term_row = 0;
  term_col = 0;
  term_color = vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);

  for(size_t y = 0; y < VGA_HEIGHT; y++) {
    for(size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t i = y * VGA_WIDTH + x;
      term_buffer[i] = vga_entry(' ', term_color);
    }
  }
}

void term_set_color(uint8_t color)
{
  term_color = color;
}

void term_put_entry_at(char c, uint8_t color, size_t x, size_t y)
{
  const size_t i = y * VGA_WIDTH + x;
  term_buffer[i] = vga_entry((unsigned char)c, color);
}

void term_put_char(char c)
{
  switch(c) {
    case '\n':
      term_row++;
      term_col = 0;
      return;
    default: break;
  }
  term_put_entry_at(c, term_color, term_col, term_row);
  if(term_col++ == VGA_WIDTH) {
    term_col = 0;
    if(term_row++ == VGA_HEIGHT)
      term_row = 0;
  }
}

void term_write(const char* data, size_t size)
{
  for(size_t i = 0; i < size; i++)
    term_put_char(data[i]);
}

void term_print(const char* data)
{
  term_write(data, strlen(data));
}

