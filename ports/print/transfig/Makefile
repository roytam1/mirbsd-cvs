# $MirOS: ports/print/transfig/Makefile,v 1.8 2008/03/09 19:16:07 tg Exp $
# $OpenBSD: Makefile,v 1.25 2003/04/04 14:28:36 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	tools to convert Xfig's .fig files
VERSION=	3.2.5
DISTNAME=	transfig.${VERSION}
DASH_VER=	0
PKGNAME=	transfig-${VERSION}-${DASH_VER}
CATEGORIES=	print
MASTER_SITES=	http://www.xfig.org/software/xfig/${VERSION}/

LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		png.2::graphics/png
RUN_DEPENDS=	:ghostscript-*:print/ghostscript/artifex \
		:netpbm->=9.19:graphics/netpbm

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake
USE_X11=		Yes

NO_REGRESS=		Yes

.include <bsd.port.mk>
