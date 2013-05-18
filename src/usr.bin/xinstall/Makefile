# $MirOS: src/usr.bin/xinstall/Makefile,v 1.7 2008/04/07 00:30:58 tg Exp $

PROG=	xinstall
SRCS=	${PROG}.c
MAN=	install.1

.include <bsd.own.mk>

.if (${MACHINE_OS} == "Linux") || (${MACHINE_OS} == "GNU")
HAVE_SETMODE?=	0
.endif
HAVE_SETMODE?=	1

.if ${HAVE_SETMODE} != 1
.PATH: ${.CURDIR}/../../bin/mksh
SRCS+=		setmode.c
CPPFLAGS+=	-DNEED_SETMODE_DECL
.endif

realinstall:
.if ${OBJECT_FMT} == "Mach-O"
	@echo Relinking ${PROG}
	${LINK.prog} -o ${PROG}
.endif
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/install

.include <bsd.prog.mk>
