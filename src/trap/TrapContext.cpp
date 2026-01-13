#include "TrapContext.hpp"

static uint64_t read_sstatus() {
  uint64_t val;
  __asm__ volatile("csrr %0, sstatus" : "=r"(val));
  return val;
}

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

