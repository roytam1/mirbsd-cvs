# $OpenBSD: Makefile,v 1.33 2003/05/14 13:09:52 margarida Exp $

COMMENT=			front-end to various audio players

DISTNAME=		gqmpeg-0.20.0		
CATEGORIES=		audio

HOMEPAGE=		http://gqmpeg.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gqmpeg/}

MODULES=		devel/gettext graphics/png

RUN_DEPENDS+=		:mpg321-*:audio/mpg321

LIB_DEPENDS=		gdk_pixbuf.2::graphics/gdk-pixbuf
USE_CXX=		Yes

CONFIGURE_STYLE=	gnu
AUTOCONF_NEW=		Yes

DOCS=			FAQ README SKIN-SPECS-V1 \
			plugin/README.plugin

post-install:
	cd ${WRKSRC} && \
	    ${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gqmpeg && \
	    ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/gqmpeg

.include <bsd.port.mk>
