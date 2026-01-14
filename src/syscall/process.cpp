#include "syscall.hpp"
#include "console.hpp"
#include "batch.hpp"

using console::printf;

namespace syscall {
  
void sys_exit(int exit_code) {
  INFO("Application exited with code %d", exit_code);
  batch::run_next_app();
}

}
