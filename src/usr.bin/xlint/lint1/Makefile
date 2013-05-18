# $MirOS: src/usr.bin/xlint/lint1/Makefile,v 1.2 2005/03/13 18:34:09 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/01/05 02:55:28 espie Exp $
# $NetBSD: Makefile,v 1.3 1995/07/04 01:53:05 cgd Exp $

PROG=		lint1
SRCS=		cgram.y decl.c emit.c emit1.c err.c func.c init.c \
		main1.c mem.c mem1.c scan.l tree.c
NOMAN=		yes
LDADD+=		-ll
DPADD+=		${LIBL}
CPPFLAGS+=	-I.
LINTFLAGS=	-aehpz
BINDIR=		/usr/libexec

.include <bsd.prog.mk>
