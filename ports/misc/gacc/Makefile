# $MirOS: ports/misc/gacc/Makefile,v 1.5 2006/09/14 00:11:14 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/06/20 08:14:52 kevlo Exp $

BROKEN=			gettext problems

COMMENT=		personal accounts manager

VERSION=		0.7.5
DASH_VER=		1
DISTNAME=		gacc_${VERSION}.orig
PKGNAME=		gacc-${VERSION}-${DASH_VER}
CATEGORIES=		misc productivity

HOMEPAGE=		http://tnemeth.free.fr/projets/gAcc-en.html


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gacc/}

LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1

USE_GMAKE=		Yes
USE_X11=		Yes

MODULES=		devel/gettext

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		no

CONFIGURE_ARGS=		--datadir=${PREFIX}/share/examples/gacc
WRKDIST=		${WRKDIR}/gacc-${VERSION}.orig

.include <bsd.port.mk>
