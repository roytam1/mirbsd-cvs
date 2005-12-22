/* $MirOS$ */

/* Enable stack execution around trampolines.
   Copyright (c) 2005 Free Software Foundation, Inc.
   Contributed by Thorsten Glaser <tg@66h.42h.de>

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#undef ENABLE_EXECUTE_STACK
#define ENABLE_EXECUTE_STACK						\
extern void __enable_execute_stack (void *);				\
void									\
__enable_execute_stack (void *addr)					\
{									\
  static intptr_t size = 0;						\
  static intptr_t mask;							\
  intptr_t page = (intptr_t)addr;					\
  size_t end = (intptr_t)addr + TRAMPOLINE_SIZE;			\
									\
  if (size == 0)							\
    {									\
      size = sysconf(_SC_PAGESIZE);					\
      mask = ~(size - 1);						\
    }									\
									\
  page &= mask;								\
  end = (end & mask) + size - page;					\
									\
  if (mprotect ((char *)page, end,					\
   PROT_READ | PROT_WRITE | PROT_EXEC) < 0)				\
    perror ("mprotect of trampoline code");				\
}
