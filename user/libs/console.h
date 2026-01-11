#include "syscall.h"
#include <stdarg.h>

const uint64_t FD_STDOUT = 1;

inline unsigned int strlen(const char * s) {
  unsigned int len = 0;
  while (*s++) len++;
  return len;
}

inline void reverse(char * s, unsigned int len) {
  unsigned int i = 0, j = len - 1;
  while (i < j) {
    char t = s[i];
    s[i] = s[j];
    s[j] = t;
    i++;
    j--;
  }
}

inline unsigned int utoa(unsigned int val, char * buf, unsigned int base) {
  const char digit[] = "0123456789abcdef";
  unsigned int i = 0;
  if (val == 0) {
    buf[i++] = '0';
  } else {
    while (val) {
      buf[i++] = digit[val % base];
      val /= base;
    }
  }
  reverse(buf, i);
  return i;
}

inline unsigned int itoa(int val, char *buf) {
  unsigned int len;
  if (val < 0) {
    *buf++ = '-';
    len = 1 + utoa((unsigned int)-val, buf, 10);
  } else {
    len = utoa((unsigned int)val, buf, 10);
  }
  return len;
}

inline static void putchar(char c) {
  char buf[2] = {c};
  sys_write(FD_STDOUT, buf);
}

inline void printf(const char *fmt, ...) {
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
