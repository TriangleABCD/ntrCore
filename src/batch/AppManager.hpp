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

extern unsigned char _num_app[];

inline static uint64_t load_volatile(uint64_t const * p) {
  return *reinterpret_cast<volatile uint64_t const*>(p); 
}

struct AppManager {
  int num_app;
  int cur_app;
  int app_start[MAX_APP_NUM + 1];
  uint64_t num_addr;

  AppManager() {
    uint64_t const* num_app_ptr =
            reinterpret_cast<uint64_t const*>(
                reinterpret_cast<uintptr_t>(&_num_app));
    this->num_addr = reinterpret_cast<uint64_t>(num_app_ptr);
    this->num_app = load_volatile(num_app_ptr);
    this->cur_app = 0;
    for (int i = 0; i <= this->num_app; i++) {
      this->app_start[i] = load_volatile(num_app_ptr + i + 1);
    }
  }

  void print_app_info() {
    printf("[kernel] num_app = %d\n", this->num_app);
    for (int i = 0; i < this->num_app; i++) {
      printf("[kernel] app_%d [0x%x, 0x%x)\n", i, this->app_start[i], this->app_start[i+1]);
    }
  }

  void load_app(int app_id) {
    if (app_id >= this->num_app) {
      printf("[kernel] All applications complete!\n");
      shutdown(false);
    }
    printf("[kernel] Loading app_%d\n", app_id);
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
