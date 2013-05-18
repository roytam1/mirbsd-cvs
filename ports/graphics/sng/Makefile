# $MirOS: ports/graphics/sng/Makefile,v 1.4 2006/09/14 00:10:07 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/04/28 09:25:42 wilfried Exp $

COMMENT=		PNG to ASCII compiler and decompiler
DISTNAME=		sng-1.0.2
DASH_VER=		1
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sng/}
HOMEPAGE=		http://sng.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# zlib license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		yes
MODULES+=		graphics/png

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-png-inc=${LOCALBASE}/include/libpng \
			--with-png-lib=${LOCALBASE}/lib \
			--disable-dependency-tracking

NO_REGRESS=		yes

.include <bsd.port.mk>
