# $MirOS: src/usr.sbin/rdate/Makefile,v 1.3 2005/03/15 19:28:38 tg Exp $

PROG=	rdate
SRCS=	rdate.c rfc868time.c ntp.c leapsecs.c
MAN=	rdate.8
CFLAGS+=-Wall

# for MirBSD:
DPADD+= ${LIBUTIL}
LDADD+= -lutil
# for generic GNU/Linux:
#CPPFLAGS+= -DNO_UTIL

.include <bsd.prog.mk>
