#include "syscall.h"
#include "console.h"

namespace syscall {
  
void sys_exit(int exit_code) {
  console::printf("[kernel] Application exited with code %d\n", exit_code); 
}

}
