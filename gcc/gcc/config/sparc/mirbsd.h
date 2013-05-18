/* $MirOS: gcc/gcc/config/i386/mirbsd.h,v 1.6 2008/11/08 23:03:42 tg Exp $ */

/* Definitions of target machine for GCC,
   for i386/ELF MirOS BSD systems.
   Copyright (C) 2001, 2002, 2005, 2006, 2009
   Free Software Foundation, Inc.
   Contributed by matthew green <mrg@eterna.com.au>
   Hacked by Thorsten “mirabilos” Glaser <tg@mirbsd.org>

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


/* We always use gas here, so we don't worry about ECOFF assembler
   problems.  */
#undef TARGET_GAS
#define TARGET_GAS 1

/* Default to pcc-struct-return, because this is the ELF abi and
   we don't care about compatibility with older gcc versions.  */
#undef DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 1

/* This gets defined in elfos.h, and keeps us from using
   libraries compiled with the native cc, so undef it. */
#undef NO_DOLLAR_IN_LABEL


#undef TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (MirOS BSD/sparc)");
