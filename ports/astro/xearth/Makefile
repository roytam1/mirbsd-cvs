# $MirOS: ports/astro/xearth/Makefile,v 1.3 2007/04/04 17:46:36 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2002/10/24 16:21:35 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	set the root window to the image of earth
DISTNAME=	xearth-1.1
CATEGORIES=	astro x11
MASTER_SITES=	ftp://cag.lcs.mit.edu/pub/tuna/


PERMIT_PACKAGE_CDROM=   "Cannot sell."
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= "Cannot sell."
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE= imake
USE_X11=	Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
