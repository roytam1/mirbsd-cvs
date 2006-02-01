# $MirOS: src/distrib/special/grep/Makefile,v 1.2 2005/03/06 18:58:10 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/06/22 22:24:41 deraadt Exp $

PROG=	grep
SRCS=	binary.c file.c grep.c mmfile.c queue.c util.c
NOMAN=	yes
.include <bsd.own.mk>
CFLAGS+=	-DNOZ
.PATH:  ${.CURDIR}/../../../usr.bin/grep

.include <bsd.prog.mk>
