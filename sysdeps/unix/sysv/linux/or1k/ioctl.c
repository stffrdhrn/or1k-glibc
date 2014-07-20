/* Copyright (C) 1998, 2002, 2003, 2004 Free Software Foundation, Inc.
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

#include <stdarg.h>
#include <sysdep.h>

/* or1k ABI uses stack for varargs, syscall uses registers.
 * This function moves from varargs to regs. */
int
__ioctl (int fd, unsigned long int request, ...)
{
  void *arg;
  va_list ap;
  int result;

  va_start (ap, request);
  arg = va_arg (ap, void *);

  result = INLINE_SYSCALL (ioctl, 3, fd, request, arg);
  va_end (ap);

  return result;
}
weak_alias (__ioctl, ioctl)
