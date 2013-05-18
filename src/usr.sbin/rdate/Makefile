# $MirOS: src/usr.sbin/rdate/Makefile,v 1.7 2007/07/05 22:32:25 tg Exp $

PROG=	rdate
SRCS=	ntp.c rdate.c rfc868time.c
MAN=	rdate.8

.ifdef SMALL
CPPFLAGS+= -DNO_UTIL -DSMALL
.else
DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.include <bsd.prog.mk>
