/* IBM PowerPC native-dependent macros for GDB, the GNU debugger.
   Copyright 1995, 2000 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifndef NM_LINUX_H

#include "config/nm-linux.h"

#define NM_LINUX_H

/* Return sizeof user struct to callers in less machine dependent routines */

#define KERNEL_U_SIZE kernel_u_size()
extern int kernel_u_size (void);

/* This is the amount to subtract from u.u_ar0
   to get the offset in the core file of the register values.  */
#define KERNEL_U_ADDR 0x0

#define FETCH_INFERIOR_REGISTERS

#endif /* #ifndef NM_LINUX_H */
