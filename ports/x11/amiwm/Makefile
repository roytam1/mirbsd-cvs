# $OpenBSD: Makefile,v 1.2 2002/10/29 19:48:57 naddy Exp $

COMMENT=	"Amiga Workbench lookalike window manager"

VERSION=	0.20pl48
DISTNAME=	amiwm${VERSION}
PKGNAME=	amiwm-0.20.48-0
CATEGORIES=	x11

MASTER_SITES=	ftp://ftp.lysator.liu.se/pub/X11/wm/amiwm/

HOMEPAGE=	http://www.lysator.liu.se/~marcus/amiwm.html


PERMIT_PACKAGE_CDROM=	restrictive
PERMIT_PACKAGE_FTP=	restrictive
PERMIT_DISTFILES_CDROM=	restrictive
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE= 	gnu dest

NO_REGRESS=	Yes

.include <bsd.port.mk>
