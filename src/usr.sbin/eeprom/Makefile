# $MirOS$
# $OpenBSD: Makefile,v 1.9 2002/12/31 16:22:26 miod Exp $

.if ${MACHINE} == "sparc" || ${MACHINE} == "sparc64"
PROG=	eeprom

BINGRP=	kmem
BINMODE=2555

SRCS=		eehandlers.c getdate.c main.c ophandlers.c
CLEANFILES+=	getdate.c y.tab.h
.else
NOPROG=		yes
.endif

MAN=		eeprom.8

.include <bsd.prog.mk>
