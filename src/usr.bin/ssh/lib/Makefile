# $MirOS$
# $OpenBSD: Makefile,v 1.50 2004/12/22 02:13:19 djm Exp $

.PATH:		${.CURDIR}/..

LIB=	ssh
SRCS=	authfd.c authfile.c bufaux.c buffer.c canohost.c channels.c \
	cipher.c cipher-3des1.c cipher-bf1.c cipher-ctr.c \
	cleanup.c compat.c compress.c crc32.c deattack.c fatal.c \
	hostfile.c log.c match.c nchan.c packet.c readpass.c \
	rsa.c tildexpand.c ttymodes.c xmalloc.c atomicio.c \
	key.c dispatch.c kex.c mac.c uidswap.c uuencode.c misc.c \
	ssh-dss.c ssh-rsa.c dh.c kexdh.c kexgex.c \
	kexdhc.c kexgexc.c scard.c msg.c progressmeter.c dns.c \
	monitor_fdpass.c

DEBUGLIBS=	no
NOPIC=		yes

install:
# nothing to do here

.include <bsd.lib.mk>
