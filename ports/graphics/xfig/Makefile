# $MirOS: ports/graphics/xfig/Makefile,v 1.3 2006/09/14 00:10:10 tg Exp $
# $OpenBSD: Makefile,v 1.27 2004/02/25 02:35:16 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			CAD drawing program for X11
VERSION=	3.2.4
DISTNAME=	xfig.${VERSION}.full
PKGNAME=	xfig-${VERSION}-0
CATEGORIES=	graphics x11
HOMEPAGE=	http://www.xfig.org/

# apparently MIT-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.xfig.org/xfigdist/ \
		ftp://www-epb.lbl.gov/xfig/ \
		ftp://www-epb.lbl.gov/xfig/previous_versions/

LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		png.2::graphics/png \
		Xaw3d.6.1::x11/Xaw3d
RUN_DEPENDS=	::print/transfig

MAKE_FLAGS+=	XAPPLOADDIR="${PREFIX}/lib/X11/app-defaults" \
		XFIGDOCDIR="${PREFIX}/share/doc/xfig" \
		XFIGLIBDIR="${PREFIX}/lib/X11/xfig"
FAKE_FLAGS+=	DESTDIR="${WRKINST}" ${MAKE_FLAGS}

CONFIGURE_STYLE=imake

INSTALL_TARGET=	install install.all

WRKDIST=	${WRKDIR}/xfig.${VERSION}

NO_REGRESS=	Yes

.include <bsd.port.mk>
