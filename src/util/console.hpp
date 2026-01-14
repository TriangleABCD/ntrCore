#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include "sbi.hpp"
#include "string.hpp"
#include <cstdarg>

using sbi::console_putchar;
using string::utoa;
using string::itoa;

inline static void putchar(char c) {
  console_putchar((unsigned char)c);
}

namespace console {

inline void printf(const char * fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  while (*fmt) {
    if (*fmt != '%') {
      putchar(*fmt++);
      continue;
    }
    ++fmt;

    switch (*fmt) {
    case 'd': {
      int val = va_arg(ap, int);
      char tmp[12];
      unsigned int len = itoa(val, tmp);
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'u': {
      unsigned int val = va_arg(ap, unsigned int);
      char tmp[11];
      unsigned int len = utoa(val, tmp, 10);
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'x':
    case 'X': {
      unsigned int val = va_arg(ap, unsigned int);
      char tmp[9];
      unsigned int len = utoa(val, tmp, 16);
      if (*fmt == 'X') {
        for (unsigned int i = 0; i < len; ++i)
          if (tmp[i] >= 'a' && tmp[i] <= 'f') tmp[i] -= 32;
      }
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'c': {
      int val = va_arg(ap, int);
      putchar((char)val);
      break;
    }
    case 's': {
      const char *s = va_arg(ap, const char *);
      if (!s) s = "(null)";
      while (*s) putchar(*s++);
      break;
    }
    case '%':
      putchar('%');
      break;
    default:
      putchar('%');
      putchar(*fmt);
      break;
    }
    ++fmt;
  }

  va_end(ap);
}

}

#define CLR_RED     "\033[31m"
#define CLR_YELLOW  "\033[93m"
#define CLR_BLUE    "\033[94m"
#define CLR_GREEN   "\033[32m"
#define CLR_GRAY    "\033[90m"
#define CLR_RESET   "\033[0m"

#define ERROR(...)  (printf(CLR_RED   "[ERROR] " __VA_ARGS__), printf(CLR_RESET "\n"))
#define WARN(...)   (printf(CLR_YELLOW "[WARN ] " __VA_ARGS__), printf(CLR_RESET "\n"))
#define INFO(...)   (printf(CLR_BLUE  "[INFO ] " __VA_ARGS__), printf(CLR_RESET "\n"))
#define DEBUG(...)  (printf(CLR_GREEN "[DEBUG] " __VA_ARGS__), printf(CLR_RESET "\n"))
#define TRACE(...)  (printf(CLR_GRAY  "[TRACE] " __VA_ARGS__), printf(CLR_RESET "\n"))

#endif
