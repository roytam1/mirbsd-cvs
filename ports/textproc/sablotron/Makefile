# $OpenBSD: Makefile,v 1.17 2004/02/29 00:18:19 avsm Exp $

COMMENT=			fast, compact and portable XSL/XSLT processor

V=		1.0.1
DISTNAME=	Sablot-${V}
PKGNAME=	sablotron-${V}-0
CATEGORIES=    	textproc

HOMEPAGE=	http://www.gingerall.com/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://download-1.gingerall.cz/download/sablot/

MODULES=	converters/libiconv
LIB_DEPENDS=	expat.2::textproc/expat
BUILD_DEPENDS=	:p5-XML-Parser-*:textproc/p5-XML-Parser

USE_GMAKE=	Yes
AUTOCONF_NEW=	Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/tools

CONFIGURE_STYLE=gnu
CONFIGURE_ENV=	SABLOT_GPL=1
CONFIGURE_ARGS=	${CONFIGURE_SHARED} --enable-static \
		--enable-debugger --with-expat-prefix=${LOCALBASE} \
		--with-iconv-prefix=${ICONV_PREFIX} --with-readline \
		--with-html-dir=${PREFIX}/share/doc/sablotron

.include <bsd.port.mk>
