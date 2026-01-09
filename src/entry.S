  .section .text.entry
  .global _start
_start:
  la sp, boot_stack_top
  call main

  .section .bss.stack
  .globl boot_stack_bottom
boot_stack_bottom:
  .space 4096 * 16
  .globl boot_stack_top
boot_stack_top:
