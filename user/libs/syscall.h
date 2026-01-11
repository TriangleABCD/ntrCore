#pragma once
#ifndef SYSCALL_H
#define SYSCALL_H

#include <cstdint>
using std::uint64_t;
using std::int64_t;

const uint64_t SYS_WRITE = 64;
const uint64_t SYS_EXIT = 93;

inline int64_t syscall(uint64_t syscall_id, uint64_t args[]) {
  int64_t ret;
  __asm__ volatile (
    "mv a0, %1\n\t"
    "mv a1, %2\n\t"
    "mv a2, %3\n\t"
    "mv a7, %4\n\t"
    "ecall\n\t"
    "mv %0,  a0"
    : "=r"(ret)
    : "r"(args[0]),
      "r"(args[1]),
      "r"(args[2]),
      "r"(syscall_id)
    : "a0", "a1", "a2", "a7", "memory"
  );
  return ret;
}

inline int64_t sys_write(uint64_t fd, const char buf[]) {
  uint64_t len = 0;
  auto p = buf;
  while(*p) {
    len++;
    p++;
  }
  uint64_t args[] = {fd, reinterpret_cast<uint64_t>(buf), len};
  return syscall(SYS_WRITE, args);
}

inline int64_t sys_exit(int exit_code) {
  uint64_t args[] = {static_cast<uint64_t>(exit_code), 0, 0};
  return syscall(SYS_EXIT, args);
}

#endif
