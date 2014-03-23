# $MirOS: src/usr.bin/xlint/xlint/Makefile,v 1.3 2006/07/03 14:45:59 tg Exp $
# $OpenBSD: Makefile,v 1.5 2011/11/08 10:37:10 guenther Exp $
# $NetBSD: Makefile,v 1.2 1995/07/03 21:25:14 cgd Exp $

.PATH:	${.CURDIR}/../lint1

PROG=	xlint
SRCS=	mem.c xlint.c
MAN=	lint.1

CPPFLAGS+= -I${.CURDIR}/../lint1

realinstall:
	${INSTALL} ${INSTALL_COPY} -S ${INSTALL_STRIP} \
	    -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/lint

.include "${.CURDIR}/../../Makefile.inc"
.include <bsd.prog.mk>
