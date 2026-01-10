#include "console.h"
#include "sbi.h"
#include "string.h"

static void putchar(char c) {
  sbi::console_putchar((unsigned char)c);
}

namespace console {

void printf(const char * fmt, ...) {
  char *ap = (char *)((char *)&fmt + sizeof(char *));

  while (*fmt) {
    if (*fmt != '%') {
      putchar(*fmt++);
      continue;
    }

    ++fmt;
    switch (*fmt) {
    case 'd': {
      int val = *(int *)ap; ap += sizeof(int);
      char tmp[12];
      unsigned int len = string::itoa(val, tmp);
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'u': {
      unsigned int val = *(unsigned int *)ap; ap += sizeof(unsigned int);
      char tmp[11];
      unsigned int len = string::utoa(val, tmp, 10);
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'x':
    case 'X': {
      unsigned int val = *(unsigned int *)ap; ap += sizeof(unsigned int);
      char tmp[9];
      unsigned int len = string::utoa(val, tmp, 16);
      if (*fmt == 'X') {
        for (unsigned int i = 0; i < len; ++i)
          if (tmp[i] >= 'a' && tmp[i] <= 'f')
            tmp[i] -= 32;
      }
      for (unsigned int i = 0; i < len; ++i) putchar(tmp[i]);
      break;
    }
    case 'c': {
      int val = *(int *)ap; ap += sizeof(int);
      putchar((char)val);
      break;
    }
    case 's': {
      const char *s = *(const char **)ap; ap += sizeof(char *);
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
}

}
