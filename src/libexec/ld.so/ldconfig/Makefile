# $MirOS: src/libexec/ld.so/ldconfig/Makefile,v 1.3 2006/06/30 18:11:01 tg Exp $
# $OpenBSD: Makefile,v 1.7 2006/05/12 23:20:52 deraadt Exp $
# $NetBSD: Makefile,v 1.10 1995/03/06 04:24:41 cgd Exp $

PROG=		ldconfig
SRCS=		ldconfig.c shlib.c etc.c prebind_delete.c debug.c prebind.c \
		library.c sod.c
CPPFLAGS+=	-I${.CURDIR}/..
LDSTATIC=	-static
BINDIR=		/sbin
MAN=		ldconfig.8

.include <bsd.prog.mk>
