#include "sbi.hpp"


namespace sbi {

uint64_t sbi_call(uint64_t sbi_type, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
  uint64_t ret;
  __asm__ volatile (
    "mv x17, %[sbi_type]\n"
    "mv x10, %[arg0]\n"
    "mv x11, %[arg1]\n"
    "mv x12, %[arg2]\n"
    "ecall\n"
    "mv %[ret], x10"  
    : [ret] "=r" (ret)
    : [sbi_type] "r" (sbi_type), [arg0] "r" (arg0), [arg1] "r" (arg1), [arg2] "r" (arg2)
    : "memory"
  );
  return ret;
}

uint64_t sbi_call5(uint64_t ext, uint64_t fid,
                          uint64_t arg0, uint64_t arg1, uint64_t arg2) {
  uint64_t ret;
  register uint64_t a0 __asm__("a0") = arg0;
  register uint64_t a1 __asm__("a1") = arg1;
  register uint64_t a2 __asm__("a2") = arg2;
  register uint64_t a6 __asm__("a6") = fid;
  register uint64_t a7 __asm__("a7") = ext;
  __asm__ volatile ("ecall"
                    : "+r"(a0)
                    : "r"(a1), "r"(a2), "r"(a6), "r"(a7)
                    : "memory");
  return a0;
}

void console_putchar(unsigned char c) {
  uint64_t err = sbi_call(1, c, 0, 0);
  if (err) {
    sbi_call5(0, 0, 0, 0, 0);
  }
}

void shutdown(bool failure) {
  sbi_call5(0x53525354, 0, failure ? 1 : 0, 0, 0);
}

  
}
