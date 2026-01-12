#include "syscall.hpp"
#include "console.hpp"

using console::printf;

namespace syscall {
  
int64_t sys_write(uint64_t fd, const char buf[], uint64_t len) {
  switch (fd) {
    case FD_STDOUT: {
      printf("%s", buf); 
      return len;
    }
  } 
  return -1;
}

}
