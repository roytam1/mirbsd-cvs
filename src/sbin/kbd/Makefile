# $MirOS: src/sbin/kbd/Makefile,v 1.2 2005/03/06 19:50:16 tg Exp $
# $OpenBSD: Makefile,v 1.17 2003/10/31 04:05:29 drahn Exp $

PROG=	kbd
SRCS=	main.c kbd_wscons.c
MAN=	kbd.8
LDADD=	-lkvm -lz
DPADD=	${LIBKVM} ${LIBZ}

.include <bsd.prog.mk>
