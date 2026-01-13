#pragma once
#ifndef STACK_H
#define STACK_H

#include "trapHandler.hpp"

#include <cstddef>
#include <cstdint>
using std::uint64_t;

const uint64_t USER_STACK_SIZE = 4096 * 2;
const uint64_t KERNEL_STACK_SIZE = 4096 * 2;

struct alignas(4096) KernelStack {
  unsigned char data[KERNEL_STACK_SIZE];
  
  uint64_t get_sp() {
    return reinterpret_cast<uint64_t>(this->data) + KERNEL_STACK_SIZE;
  }

  TrapContext* push_context(TrapContext&& cx) {
    TrapContext * cx_ptr = reinterpret_cast<TrapContext*>(this->get_sp() - sizeof(TrapContext));
    for (int i = 0; i < 32; i++) {
      cx_ptr->gp_regs[i] = cx.gp_regs[i];
    }
    cx_ptr->sstatus = cx.sstatus;
    cx_ptr->sepc = cx.sepc;
    return cx_ptr;
  }
};

struct  alignas(4096) UserStack {
  unsigned char data[USER_STACK_SIZE];

  uint64_t get_sp() {
    return reinterpret_cast<uint64_t>(this->data) + USER_STACK_SIZE;
  }
};

inline KernelStack kernelStack;
inline UserStack userStack;

#endif
