#pragma once
#ifndef TRAP_HANDLER_H
#define TRAP_HANDLER_H

#include "TrapContext.hpp"

namespace trap {
 
void init();

extern "C" TrapContext trap_handler(TrapContext & ctx);

}

#endif
