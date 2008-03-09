# $MirOS$
# $OpenBSD: Makefile,v 1.7 2001/10/03 19:07:58 drahn Exp $

PROG=		apm
SRCS=		apm.c apmsubr.c
.PATH:	${.CURDIR}/../apmd

CPPFLAGS+=	-I${.CURDIR}/../apmd
LINKS=		${BINDIR}/apm ${BINDIR}/zzz

MAN=		apm.8
MLINKS=		apm.8 zzz.8

.include <bsd.prog.mk>
