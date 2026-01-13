#pragma once
#ifndef BATCH_H
#define BATCH_H

#include "stack.hpp"
#include "AppManager.hpp"

extern "C" void __restore(uint64_t cx_addr);

namespace batch {

void run_next_app();

void print_app_info();

void init();

}

#endif
