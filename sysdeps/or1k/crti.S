# Start .init and .fini sections.
# Copyright (C) 2010 Embecosm Limited
# 
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GCC is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# Under Section 7 of GPL version 3, you are granted additional
# permissions described in the GCC Runtime Library Exception, version
# 3.1, as published by the Free Software Foundation.
#
# You should have received a copy of the GNU General Public License and
# a copy of the GCC Runtime Library Exception along with this program;
# see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
# <http://www.gnu.org/licenses/>.

#include <libc-symbols.h>
#include <sysdep.h>

#ifndef PREINIT_FUNCTION
# define PREINIT_FUNCTION __gmon_start__
#endif

#ifndef PREINIT_FUNCTION_WEAK
# define PREINIT_FUNCTION_WEAK 1
#endif

#if PREINIT_FUNCTION_WEAK
	weak_extern (PREINIT_FUNCTION)
#else
	.hidden PREINIT_FUNCTION
#endif

	.section .init
	.global _init
_init:
	l.addi  r1,r1,-8
	l.sw  0(r1),r9
	l.sw  4(r1),r16

#if PREINIT_FUNCTION_WEAK
	l.jal 8

	/* Check if PREINIT_FUNCTION is loaded in GOT */
	l.movhi  r16,gotpchi(_GLOBAL_OFFSET_TABLE_-4)
	l.ori    r16,r16,gotpclo(_GLOBAL_OFFSET_TABLE_+0)
	l.add    r16,r16,r9
	l.lwz    r9,got(PREINIT_FUNCTION)(r16)
	l.sfeqi  r9,0
	l.bf     .Lno_weak_fn
	l.nop

	l.jal    plt(PREINIT_FUNCTION)
	l.nop

.Lno_weak_fn:
#else
	l.jal PREINIT_FUNCTION
	l.nop

#endif

	.section .fini
	.global _fini
_fini:
	l.addi  r1,r1,-4
	l.sw    0(r1),r9

