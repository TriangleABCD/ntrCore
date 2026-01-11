#include "syscall.h"
#include "console.h"

int64_t write(uint64_t fd, const char buf[]) {
  return sys_write(fd, buf);
}

int64_t exit(int exit_code) {
  return sys_exit(exit_code);
}

extern unsigned char sbss[];
extern unsigned char ebss[];
void clear_bss() {
  unsigned char * start = sbss; 
  unsigned char * end = ebss; 

  while (start < end) {
    *start++ = 0;
  }
}

int main();
extern "C" __attribute__((section(".text.entry")))
void _start() {
  clear_bss(); 
  exit(main());
  printf("Here is unreachable !\n");
}

