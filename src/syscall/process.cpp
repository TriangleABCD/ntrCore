#include "syscall.hpp"
#include "console.hpp"
#include "batch.hpp"

using console::printf;

namespace syscall {
  
void sys_exit(int exit_code) {
  printf("[kernel] Application exited with code %d\n", exit_code);
  batch::run_next_app();
}

}
