# $MirOS: src/usr.sbin/rdate/Makefile,v 1.2 2005/03/13 19:17:21 tg Exp $

PROG=	rdate
SRCS=	rdate.c rfc868time.c ntp.c ntpleaps.c
MAN=	rdate.8
CFLAGS+=-Wall

# for MirBSD:
DPADD+= ${LIBUTIL}
LDADD+= -lutil
# for generic GNU/Linux:
#CPPFLAGS+= -DNO_UTIL

.include <bsd.prog.mk>
