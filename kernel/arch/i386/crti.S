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

.section .init
.global _init
.type _init, @function
_init:
	push %ebp
	movl %esp, %ebp
	# gcc will nicely put the contents of crtbegin.o's .init section here. 

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %ebp
	movl %esp, %ebp
	# gcc will nicely put the contents of crtbegin.o's .fini section here. 

