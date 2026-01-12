#pragma once
#ifndef TRAP_CONTEXT_H
#define TRAP_CONTEXT_H

#include <cstdint>
using std::uint64_t;

inline static uint64_t read_sstatus() {
  uint64_t val;
  __asm__ volatile("csrr %0, sstatus" : "=r"(val));
  return val;
}

struct TrapContext {
  uint64_t gp_regs[32];
  uint64_t sstatus;
  uint64_t sepc;

  void set_sp(uint64_t sp) {
    this->gp_regs[2] = sp;
  }

  static TrapContext app_init_context(uint64_t entry, uint64_t sp);
};

TrapContext TrapContext::app_init_context(uint64_t entry, uint64_t sp) {
  uint64_t sstatus = read_sstatus();
  sstatus &= ~(1ULL << 8); // set SPP as user
  TrapContext ctx;
  for (int i = 0; i < 32; i++) {
    ctx.gp_regs[i] = 0;
  }
  ctx.sstatus = sstatus;
  ctx.sepc = entry;
  ctx.set_sp(sp);
  return ctx;
}

#endif
