# $MirOS: src/usr.bin/ssh/lib/Makefile,v 1.3 2005/04/14 19:49:36 tg Exp $
# $OpenBSD: Makefile,v 1.53 2006/04/18 10:44:28 dtucker Exp $

.PATH:		${.CURDIR}/..

LIB=	ssh
SRCS=	authfd.c authfile.c bufaux.c bufbn.c buffer.c canohost.c channels.c \
	cipher.c cipher-3des1.c cipher-bf1.c cipher-ctr.c \
	cleanup.c compat.c compress.c crc32.c deattack.c fatal.c \
	hostfile.c log.c match.c nchan.c packet.c readpass.c \
	rsa.c ttymodes.c xmalloc.c atomicio.c \
	key.c dispatch.c kex.c mac.c uidswap.c uuencode.c misc.c \
	ssh-dss.c ssh-rsa.c dh.c kexdh.c kexgex.c \
	kexdhc.c kexgexc.c scard.c msg.c progressmeter.c dns.c \
	monitor_fdpass.c md-sha256.c

DEBUGLIBS=	no
NOPIC=		yes

install:
# nothing to do here

.include <bsd.lib.mk>
