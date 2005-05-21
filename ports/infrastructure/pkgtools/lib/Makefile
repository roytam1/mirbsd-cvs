# $MirOS: ports/infrastructure/pkgtools/lib/Makefile,v 1.1.7.1 2005/03/18 15:47:16 tg Exp $
# $OpenBSD: Makefile,v 1.5 2001/04/08 16:45:47 espie Exp $

LIB=		install
SRCS=		exec.c file.c global.c pen.c plist.c pwarnx.c rcdb.c str.c
CPPFLAGS+=	${DEBUG}
NOPIC=		yes

.if defined(NEED_COMPAT)
SRCS+=		bsd-arc4random.c mktemp.c strtoll.c
.PATH:	${.CURDIR}/../mbcompat
.endif

.if defined(INSTALLMANS)
install: maninstall
.endif

install:
	# Nothing to do...

.include <bsd.lib.mk>
