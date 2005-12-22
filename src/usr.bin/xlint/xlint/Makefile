# $MirOS$
# $OpenBSD: Makefile,v 1.4 1997/04/27 20:57:00 millert Exp $
# $NetBSD: Makefile,v 1.2 1995/07/03 21:25:14 cgd Exp $

.PATH:	${.CURDIR}/../lint1

PROG=	xlint
SRCS=	mem.c xlint.c
MAN=	lint.1

CPPFLAGS+= -I${.CURDIR}/../lint1 -DREISER_CPP

realinstall:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/lint

.include "${.CURDIR}/../../Makefile.inc"
.include <bsd.prog.mk>
