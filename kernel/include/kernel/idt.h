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

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
  uint16_t isr_low;
  uint16_t kernel_cs;
  uint8_t  reserved;
  uint8_t  attributes;
  uint16_t isr_high;
} __attribute__((packed)) IDT_Entry;

typedef struct {
  uint16_t limit;
  uint32_t location;
} __attribute__((packed)) IDT_Ptr;

void exception_handler(void);
void init_idt(void);
