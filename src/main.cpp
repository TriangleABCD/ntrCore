#include "console.hpp"
#include "batch.hpp"
#include "trapHandler.hpp"

using console::printf;

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
  appManager.init();
  trap::init();
  batch::init();
  batch::run_next_app();
}
