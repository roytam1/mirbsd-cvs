# $MirOS: ports/misc/gacc/Makefile,v 1.4 2006/02/09 11:12:06 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/06/20 08:14:52 kevlo Exp $

COMMENT=			personal accounts manager

VERSION=	0.7.5
DISTNAME=	gacc_${VERSION}.orig
PKGNAME=	gacc-${VERSION}-0
CATEGORIES=	misc productivity

HOMEPAGE=	http://tnemeth.free.fr/projets/gAcc-en.html


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gacc/}

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

USE_GMAKE=	Yes
USE_X11=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--datadir=${PREFIX}/share/examples/gacc

WRKDIST=        ${WRKDIR}/gacc-${VERSION}.orig

.include <bsd.port.mk>
