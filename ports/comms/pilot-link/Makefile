# $MirOS: ports/comms/pilot-link/Makefile,v 1.5 2008/05/07 22:47:55 tg Exp $
# $OpenBSD: Makefile,v 1.31 2003/10/07 17:17:31 fgsch Exp $

COMMENT=	PalmPilot communication utilities

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

FLAVOURS=	debug
FLAVOUR?=

USE_GMAKE=	Yes
CONFIGURE_STYLE= autoconf no-autoheader
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS= --enable-static \
		--with-perl5="/usr/bin/perl" \
		--without-itcl \
		--without-python \
		--without-java

.if ${FLAVOUR:L:Mdebug} 
LIB_DEPENDS=	tk83::x11/tk/8.3
.else
CONFIGURE_ARGS+= --without-tk
.endif

MODGNU_RECURSE_DIRS=	${WRKSRC}/scripts ${WRKSRC}

MODULES=	converters/libiconv

USE_CXX=yes

post-extract:
	echo "include(libtool.m4)" >  ${WRKSRC:Q}/aclocal.m4

.include <bsd.port.mk>
