# $MirOS: src/usr.sbin/eeprom/Makefile,v 1.2 2005/03/13 19:16:26 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/12/31 16:22:26 miod Exp $

PROG=		eeprom
MAN=		eeprom.8
SRCS=		eehandlers.c getdate.c main.c ophandlers.c
CLEANFILES+=	getdate.c y.tab.h

BINGRP=		kmem
BINMODE=	2555

.include <bsd.prog.mk>
