#include "console.h"

int main() {

  auto fib = [](auto&& self, int n) -> int {
    if (0 == n) return 0;
    if (1 == n) return 1;
    return self(self, n-1) + self(self, n-2);
  };

  int r = fib(fib, 10);
  printf("[app] fib(10) = %d\n", r);
}
