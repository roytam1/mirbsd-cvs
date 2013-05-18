# $MirOS: src/lib/libc/arch/i386/gen/Makefile.inc,v 1.3 2008/08/01 16:45:05 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 2005/02/01 15:12:29 millert Exp $

SRCS+=	_setjmp.S alloca.S fabs.S \
	modf.S setjmp.S sigsetjmp.S
SRCS+=	flt_rounds.S fpgetmask.S fpgetround.S fpgetsticky.S fpsetmask.S \
	fpsetround.S fpsetsticky.S
SRCS+=	fpclassifyl.c infinityl.c isfinitel.c isinfl.c isnanl.c nanf.c \
	signbitl.c
