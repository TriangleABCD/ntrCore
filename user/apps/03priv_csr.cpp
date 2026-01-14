
int main() {
  __asm__ volatile("csrrw sp, sscratch, sp");
  return 0;
}
