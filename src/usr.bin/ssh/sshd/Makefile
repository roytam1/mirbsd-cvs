# $MirOS$
# $OpenBSD: Makefile,v 1.64 2004/08/23 14:26:39 dtucker Exp $

.PATH:		${.CURDIR}/..

PROG=	sshd
BINOWN=	root
BINMODE=555
BINDIR=	/usr/sbin
MAN=	sshd.8 sshd_config.5
CPPFLAGS+=	-DHAVE_LOGIN_CAP -DBSD_AUTH

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

.if ${TCP_WRAPPERS:L} == "yes"
CPPFLAGS+=	-DLIBWRAP
DPADD+=		${LIBWRAP}
LDADD+=		-lwrap
.endif

#.if ${SKEY:L} == "yes"
#CPPFLAGS+=	-DSKEY
#DPADD+=	${SKEY}
#LDADD+=	-lskey
#.endif
