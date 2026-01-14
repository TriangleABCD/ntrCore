#pragma once
#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include "sbi.hpp"
#include "string.hpp"
#include "console.hpp"

using sbi::shutdown;
using console::printf;

#include <cstdint>
using std::uint64_t;

const int MAX_APP_NUM = 16;
const uint64_t APP_BASE_ADDRESS = 0x80400000;
const int APP_SIZE_LIMIT = 0x20000;

extern "C" {
  extern char _num_app;
}

struct AppManager {
  int num_app;
  int cur_app;
  uintptr_t app_start[MAX_APP_NUM + 1];

  void init() {
    uint64_t * num_app_ptr = reinterpret_cast<uint64_t*>(&_num_app);
    this->num_app = num_app_ptr[0];
    this->cur_app = 0;
    for (int i = 0; i <= this->num_app; i++) {
      this->app_start[i] = static_cast<uintptr_t>(num_app_ptr[i + 1]);
    }
  }

  void print_app_info() {
    INFO("num_app = %d", this->num_app);
    for (int i = 0; i < this->num_app; i++) {
      INFO("app_%d [0x%x, 0x%x)", i, this->app_start[i], this->app_start[i+1]);
    }
  }

  void load_app(int app_id) {
    if (app_id >= this->num_app) {
      INFO("All applications complete!");
      shutdown(false);
    }
    INFO("Loading app_%d", app_id);
    string::memset(
      reinterpret_cast<volatile unsigned char*>(APP_BASE_ADDRESS),
      0,
      APP_SIZE_LIMIT
    ); 

    int sz = (this->app_start[app_id + 1] - this->app_start[app_id]) * sizeof(int);

    const unsigned char * src = reinterpret_cast<const unsigned char*>(this->app_start[app_id]);
    volatile unsigned char * dst = reinterpret_cast<volatile unsigned char*>(APP_BASE_ADDRESS);
    string::memcpy(dst, src, sz);

    __asm__ volatile("fence.i" ::: "memory");
  }

  int get_current_app() {
    return this->cur_app;
  }

  void move_to_next_app() {
    this->cur_app += 1;
  }
};

inline AppManager appManager;

#endif
