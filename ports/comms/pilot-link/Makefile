# $MirOS: ports/comms/pilot-link/Makefile,v 1.2 2005/07/07 21:18:02 bsiegert Exp $
# $OpenBSD: Makefile,v 1.31 2003/10/07 17:17:31 fgsch Exp $

COMMENT=			PalmPilot communication utilities

VERSION=	0.9.5
DISTNAME=	pilot-link.${VERSION}
PKGNAME=	pilot-link-${VERSION}-1
CATEGORIES=	comms palm
EXTRACT_SUFX=	.tar.bz2

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes


HOMEPAGE=	http://www.pilot-link.org

MASTER_SITES=	${HOMEPAGE}/source/

FLAVORS=	debug
FLAVOR?=

USE_GMAKE=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS= --enable-static \
		--with-perl5="/usr/bin/perl" \
		--without-itcl \
		--without-python \
		--without-java

.if ${FLAVOR:L:Mdebug} 
LIB_DEPENDS=	tk83::x11/tk/8.3
.else
CONFIGURE_ARGS+= --without-tk
.endif

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/scripts

MODULES=	converters/libiconv

USE_CXX=yes

.include <bsd.port.mk>
