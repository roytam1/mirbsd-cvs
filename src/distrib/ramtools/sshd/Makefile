# $MirOS: src/distrib/special/sshd/Makefile,v 1.1.7.1 2005/03/06 16:33:39 tg Exp $
# $OpenBSD: Makefile,v 1.64 2004/08/23 14:26:39 dtucker Exp $
#
# Yes, this is _without_ BSD auth.

SSHDIR=	${.CURDIR}/../../../usr.bin/ssh

.PATH: ${SSHDIR}

PROG=	sshd
BINOWN=	root
BINMODE=555
BINDIR=	/usr/sbin
NOMAN=	yes

SRCS=	sshd.c auth-rhosts.c auth-passwd.c auth-rsa.c auth-rh-rsa.c \
	sshpty.c sshlogin.c servconf.c serverloop.c \
	auth.c auth1.c auth2.c auth-options.c session.c \
	auth-chall.c auth2-chall.c groupaccess.c \
	auth-skey.c auth-bsdauth.c auth2-hostbased.c auth2-kbdint.c \
	auth2-none.c auth2-passwd.c auth2-pubkey.c \
	monitor_mm.c monitor.c monitor_wrap.c \
	kexdhs.c kexgexs.c

.include <bsd.prog.mk>

DPADD+=	${LIBCRYPTO} ${LIBUTIL} ${LIBZ} ${LIBDES}
LDADD+=	-lcrypto -lutil -lz -ldes

DPADD+=	${SSHDIR}/lib/${__objdir}/libssh.a
LDADD+=	-L${SSHDIR}/lib/${__objdir} -L${SSHDIR}/lib -lssh
