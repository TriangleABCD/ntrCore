#pragma once
#ifndef SBI_H
#define SBI_H

#include <cstdint>

using std::uint64_t;

namespace sbi {

uint64_t sbi_call(uint64_t sbi_type, uint64_t arg0, uint64_t arg1, uint64_t arg2);

uint64_t sbi_call5(uint64_t ext, uint64_t fid, uint64_t arg0, uint64_t arg1, uint64_t arg2);

void console_putchar(unsigned char c);

void shutdown(bool failure);

}

#endif
