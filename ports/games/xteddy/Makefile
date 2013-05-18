# $MirOS$
# $OpenBSD: Makefile,v 1.13 2004/01/31 21:32:18 pvalchev Exp $

COMMENT=		cuddlesome teddy for the X11 desktop
DISTNAME=		xteddy-2.0.2
CATEGORIES=		games
MASTER_SITES=		http://www.ITN.LiU.SE/~stegu/xteddy/
LIB_DEPENDS=		Imlib.19::graphics/imlib

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
USE_X11=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
NO_REGRESS=		Yes

post-patch:
	@perl -pi -e 's#/usr/share/xteddy#${PREFIX}/share/xteddy#g' \
	    ${WRKSRC}/{configure,xteddy.c}
	@perl -pi -e 's#!!PREFIX!!#${PREFIX}#g' ${WRKSRC}/{xtoys,xteddy_test}

.include <bsd.port.mk>
