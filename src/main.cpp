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

  printf("[DEBUG] %d\n", appManager.num_app);
  printf("[DEBUG] 0x%x\n", appManager.num_addr);
  for (int i = 0; i <= appManager.num_app; i++) {
    printf("[DEBUG] app start %d: 0x%x\n", i, appManager.app_start[i]);
  }

  trap::init();
  batch::init();
  batch::run_next_app();
}
