# $MirOS: ports/games/bzflag/Makefile,v 1.2 2005/07/07 21:20:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/02/25 02:35:15 naddy Exp $

BROKEN=		doesn't respect CXXFLAGS, problems loading data files

COMMENT=	"graphical multiplayer 3-d tank war game"
DISTNAME=	bzflag-1.10.4.20040125
PKGNAME=	bzflag-1.10.4-0
CATEGORIES=	games x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=bzflag/}

HOMEPAGE=	http://www.bzflag.org/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=gnu

post-extract:
	@sed -e 's|@LINUX_TRUE@||g ; s|@LINUX_FALSE@|#|g' \
		${WRKSRC}/src/platform/Makefile.in > \
		${WRKSRC}/src/platform/Makefile.sed
	@mv ${WRKSRC}/src/platform/Makefile.sed \
		${WRKSRC}/src/platform/Makefile.in

.include <bsd.port.mk>
