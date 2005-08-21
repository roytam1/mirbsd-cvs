# $MirOS: ports/infrastructure/pkgtools/lib/Makefile,v 1.3 2005/05/21 17:15:40 tg Exp $
# $OpenBSD: Makefile,v 1.5 2001/04/08 16:45:47 espie Exp $

LIB=		install
SRCS=		exec.c file.c global.c pen.c plist.c pwarnx.c rcdb.c str.c
CPPFLAGS+=	${DEBUG}
NOPIC=		yes

.if defined(NEED_COMPAT)
SRCS+=		mktemp.c strtoll.c
.PATH: ${.CURDIR}/../mbcompat
.endif

install:

.include <bsd.lib.mk>
