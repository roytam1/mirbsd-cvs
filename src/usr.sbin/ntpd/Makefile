# $MirOS: src/usr.sbin/ntpd/Makefile,v 1.5 2014/03/12 23:42:59 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/07/04 11:01:49 alexander Exp $

PROG=		ntpd
SRCS=		buffer.c client.c config.c cutil.c imsg.c log.c ntp.c \
		ntp_msg.c ntpd.c parse.y server.c util.c
CPPFLAGS+=	-DIN_NTPD
CFLAGS+=	-Wall -Wextra
CFLAGS+=	-Wstrict-prototypes -Wmissing-prototypes
CFLAGS+=	-Wmissing-declarations
CFLAGS+=	-Wshadow -Wpointer-arith -Wcast-qual
CFLAGS+=	-Wsign-compare
YFLAGS=
MAN=		ntpd.8 ntpd.conf.5

# for cutil.c
.PATH: ${.CURDIR}/../rdate

.include <bsd.prog.mk>
