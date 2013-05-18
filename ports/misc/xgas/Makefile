# $MirOS: ports/misc/xgas/Makefile,v 1.4 2007/04/18 18:34:43 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2003/04/14 15:02:09 wilfried Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	animated simulation of an ideal gas

DISTNAME=	xgas
PKGNAME=        xgas-1.0-0
CATEGORIES=     misc chemistry

MASTER_SITES=	${MASTER_SITE_SUNSITE:=X11/demos/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=imake
USE_X11=	Yes

NO_REGRESS=	Yes

post-install:
	@chmod 755 ${PREFIX}/bin/xgas
	@chown bin:bin ${PREFIX}/bin/xgas

.include <bsd.port.mk>
