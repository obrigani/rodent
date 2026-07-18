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

#include <kernel/idt.h>
#include <stdbool.h>
#include <stdio.h>

__attribute__((aligned(0x10)))
static IDT_Entry idt[IDT_MAX_DESCRIPTORS];

static IDT_Ptr pidt;

// __attribute__((noreturn))
void exception_handler(void);
void exception_handler()
{
  __asm__ volatile ("cli; hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    IDT_Entry* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void init_idt(void);
void init_idt() {
    printf("[LOG] Initializing IDT... ");
    pidt.location = (uintptr_t)&idt[0];
    pidt.limit = (uint16_t)sizeof(IDT_Entry) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(pidt)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
    puts("OK");
}
