# $MirOS$
# $OpenBSD: Makefile,v 1.5 2001/04/08 16:45:47 espie Exp $

LIB=		install
SRCS=		exec.c file.c global.c pen.c plist.c pwarnx.c rcdb.c str.c
CPPFLAGS+=	${DEBUG}
NOPIC=		yes

.if defined(INSTALLMANS)
install: maninstall
.endif

install:
	# Nothing to do...

.include <bsd.lib.mk>
