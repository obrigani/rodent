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

#include <kernel/serial.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <stdio.h>

#ifdef __linux__
#error "Use a cross-compiler, dumbass"
#endif

#ifdef __WIN_32
#error "Use a cross-compiler, dumbass"
#warn "Use a real operating system, dumbass"
#endif

#ifndef __i386__
#error "You need a 32bit (i686 (i386)) cross-compiler, dumbass"
#endif

void kmain(void)
{
  init_serial();
  init_term();

  puts("rodent operating system \nCopyright (C) 2026  obrigani team");
  puts("This program comes with ABSOLUTELY NO WARRANTY;");
  puts("This is free software, and you are welcome to distribute it under the");
  puts("conditions of the GNU General Public License v3.0");
  puts("===============================================================================");
  
  init_gdt();
  init_idt();
  
  puts("Sall lox");
}
