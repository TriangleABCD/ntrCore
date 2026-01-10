#pragma once
#ifndef STRING_H
#define STRING_H

namespace string {

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

}

#endif
