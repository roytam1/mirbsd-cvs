# $MirOS: ports/graphics/png/Makefile,v 1.5 2006/09/14 00:10:04 tg Exp $
# $OpenBSD: Makefile,v 1.46 2004/07/06 22:17:48 brad Exp $

COMMENT=		library for manipulating PNG images
DISTNAME=		libpng-1.2.12
PKGNAME=		${DISTNAME:S/lib//}-0
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libpng/}
HOMEPAGE=		http://www.libpng.org/pub/png/libpng.html

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FAKE_FLAGS=		DESTDIR="${WRKINST}" PREFIX="${PREFIX}"
MAKE_FILE=		scripts/makefile.openbsd
REGRESS_TARGET=		test

.include <bsd.port.mk>
