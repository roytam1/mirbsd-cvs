# $MirOS: src/usr.sbin/ntpd/Makefile,v 1.2 2005/03/13 19:17:09 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/07/04 11:01:49 alexander Exp $

PROG=	ntpd
SRCS=	ntpd.c buffer.c log.c imsg.c ntp.c ntp_msg.c parse.y config.c \
	server.c client.c util.c
CFLAGS+= -Wall -Wextra
CFLAGS+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS+= -Wmissing-declarations
CFLAGS+= -Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+= -Wsign-compare
YFLAGS=
MAN=	ntpd.8 ntpd.conf.5

.include <bsd.prog.mk>
