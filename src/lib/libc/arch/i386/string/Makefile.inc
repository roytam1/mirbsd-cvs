# $MirOS: src/lib/libc/arch/i386/string/Makefile.inc,v 1.9 2010/01/10 20:18:51 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1999/04/25 00:23:58 millert Exp $

SRCS+=	\
	strcat.S strcpy.S strcspn.c \
	strncat.c strpbrk.c strsep.c \
	strspn.c strstr.c swab.S
LSRCS+=	\
	rindex.c strcat.c strcpy.c swab.c

_MD_BCMP=1
_MD_MEMCPY=1
_MD_MEMMOVE=1
