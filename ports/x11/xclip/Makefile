# $OpenBSD: Makefile,v 1.1.1.1 2004/04/18 23:24:01 jolan Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			command line interface to X selections
DISTNAME=		xclip-0.08
CATEGORIES=		x11
MASTER_SITES=		${HOMEPAGE}
HOMEPAGE=		http://people.debian.org/~kims/xclip/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

NO_REGRESS=		yes
USE_X11=		yes
CONFIGURE_STYLE=	imake

WRKDIST=		${WRKDIR}/xclip

.include <bsd.port.mk>
