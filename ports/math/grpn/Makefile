# $MirOS: ports/math/grpn/Makefile,v 1.2 2005/03/30 18:13:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2003/11/02 19:58:21 margarida Exp $

COMMENT=	"graphical reverse polish notation calculator"

DISTNAME=	grpn-1.1.2
CATEGORIES=	math x11

HOMEPAGE=	http://lashwhip.com/grpn.html

MASTER_SITES=	http://lashwhip.com/grpn/ \
		ftp://lashwhip.com/pub/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

ALL_TARGET=

USE_X11=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/grpn ${PREFIX}/bin

.include <bsd.port.mk>
