/* Assembler macros for OR1k.
   Copyright (C) 1997, 1998, 2003, 2009, 2010, 2012
   Free Software Foundation, Inc.
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
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdeps/generic/sysdep.h>
#include <features.h>

/* TODO: clean up this file */
#ifdef	__ASSEMBLER__

/* Syntactic details of assembler.  */

#define ALIGNARG(log2) log2
#define ASM_SIZE_DIRECTIVE(name) .size name,.-name

#define PLTJMP(_x)	_x##(PLT)

#define RETINSTR(cond, reg)	\
	mov##cond	pc, reg
#define DO_RET(_reg)		\
	.jr _reg

/* Define an entry point visible from C.  */
#define	ENTRY(name)							      \
  .globl C_SYMBOL_NAME(name);						      \
  .type C_SYMBOL_NAME(name),%function;					      \
  .align ALIGNARG(4);							      \
  C_LABEL(name)								      \
  .cfi_sections .debug_frame;						      \
  cfi_startproc;							      \
  CALL_MCOUNT

#undef	END
#define END(name)							      \
  cfi_endproc;								      \
  ASM_SIZE_DIRECTIVE(name)

/* If compiled for profiling, call `mcount' at the start of each function.  */
#ifdef	PROF
/* Call __gnu_mcount_nc if GCC >= 4.4.  */
#if __GNUC_PREREQ(4,4)
#define CALL_MCOUNT \
  str	lr,[sp, #-4]!; \
  cfi_adjust_cfa_offset (4); \
  cfi_rel_offset (lr, 0); \
  bl PLTJMP(mcount); \
  cfi_adjust_cfa_offset (-4); \
  cfi_restore (lr)
#else /* else call _mcount */
#define CALL_MCOUNT \
  str	lr,[sp, #-4]!; \
  cfi_adjust_cfa_offset (4); \
  cfi_rel_offset (lr, 0); \
  bl PLTJMP(mcount); \
  ldr lr, [sp], #4; \
  cfi_adjust_cfa_offset (-4); \
  cfi_restore (lr)
#endif
#else
#define CALL_MCOUNT		/* Do nothing.  */
#endif

/* Since C identifiers are not normally prefixed with an underscore
   on this system, the asm identifier `syscall_error' intrudes on the
   C name space.  Make sure we use an innocuous name.  */
#define	syscall_error	__syscall_error
#if __GNUC_PREREQ(4,4)
#define mcount		__gnu_mcount_nc
#else
#define mcount		_mcount
#endif

#endif	/* __ASSEMBLER__ */
