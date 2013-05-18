# $MirOS: src/usr.bin/systat/Makefile,v 1.3 2005/11/23 18:04:23 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/11/16 09:52:33 markus Exp $

PROG=	systat

.PATH:	${.CURDIR}/../../usr.bin/vmstat

CPPFLAGS+=	-I${.CURDIR}/../../usr.bin/vmstat
SRCS=	cmds.c cmdtab.c disks.c dkstats.c fetch.c if.c iostat.c keyboard.c \
	main.c mbufs.c netcmds.c netstat.c pigs.c swap.c vmstat.c
DPADD=	${LIBCURSES} ${LIBM} ${LIBKVM} ${LIBZ}
LDADD=	-lcurses -lm -lkvm -lz
BINGRP=	kmem
BINMODE=2555

.include <bsd.prog.mk>

