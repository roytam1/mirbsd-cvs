# $MirOS: src/usr.bin/ssh/sshd/Makefile,v 1.9 2014/03/28 22:31:59 tg Exp $
# $OpenBSD: Makefile,v 1.69 2009/05/28 16:50:16 andreas Exp $

.PATH:		${.CURDIR}/..

PROG=	sshd
BINOWN=	root
BINMODE=555
BINDIR=	/usr/sbin
MAN=	sshd.8 sshd_config.5
CPPFLAGS+= -DBSD_AUTH

SRCS=	sshd.c auth-rhosts.c auth-passwd.c auth-rsa.c auth-rh-rsa.c \
	sshpty.c sshlogin.c servconf.c serverloop.c \
	auth.c auth1.c auth2.c auth-options.c session.c \
	auth-chall.c auth2-chall.c groupaccess.c \
	auth-bsdauth.c auth2-hostbased.c auth2-kbdint.c \
	auth2-none.c auth2-passwd.c auth2-pubkey.c \
	monitor_mm.c monitor.c monitor_wrap.c \
	kexdhs.c kexgexs.c sftp-server.c sftp-common.c

DPADD+=	${LIBCRYPTO} ${LIBUTIL} ${LIBZ} ${LIBDES}
LDADD+=	-lcrypto -lutil -lz -ldes

CFLAGS_auth1.o+=	-Wno-unused
CFLAGS_auth2.o+=	-Wno-unused
CFLAGS_auth2-chall.o+=	-Wno-unused
CFLAGS_monitor.o+=	-Wno-unused
CFLAGS_monitor_wrap.o+=	-Wno-unused
CFLAGS_session.o+=	-Wno-unused
CFLAGS_sshd.o+=		-Wno-unused
CFLAGS_serverloop.o+=	-Wno-unused

.include <bsd.prog.mk>
