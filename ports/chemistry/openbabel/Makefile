# $MirOS: ports/x11/libxklavier/Makefile,v 1.5 2008/07/27 14:02:44 bsiegert Exp $

COMMENT=		toolbox for working with molecule files

VERSION=		2.2.3
DISTNAME=		openbabel-${VERSION}
CATEGORIES=		chemistry

HOMEPAGE=		http://www.openbabel.org/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=openbabel/}

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		xml2::textproc/libxml
MODULES+=		devel/pkgconfig

USE_CXX=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_VERSION=	2.63

pre-patch:
	rm -f ${WRKSRC}/autoconf/l*.m4 ${WRKSRC}/ltmain.sh ${WRKSRC}/libtool.m4

.include <bsd.port.mk>
