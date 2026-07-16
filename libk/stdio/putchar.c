#include <stdio.h>

#ifdef __is_libk
#include <kernel/tty.h>
#endif

int putchar(int ic)
{
#ifdef __is_libk
  char c = (char)ic;
  term_write(&c, sizeof(c));
#else
  // TODO: implement the rest 
#endif
  return ic;
}
