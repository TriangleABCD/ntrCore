#pragma once
#ifndef TRAP_CONTEXT_H
#define TRAP_CONTEXT_H

#include <cstdint>
using std::uint64_t;

struct TrapContext {
  uint64_t gp_regs[32];
  uint64_t sstatus;
  uint64_t sepc;

  void set_sp(uint64_t sp) {
    this->gp_regs[2] = sp;
  }

  static TrapContext app_init_context(uint64_t entry, uint64_t sp);
};


#endif
