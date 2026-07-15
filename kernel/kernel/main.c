#include <kernel/tty.h>

void kmain(void)
{
  init_term();
  term_print("suka\n");
  term_print("suka");
  term_print("suka");
}
