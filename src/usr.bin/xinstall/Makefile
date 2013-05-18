# $MirOS: src/usr.bin/xinstall/Makefile,v 1.5 2008/03/27 17:42:44 tg Exp $

PROG=	xinstall
SRCS=	${PROG}.c
MAN=	install.1

.include <bsd.own.mk>

.if ${MACHINE_OS} == "Linux"
HAVE_SETMODE?=	0
.endif
HAVE_SETMODE?=	1

.if ${HAVE_SETMODE} != 1
.PATH: ${.CURDIR}/../../bin/mksh
SRCS+=		setmode.c
CPPFLAGS+=	-DNEED_SETMODE_DECL
.endif

realinstall:
.if (${OBJECT_FMT} == "Mach-O") && (${LINK.prog} != "NO")
	@echo Relinking ${PROG}
	${LINK.prog} -o ${PROG}
.endif
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/install

.include <bsd.prog.mk>
