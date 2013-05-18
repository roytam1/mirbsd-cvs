# $MirOS: src/usr.sbin/rdate/Makefile,v 1.6 2007/05/14 22:06:51 tg Exp $

PROG=	rdate
SRCS=	ntp.c rdate.c rfc868time.c
MAN=	rdate.8

.ifdef SMALL
CPPFLAGS+= -DNO_UTIL
.else
DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.include <bsd.prog.mk>
