# $MirOS: src/usr.sbin/rdate/Makefile,v 1.5 2006/06/09 20:58:08 tg Exp $

PROG=	rdate
SRCS=	ntp.c ntpleaps.c rdate.c rfc868time.c
MAN=	rdate.8

DPADD+= ${LIBUTIL}
LDADD+= -lutil

.include <bsd.prog.mk>
