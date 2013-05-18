# $MirOS: ports/textproc/sablotron/Makefile,v 1.6 2008/05/07 22:48:43 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/02/29 00:18:19 avsm Exp $

COMMENT=		fast, compact and portable XSL/XSLT processor
VSN=			1.0.1
DISTNAME=		Sablot-${VSN}
PKGNAME=		sablotron-${VSN}-${DASH_VER}
CATEGORIES=    		textproc
HOMEPAGE=		http://www.gingerall.com/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://download-1.gingerall.cz/download/sablot/

MODULES+=		converters/libiconv
MODULES+=		textproc/expat
BUILD_DEPENDS+=		:p5-XML-Parser-*:textproc/p5-XML-Parser

USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/tools ${WRKSRC}

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV+=		SABLOT_GPL=1
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} --enable-static \
			--enable-debugger --with-expat-prefix=${EXPAT_PREFIX:Q} \
			--with-iconv-prefix=${ICONV_PREFIX:Q} --with-readline \
			--with-html-dir=${PREFIX:Q}/share/doc/sablotron

.include <bsd.port.mk>
