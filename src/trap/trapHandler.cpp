#include "trapHandler.hpp"
#include "syscall.hpp"
#include "batch.hpp"

using batch::run_next_app;

static uint64_t read_scause() {
  uint64_t v;
  __asm__ volatile("csrr %0, scause" : "=r"(v));
  return v;
}

static uint64_t read_stval() {
  uint64_t v;
  __asm__ volatile("csrr %0, stval" : "=r"(v));
  return v;
}

static void write_stvec(uint64_t v) {
  __asm__ volatile("csrw stvec, %0" :: "r"(v));
}

static bool is_exception(uint64_t scause) { return (scause >> 63) == 0; }

static uint64_t exception_code(uint64_t scause) { return scause & 0xFF; }


extern "C" void __alltraps();

namespace trap {

void init() {
  uint64_t addr = reinterpret_cast<uint64_t>(__alltraps);
  write_stvec(addr);
}

TrapContext& trap_handler(TrapContext & ctx) {
  const uint64_t scause = read_scause();
  const uint64_t stval = read_stval();

  if (!is_exception(scause))
    goto unsupported;

  switch (static_cast<TrapType>(exception_code(scause))) {
    case TrapType::UserEnvCall: {
      ctx.sepc += 4;
      uint64_t args[] = {ctx.gp_regs[10], ctx.gp_regs[11], ctx.gp_regs[12]}; 
      uint64_t ret = syscall::syscall(ctx.gp_regs[17], args);
      ctx.gp_regs[10] = ret;
      break;
    }
    case TrapType::StoreFault:
    case TrapType::StorePageFault:
      printf("[kernel] PageFault in application, kernel killed it.");
      run_next_app();
      break;

    case TrapType::IllegalInstruction:
      printf("[kernel] IllegalInstruction in application, kernel killed it.");
      run_next_app();
      break;

    default:
    unsupported:
      printf("Unsupported trap code=%lu, stval=%#lx\n", exception_code(scause), stval);
      __asm__ volatile("unimp");
  }
  return ctx;
}

}

