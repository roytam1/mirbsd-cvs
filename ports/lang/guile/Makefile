# $MirOS: ports/lang/guile/Makefile,v 1.5 2006/09/14 00:10:20 tg Exp $
# $OpenBSD: Makefile,v 1.20 2002/12/29 20:41:07 fgsch Exp $

COMMENT=		GNU Ubiquitous Intelligent Language for Extension

VERSION=		1.8.2
DISTNAME=		guile-${VERSION}
CATEGORIES=		lang
MASTER_SITES=		${MASTER_SITE_GNU:=guile/}

HOMEPAGE=		http://www.gnu.org/software/guile/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		ltdl::devel/libtool
LIB_DEPENDS+=		gmp::devel/gmp
LIB_DEPENDS+=		readline::devel/libreadline
MODULES+=		devel/gettext

CONFIGURE_STYLE=	autoconf # no-autoheader
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/guile-readline
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

post-extract:
	rm -rf ${WRKSRC}/libltdl

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/aclocal
	${INSTALL_DATA} ${WRKSRC}/guile-config/guile.m4 ${PREFIX}/share/aclocal
	mv ${WRKINST}/1.8/ice9/* ${PREFIX}/share/guile/1.8/ice-9/

.include <bsd.port.mk>
