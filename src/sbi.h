#pragma once
#include <cstdint>
#ifndef SBI_H
#define SBI_H

#include <cstdint>

using std::uint64_t;

enum struct SBIType : uint64_t {
  SBI_SET_TIMER = 0,
  SBI_CONSOLE_PUTCHAR = 1,
  SBI_CONSOLE_GETCHAR = 2,
  SBI_CLEAR_IPI = 3,
  SBI_SEND_IPI = 4,
  SBI_REMOTE_FENCE_I = 5,
  SBI_REMOTE_SFENCE_VMA = 6,
  SBI_REMOTE_SFENCE_VMA_ASID = 7,
  SBI_SHUTDOWN = 8
};

uint64_t sbi_call(uint64_t sbi_type, uint64_t arg0, uint64_t arg1, uint64_t arg2);

void console_putchar(unsigned char c);

void shutdown();

#endif
