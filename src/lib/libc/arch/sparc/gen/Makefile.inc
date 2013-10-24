# $MirOS: src/lib/libc/arch/sparc/gen/Makefile.inc,v 1.4 2009/09/15 16:27:30 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 2005/02/01 15:12:30 millert Exp $

SRCS+=	_setjmp.S fabs.S modf.S
SRCS+=	flt_rounds.c fpgetmask.c fpgetround.c fpgetsticky.c fpsetmask.c \
	fpsetround.c fpsetsticky.c
SRCS+=	setjmp.S sigsetjmp.S
SRCS+=	alloca.c
SRCS+=	nanf.c