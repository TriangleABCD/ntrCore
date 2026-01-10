#include "console.h"

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
  console::printf("Hello, ntrCore!\n");
  while (true)
    ;
}

int x;
int y = 2;
