# $MirOS$
# $OpenBSD: Makefile,v 1.29 2003/08/04 07:29:22 hin Exp $

PROG=	passwd
SRCS=	getpwent.c local_passwd.c passwd.c pwd_check.c pwd_gensalt.c
.PATH:  ${.CURDIR}/../../lib/libc/gen
DPADD+=	${LIBUTIL}
LDADD+=	-lutil

CFLAGS_getpwent.o=-UYP

BINMODE=4555
BINOWN=root

.include <bsd.prog.mk>
