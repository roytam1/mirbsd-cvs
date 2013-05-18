# $MirOS$
# $OpenBSD: Makefile.inc,v 1.4 2005/02/01 15:12:29 millert Exp $

SRCS+=	_setjmp.S alloca.S fabs.S \
	modf.S setjmp.S sigsetjmp.S
SRCS+=	flt_rounds.S fpgetmask.S fpgetround.S fpgetsticky.S fpsetmask.S \
	fpsetround.S fpsetsticky.S
SRCS+=	divsi3.S fixdfsi.S fixunsdfsi.S udivsi3.S
SRCS+=	fpclassifyl.c infinityl.c isfinitel.c isinfl.c isnanl.c nanf.c \
	signbitl.c
