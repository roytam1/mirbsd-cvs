# $MirOS$

PROG=	rdate
SRCS=	rdate.c rfc868time.c ntp.c ntpleaps.c
MAN=	rdate.8
CFLAGS+=-Wall -Werror

# for MirBSD:
DPADD+= ${LIBUTIL}
LDADD+= -lutil
# for generic GNU/Linux:
#CFLAGS+= -DNO_UTIL

.include <bsd.prog.mk>
