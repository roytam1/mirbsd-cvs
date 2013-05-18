# $MirOS: ports/graphics/sng/Makefile,v 1.6 2007/02/22 22:57:51 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/04/28 09:25:42 wilfried Exp $

COMMENT=		PNG to ASCII compiler and decompiler
DISTNAME=		sng-1.0.2
DASH_VER=		1
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sng/}
HOMEPAGE=		http://sng.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# zlib license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		yes
MODULES+=		graphics/png

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-png-inc=${LOCALBASE:Q}/include/libpng \
			--with-png-lib=${LOCALBASE:Q}/lib

NO_REGRESS=		yes

.include <bsd.port.mk>
