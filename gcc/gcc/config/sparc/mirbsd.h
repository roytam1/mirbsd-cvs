/* $MirOS: gcc/gcc/config/sparc/mirbsd.h,v 1.1 2006/06/11 00:15:13 tg Exp $ */

/* Definitions of target machine for GCC,
   for sparc/ELF MirOS BSD systems.
   Copyright (C) 2001, 2002, 2005, 2006
   Free Software Foundation, Inc.
   Contributed by matthew green <mrg@eterna.com.au>
   Hacked by Thorsten Glaser <tg@66h.42h.de>

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#define TARGET_OS_CPP_BUILTINS()		\
  do						\
    {						\
      MIRBSD_OS_CPP_BUILTINS();			\
      builtin_define ("__sparc");		\
      builtin_define ("__sparc__");		\
    }						\
  while (0)


/* Make gcc agree with <machine/ansi.h> */

#undef SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

/* We always use gas here, so we don't worry about ECOFF assembler
   problems.  */
#undef TARGET_GAS
#define TARGET_GAS 1

/* Default to pcc-struct-return, because this is the ELF abi and
   we don't care about compatibility with older gcc versions.  */
#undef DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 1

#undef TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (MirOS BSD/sparc)");
