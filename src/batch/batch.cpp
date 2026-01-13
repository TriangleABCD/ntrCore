#include "batch.hpp"

namespace batch {

void run_next_app() {
  auto cur_app = appManager.get_current_app();
  appManager.load_app(cur_app);
  appManager.move_to_next_app();

  auto ctx_ptr = kernelStack.push_context(
    TrapContext::app_init_context(APP_BASE_ADDRESS, userStack.get_sp())
  );

  __restore(reinterpret_cast<uint64_t>(ctx_ptr));
}

void print_app_info() {
  appManager.print_app_info();
}

void init() {
  print_app_info();
}

}
