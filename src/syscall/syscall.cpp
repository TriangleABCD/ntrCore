#include "syscall.h"

namespace syscall {
  
int64_t syscall(uint64_t syscall_id, std::vector<uint64_t> args) {
  switch (syscall_id) {
    case SYS_WRITE: {
      return sys_write(args[0], static_cast<char*>(args[1]), args[2]);
    }
    case SYS_EXIT: {
      sys_exit(static_cast<int>(args[0]));
      return 0;
    }
  }
  return -1;
}

}
