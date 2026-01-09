#include "sbi.h"

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

void console_putchar(unsigned char c) {
  sbi_call(static_cast<uint64_t>(SBIType::SBI_CONSOLE_PUTCHAR), static_cast<uint64_t>(c), 0, 0);
}

void shutdown() {
  sbi_call(static_cast<uint64_t>(SBIType::SBI_SHUTDOWN), 0, 0, 0);
}
