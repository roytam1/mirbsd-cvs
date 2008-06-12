# $MirOS$

PROG=		vnkeygen
SRCS=		${PROG}.c pkcs5_pbkdf2.c
MAN=		${PROG}.8
NOMAN=		Yes
BINDIR=		/usr/sbin

DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto

.include <bsd.prog.mk>
