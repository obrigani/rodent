#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void)
{
#ifdef __is_libk
  printf("Kernel panic: abort()\n");
    asm volatile("hlt");
#else
  printf("abort\n");
#endif
  for(;;) {}
  __builtin_unreachable();
}
