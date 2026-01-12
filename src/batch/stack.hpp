#pragma once
#ifndef STACK_H
#define STACK_H

#include <cstdint>
using std::uint64_t;

const uint64_t USER_STACK_SIZE = 4096 * 2;
const uint64_t KERNEL_STACK_SIZE = 4096 * 2;

struct KernelStack {
  char data[KERNEL_STACK_SIZE];

};

struct UserStack {
  char data[USER_STACK_SIZE];
};

#endif
