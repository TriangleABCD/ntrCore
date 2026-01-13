#pragma once
#ifndef TRAP_HANDLER_H
#define TRAP_HANDLER_H

#include "TrapContext.hpp"

#include <cstdint>
using std::uint64_t;

namespace trap {

enum class TrapType : uint64_t {
    UserEnvCall        = 8,
    StoreFault         = 6,
    StorePageFault     = 15,
    IllegalInstruction = 2,
};
 
void init();

extern "C" TrapContext& trap_handler(TrapContext & ctx);

}

#endif
