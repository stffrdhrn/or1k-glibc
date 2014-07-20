/* Copyright (C) 2014 Free Software Foundation, Inc.
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

#include <sysdep.h>
#include <tls.h>
#ifndef __ASSEMBLER__
# include <nptl/pthreadP.h>
#endif

#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

# undef PSEUDO
# define PSEUDO(name, syscall_name, args)                                     \
ENTRY(__##syscall_name##_nocancel);                                           \
L(pseudo_nocancel):                                                           \
  DO_CALL(syscall_name);                                                      \
  l.j     L(pseudo_finish);                                                   \
   l.nop;                                                                     \
END(__##syscall_name##_nocancel);                                             \
ENTRY(name);                                                                  \
  SINGLE_THREAD_P(r13);                                                       \
  l.sfeq  r13,r0;                                                             \
  l.bnf   L(pseudo_nocancel);                                                 \
   l.nop;                                                                     \
  l.j     L(pseudo_nocancel);                                                 \
   l.nop;                                                                     \
L(pseudo_finish):                                                             \
  /* if -4096 < ret < 0 holds, it's an error */                               \
  l.sfgeui r11,0xf001;                                                        \
  l.bf    L(pseudo_end);                                                      \
   l.nop

# undef PSEUDO_END
# define PSEUDO_END(name) \
L(pseudo_end): \
  l.j SYSCALL_ERROR_NAME; \
  l.ori r3,r11,0; \
  END(name)

# define PUSHARGS_0     /* nothing to do */
# define PUSHARGS_1     PUSHARGS_0 sw a0, 0(sp); cfi_rel_offset (a0, 0);
# define PUSHARGS_2     PUSHARGS_1 sw a1, 4(sp); cfi_rel_offset (a1, 4);
# define PUSHARGS_3     PUSHARGS_2 sw a2, 8(sp); cfi_rel_offset (a2, 8);
# define PUSHARGS_4     PUSHARGS_3 sw a3, 12(sp); cfi_rel_offset (a3, 12);
# define PUSHARGS_5     PUSHARGS_4 /* handled by SAVESTK_## */
# define PUSHARGS_6     PUSHARGS_5
# define PUSHARGS_7     PUSHARGS_6

# define POPARGS_0      /* nothing to do */
# define POPARGS_1      POPARGS_0 lw a0, 0(sp);
# define POPARGS_2      POPARGS_1 lw a1, 4(sp);
# define POPARGS_3      POPARGS_2 lw a2, 8(sp);
# define POPARGS_4      POPARGS_3 lw a3, 12(sp);
# define POPARGS_5      POPARGS_4 /* args already in new stackframe */
# define POPARGS_6      POPARGS_5
# define POPARGS_7      POPARGS_6


# define STKSPACE       48
# define SAVESTK_0      subu sp, STKSPACE; cfi_adjust_cfa_offset(STKSPACE)
# define SAVESTK_1      SAVESTK_0
# define SAVESTK_2      SAVESTK_1
# define SAVESTK_3      SAVESTK_2
# define SAVESTK_4      SAVESTK_3
# define SAVESTK_5      lw t0, 16(sp);          \
                        SAVESTK_0;              \
                        sw t0, 16(sp)

# define SAVESTK_6      lw t0, 16(sp);          \
                        lw t1, 20(sp);          \
                        SAVESTK_0;              \
                        sw t0, 16(sp);          \
                        sw t1, 20(sp)

# define SAVESTK_7      lw t0, 16(sp);          \
                        lw t1, 20(sp);          \
                        lw t2, 24(sp);          \
                        SAVESTK_0;              \
                        sw t0, 16(sp);          \
                        sw t1, 20(sp);          \
                        sw t2, 24(sp)

# define RESTORESTK     addu sp, STKSPACE; cfi_adjust_cfa_offset(-STKSPACE)


# define PSEUDO_JMP(sym) l.jal sym; l.nop;

# ifdef IS_IN_libpthread
#  define CENABLE       PSEUDO_JMP (__pthread_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__pthread_disable_asynccancel)
# elif defined IS_IN_librt
#  define CENABLE       PSEUDO_JMP (__librt_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__librt_disable_asynccancel)
# else
#  define CENABLE       PSEUDO_JMP (__libc_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__libc_disable_asynccancel)
# endif

# ifndef __ASSEMBLER__
#  define SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
                                   header.multiple_threads) == 0, 1)
# else
/* It's not super nice to have "r10" hardcoded here */
#  define SINGLE_THREAD_P(reg) l.lwz reg, MULTIPLE_THREADS_OFFSET(r10)
#endif

#elif !defined __ASSEMBLER__

# define SINGLE_THREAD_P 1
# define NO_CANCELLATION 1

#endif

#ifndef __ASSEMBLER__
# define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
                                   header.multiple_threads) == 0, 1)
#endif
