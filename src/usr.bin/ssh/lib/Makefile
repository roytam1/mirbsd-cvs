# $MirOS: src/usr.bin/ssh/lib/Makefile,v 1.9 2008/12/27 21:18:01 tg Exp $
# $OpenBSD: Makefile,v 1.58 2008/11/04 08:22:13 djm Exp $

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
	monitor_fdpass.c umac.c addrmatch.c schnorr.c jpake.c
SRCS+=	md-sha256.c

NOPIC=		yes

CFLAGS_channels.o+=	-Wno-unused

install:

.include <bsd.lib.mk>
