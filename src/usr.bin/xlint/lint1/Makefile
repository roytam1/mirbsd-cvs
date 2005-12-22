# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/01/05 02:55:28 espie Exp $
# $NetBSD: Makefile,v 1.3 1995/07/04 01:53:05 cgd Exp $

PROG=		lint1
SRCS=		cgram.c decl.c emit.c emit1.c err.c func.c init.c \
		main1.c mem.c mem1.c scan.c tree.c
NOMAN=		yes
LDADD+=		-ll
DPADD+=		${LIBL}
YFLAGS=		-d
CPPFLAGS+=	-I.
LINTFLAGS=	-aehpz
CLEANFILES+=	y.tab.h cgram.c scan.c
BINDIR=		/usr/libexec

.include <bsd.prog.mk>
