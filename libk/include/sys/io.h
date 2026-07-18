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

__attribute__((always_inline)) inline void outb(uint16_t port, uint8_t value)
{
  asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

__attribute__((always_inline)) inline void outw(uint16_t port, uint16_t value)
{
  asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

__attribute__((always_inline)) inline void outl(uint16_t port, uint16_t value)
{
  asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

__attribute__((always_inline)) inline uint8_t inb(uint16_t port)
{
  uint8_t value;
  asm volatile ("inb %1, %0"
    : "=a"(value)
    : "Nd"(port));
  return value;
}

__attribute__((always_inline)) inline uint16_t inw(uint16_t port)
{
  uint16_t value;
  asm volatile ("inw %1, %0"
    : "=a"(value)
    : "Nd"(port));
  return value;
}

__attribute__((always_inline)) inline uint32_t inl(uint16_t port)
{
  uint32_t value;
  asm volatile ("inl %1, %0"
    : "=a"(value)
    : "Nd"(port));
  return value;
}
