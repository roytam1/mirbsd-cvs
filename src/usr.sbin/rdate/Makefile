# $MirOS: src/usr.sbin/rdate/Makefile,v 1.8 2007/07/08 15:00:30 tg Exp $

PROG=		rdate
SRCS=		cutil.c ntp.c rdate.c rfc868time.c
MAN=		rdate.8
CPPFLAGS+=	-DIN_RDATE

.ifdef SMALL
CPPFLAGS+=	-DNO_UTIL -DSMALL
.else
DPADD+=		${LIBUTIL}
LDADD+=		-lutil
.endif

.include <bsd.prog.mk>
