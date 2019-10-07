/* syscall, OpenRISC version.
   Copyright (C) 2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

	.globl	syscall
	.type	syscall, %function
	.align	4
syscall: 
	.cfi_startproc

	/* Copy the syscall number to r11 and rats to r3-r8.  */
	l.ori	r11, r3, 0
	l.ori	r3, r4, 0
	l.ori	r4, r5, 0
	l.ori	r5, r6, 0
	l.ori	r6, r7, 0
	l.ori	r7, r8, 0
	l.lwz	r8, 0(r1)
	/* Do the syscall.  */
	l.sys	1
	 l.nop

	/* if -4096 < ret < 0 holds, it's an error */
	l.sfgeui r11, 0xf001
	l.bf	0f
	 l.nop

	l.jr	r9
 	 l.nop

0: 
	l.j	__syscall_error
	 l.ori	r3, r11, 0

	.cfi_endproc
	.size	syscall, . - syscall
