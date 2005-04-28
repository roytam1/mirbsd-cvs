# $MirOS: ports/graphics/libmng/Makefile,v 1.1.7.1 2005/03/18 15:46:59 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/12/23 23:50:56 brad Exp $

COMMENT=	"Multiple-image Network Graphics (MNG) reference library"
DISTNAME=	libmng-1.0.9
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libmng/}
HOMEPAGE=	http://www.libmng.com/
LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		lcms::graphics/lcms

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SEPARATE_BUILD=		simple
CONFIGURE_STYLE=	autogen no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
INSTALL_TARGET=		MANS= install

post-extract:
	cd ${WRKSRC}/makefiles && for f in configure.in Makefile.am; do \
		tr -d '\r' <$$f >../$$f; \
	done

post-install:
	cd ${WRKSRC}/doc/man && \
		${INSTALL_MAN} libmng.3 ${PREFIX}/man/man3/ && \
		${INSTALL_MAN} jng.5 mng.5 ${PREFIX}/man/man5/

.include <bsd.port.mk>
