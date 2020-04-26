/* Machine-specific pthread type layouts.  OpenRISC version.
   Copyright (C) 2020 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _BITS_PTHREADTYPES_H
#define _BITS_PTHREADTYPES_H	1

#include <bits/wordsize.h>

/* Opaque union sizes for:
     pthread_attr_t - internally pthread_attr
     pthread_mutex_t - internally __pthread_mutex_s
     pthread_mutexattr_t - internally pthread_mutexattr
     pthread_cond_t - internally __pthread_cond_s
     pthread_condattr_t - internally pthread_condattr
     pthread_rwlock_t - internally __pthread_rwlock_arch_t
     pthread_rwlockattr_t - internally pthread_rwlockattr
     pthread_barrier_t - internally pthread_barrier
     pthread_barrierattr_t - internally pthread_barrierattr  */

#define __SIZEOF_PTHREAD_ATTR_T 32
#define __SIZEOF_PTHREAD_MUTEX_T 32
#define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#define __SIZEOF_PTHREAD_COND_T 48
#define __SIZEOF_PTHREAD_CONDATTR_T 4
#define __SIZEOF_PTHREAD_RWLOCK_T 44
#define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#define __SIZEOF_PTHREAD_BARRIER_T 20
#define __SIZEOF_PTHREAD_BARRIERATTR_T 4

#define __PTHREAD_COMPAT_PADDING_MID
#define __PTHREAD_COMPAT_PADDING_END
#define __PTHREAD_MUTEX_LOCK_ELISION		0
#define __PTHREAD_MUTEX_USE_UNION	 	0
#define __PTHREAD_MUTEX_NUSERS_AFTER_KIND	0

#define __LOCK_ALIGNMENT
#define __ONCE_ALIGNMENT

struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad1;
  unsigned int __pad2;
  int __cur_writer;
  int __shared;
  unsigned int __pad3;
  /* FLAGS must stay at this position in the structure to maintain
     binary compatibility.  */
  unsigned int __flags;
  unsigned int __pad4;
};

#define __PTHREAD_RWLOCK_ELISION_EXTRA 		0

#endif	/* bits/pthreadtypes.h */
