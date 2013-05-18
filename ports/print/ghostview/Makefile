# $MirOS: ports/print/ghostview/Makefile,v 1.4 2007/04/13 19:27:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2003/06/04 01:17:50 margarida Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	X11 front-end for ghostscript

DISTNAME=	ghostview-1.5
PKGNAME=	${DISTNAME}-1
CATEGORIES=	print

MASTER_SITES=	${MASTER_SITE_GNU:=ghostview/}

# License: GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

RUN_DEPENDS=    :ghostscript-*:print/ghostscript/artifex

CONFIGURE_STYLE=	imake
USE_X11=		Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
