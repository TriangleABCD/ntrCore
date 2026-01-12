#include "syscall.hpp"

namespace syscall {
  
int64_t syscall(uint64_t syscall_id, uint64_t args[]) {
  switch (syscall_id) {
    case SYS_WRITE: {
      return sys_write(args[0], reinterpret_cast<char*>(args[1]), args[2]);
    }
    case SYS_EXIT: {
      sys_exit(static_cast<int>(args[0]));
      return 0;
    }
  }
  return -1;
}

}
