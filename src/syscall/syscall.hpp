#pragma once
#ifndef SYSCALL_H
#define SYSCALL_H

#include <cstdint>

using std::uint64_t;
using std::int64_t;

namespace syscall {
  
const uint64_t SYS_WRITE = 64;
const uint64_t SYS_EXIT = 93;

const uint64_t FD_STDOUT = 1;

int64_t syscall(uint64_t syscall_id, uint64_t args[]);

int64_t sys_write(uint64_t fd, const char buf[], uint64_t len);

void sys_exit(int exit_code);

}

#endif
