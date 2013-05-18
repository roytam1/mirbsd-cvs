# $MirOS: src/usr.sbin/rdate/Makefile,v 1.4 2006/05/29 23:38:31 tg Exp $

PROG=	rdate
SRCS=	ntp.c ntpleaps.c rdate.c rfc868time.c
MAN=	rdate.8
CFLAGS+=-Wall

# for MirBSD:
DPADD+= ${LIBUTIL}
LDADD+= -lutil
# for generic GNU/Linux:
#CPPFLAGS+= -DNO_UTIL

.include <bsd.prog.mk>
