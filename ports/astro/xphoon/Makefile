# $MirOS: ports/astro/xphoon/Makefile,v 1.4 2007/04/04 17:46:36 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/05/18 08:45:33 xsa Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	set the root window to the moon in its current phase
DISTNAME=	xphoon
PKGNAME=	xphoon-91.9.18-0
CATEGORIES=	astro x11
MASTER_SITES=	${MASTER_SITE_R5CONTRIB}
EXTRACT_SUFX=	.tar.Z

PERMIT_PACKAGE_CDROM=   "Cannot sell."
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= "Cannot sell."
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE= imake
USE_X11=	Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
