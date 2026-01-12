#include "console.hpp"
#include "sbi.hpp"

using console::printf;
using sbi::shutdown;
using sbi::console_putchar;

extern unsigned char sbss[];
extern unsigned char ebss[];

void clear_bss() {
  unsigned char * start = sbss;
  unsigned char * end = ebss;

  while (start < end) {
    *start++ = 0;
  }
}

extern "C" void main() {
  clear_bss();
  printf("[kernel] Hello, ntrCore!\n");
  while (true)
    ;
}
