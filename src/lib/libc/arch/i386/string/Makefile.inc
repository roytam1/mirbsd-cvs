# $MirOS: src/lib/libc/arch/i386/string/Makefile.inc,v 1.8 2008/08/04 19:10:53 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1999/04/25 00:23:58 millert Exp $

SRCS+=	index.S \
	rindex.S strcat.S strcpy.S strcspn.c \
	strncat.c strncpy.c strpbrk.c strsep.c \
	strspn.c strstr.c swab.S
LSRCS+=	index.c \
	rindex.c strcat.c strcpy.c swab.c

_MD_BCMP=1
_MD_MEMCPY=1
_MD_MEMMOVE=1
_MD_STRCHR=1
_MD_STRRCHR=1
