
.globl syscall
.type syscall,%function
.align 4
syscall: 
  .cfi_sections .debug_frame
  .cfi_startproc

  l.ori r11, r3, 0
  l.ori r3, r4, 0
  l.ori r4, r5, 0
  l.ori r5, r6, 0
  l.ori r6, r7, 0
  l.ori r7, r8, 0
  l.lwz r8, 0(r1)
  l.sys 1
  l.nop

  /* if -4096 < ret < 0 holds, it's an error */
  l.sfgeui r11, 0xf001
  l.bf 0f
  l.nop

  l.jr r9
  l.nop

0: 
  l.j __syscall_error
  l.ori r3,r11,0

  .cfi_endproc
  .size syscall,.-syscall
