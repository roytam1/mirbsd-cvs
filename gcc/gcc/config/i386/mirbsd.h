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
    }						\
  while (0)


#undef ASM_APP_ON
#define ASM_APP_ON "#APP\n"

#undef ASM_APP_OFF
#define ASM_APP_OFF "#NO_APP\n"

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "#"

#undef DBX_REGISTER_NUMBER
#define DBX_REGISTER_NUMBER(n)  svr4_dbx_register_map[n]

#undef HAS_INIT_SECTION

/* This is how we tell the assembler that two symbols have the same value.  */

#define ASM_OUTPUT_DEF(FILE,NAME1,NAME2) \
  do { assemble_name(FILE, NAME1); 	 \
       fputs(" = ", FILE);		 \
       assemble_name(FILE, NAME2);	 \
       fputc('\n', FILE); } while (0)

/* A C statement to output to the stdio stream FILE an assembler
   command to advance the location counter to a multiple of 1<<LOG
   bytes if it is within MAX_SKIP bytes.

   This is used to align code labels according to Intel recommendations.  */

#ifdef HAVE_GAS_MAX_SKIP_P2ALIGN
#define ASM_OUTPUT_MAX_SKIP_ALIGN(FILE, LOG, MAX_SKIP)			\
  if ((LOG) != 0) {							\
    if ((MAX_SKIP) == 0) fprintf ((FILE), "\t.p2align %d\n", (LOG));	\
    else fprintf ((FILE), "\t.p2align %d,,%d\n", (LOG), (MAX_SKIP));	\
  }
#endif

/* We always use gas here, so we don't worry about ECOFF assembler
   problems.  */
#undef TARGET_GAS
#define TARGET_GAS 1

/* Default to pcc-struct-return, because this is the ELF abi and
   we don't care about compatibility with older gcc versions.  */
#define DEFAULT_PCC_STRUCT_RETURN 1

/* By default, target has a 80387, uses IEEE compatible arithmetic,
   and returns float values in the 387.  */
#undef TARGET_SUBTARGET_DEFAULT
#define TARGET_SUBTARGET_DEFAULT (MASK_80387 | MASK_IEEE_FP | MASK_FLOAT_RETURNS)

/* This gets defined in elfos.h, and keeps us from using
   libraries compiled with the native cc, so undef it. */
#undef NO_DOLLAR_IN_LABEL


#undef TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (MirOS BSD/i386)");
