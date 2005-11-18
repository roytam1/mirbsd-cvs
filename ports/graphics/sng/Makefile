# $MirOS: ports/graphics/sng/Makefile,v 1.1.7.1 2005/03/18 15:47:09 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/04/28 09:25:42 wilfried Exp $

COMMENT=		"PNG to ASCII compiler and decompiler"
DISTNAME=		sng-1.0.2
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sng/}
HOMEPAGE=		http://sng.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# zlib license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		png::graphics/png
USE_X11=		yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--with-png-inc=${LOCALBASE}/include/libpng \
			--with-png-lib=${LOCALBASE}/lib

NO_REGRESS=		yes

.include <bsd.port.mk>
