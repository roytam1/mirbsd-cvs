/* $MirOS: gcc/gcc/config/rs6000/mirbsd.h,v 1.2 2005/04/29 16:41:50 tg Exp $ */

/* Definitions of target machine for GNU compiler,
   for PowerPC NetBSD systems.
   Copyright 2002, 2003, 2005 Free Software Foundation, Inc.
   Contributed by Wasabi Systems, Inc.
   Hacked by Thorsten Glaser <tg@MirBSD.de>

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 2, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to the
   Free Software Foundation, 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.  */

#undef  TARGET_OS_CPP_BUILTINS	/* FIXME: sysv4.h should not define this! */
#define TARGET_OS_CPP_BUILTINS()		\
  do						\
    {						\
      MIRBSD_OS_CPP_BUILTINS();			\
      builtin_define ("__powerpc__");		\
      builtin_assert ("cpu=powerpc");		\
      builtin_assert ("machine=powerpc");	\
    }						\
  while (0)

/* Make GCC agree with <machine/ansi.h>.  */

#undef  SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef  PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

/* Undo the spec mess from sysv4.h, and just define the specs
   the way MirOS BSD systems actually expect.  */

#undef  CPP_SPEC
#define CPP_SPEC MIRBSD_CPP_SPEC

#undef  LINK_SPEC
#define LINK_SPEC				\
  "%{!msdata=none:%{G*}} %{msdata=none:-G0}	\
   %{assert*} %{R*} %{rpath*}			\
   %{!shared:					\
     -dc -dp					\
     %{!nostdlib:				\
       %{!r*:					\
	 %{!e*:-e _start}}}			\
     %{!static:					\
       %{rdynamic:-export-dynamic}		\
       %{!dynamic-linker:			\
	 -dynamic-linker /usr/libexec/ld.so}}	\
     %{static:-Bstatic}}			\
   %{!static:-Bdynamic}				\
   %{shared:-shared}"

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC \
  "%:if-exists(crti%O%s)	\
   ncrti%O%s			\
   %{!shared:crt0%O%s}		\
   %{static:			\
     %:if-exists-else(crtbeginT%O%s crtbegin%O%s)} \
   %{!static:			\
     %{!shared:crtbegin%O%s}	\
     %{shared:crtbeginS%O%s}}"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC \
  "crtsavres%O%s		\
   %{!shared:crtend%O%s}	\
   %{shared:crtendS%O%s}	\
   ncrtn%O%s"

#undef  LIB_SPEC
#define LIB_SPEC MIRBSD_LIB_SPEC

#undef  SUBTARGET_EXTRA_SPECS

#undef	DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR 1

#undef	WCHAR_TYPE
#define	WCHAR_TYPE "int"

#undef	WCHAR_TYPE_SIZE
#define	WCHAR_TYPE_SIZE 32

#undef  TARGET_VERSION
#define TARGET_VERSION fprintf (stderr, " (MirOS BSD/macppc)");
