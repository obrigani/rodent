#include <kernel/serial.h>
#include <kernel/tty.h>
#include <stdio.h>

void kmain(void)
{
  init_serial();
  init_term();
  puts("rodent operating system \nCopyright (C) 2026  obrigani team");
  puts("This program comes with ABSOLUTELY NO WARRANTY;");
  puts("This is free software, and you are welcome to distribute it under the");
  puts("conditions of the GNU General Public License v3.0");
  puts("===============================================================================");
  puts("Sall lox");
}
