# $MirOS: src/distrib/special/sshd/Makefile,v 1.11 2014/03/28 22:35:20 tg Exp $
# $OpenBSD: Makefile,v 1.68 2008/11/04 08:22:13 djm Exp $
#-
# Build an extra small sshd(8) without BSD auth

SSHDIR=	${.CURDIR}/../../../usr.bin/ssh
.PATH: ${SSHDIR}

CFLAGS+=-Wall -Wpointer-arith -Wno-uninitialized -Wstrict-prototypes \
	-Wmissing-prototypes -Wunused -Wsign-compare -Wshadow
CDIAGFLAGS+=	-Wno-cast-qual -Wno-unused

PROG=	sshd
BINOWN=	root
BINMODE=555
BINDIR=	/usr/sbin
CPPFLAGS+= -DSMALL

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

.include <bsd.prog.mk>

DPADD+=	${SSHDIR}/lib/${__objdir}/libssh.a
LDADD+=	-L${SSHDIR}/lib/${__objdir} -L${SSHDIR}/lib -lssh
