# $MirOS: ports/net/rrdtool/Makefile,v 1.3 2006/02/09 11:15:06 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/02/15 20:59:58 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			system to store and display time-series data
VERSION=	1.0.46
DISTNAME=	rrdtool-${VERSION}
CATEGORIES=     net
MASTER_SITES=	http://people.ee.ethz.ch/~oetiker/webtools/rrdtool/pub/ \
		ftp://ftp.sunet.se/pub/network/monitoring/rrdtool/ \
		http://ftp.sunet.se/pub/network/monitoring/rrdtool/
HOMEPAGE=	http://people.ee.ethz.ch/~oetiker/webtools/rrdtool/

# GPL
PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes 
PERMIT_DISTFILES_FTP=	Yes 

SUBST_VARS=	VERSION

FLAVORS=	tcl
FLAVOR?=

MODULES+=		graphics/png
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED} --enable-static \
		--enable-local-libpng \
		--enable-local-zlib
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/config ${WRKSRC}/contrib/php4

.if ${FLAVOR:L:Mtcl}
LIB_DEPENDS+=	tcl84::lang/tcl/8.4
USE_GMAKE=	Yes
CONFIGURE_ARGS+= --with-tcllib="${LOCALBASE}/lib/tcl8.4"
CFLAGS+=	-I${LOCALBASE}/include/tcl8.4
.else
CONFIGURE_ARGS+= --without-tcllib
.endif

.if ${FLAVOR:L:Mtcl}
post-install:
	cd ${WRKSRC} && ${MAKE} site-tcl-install
.endif

pre-patch:
	for a in acconfig.h aclocal.m4 config.h.in install-sh \
	    missing mkinstalldirs stamp-h.in; do \
		cp ${WRKSRC}/config/$$a ${WRKSRC}/; done

.include <bsd.port.mk>
