# $MirOS: ports/graphics/libmng/Makefile,v 1.4 2006/01/11 17:30:16 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/12/23 23:50:56 brad Exp $

COMMENT=		"Multiple-image Network Graphics (MNG) reference library"
DISTNAME=		libmng-1.0.9
PKGNAME=		${DISTNAME}-1
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libmng/}
HOMEPAGE=		http://www.libmng.com/
LIB_DEPENDS=		jpeg::graphics/jpeg \
			lcms::graphics/lcms

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autogen no-autoheader
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

post-extract:
	cd ${WRKSRC}/makefiles && for f in configure.in Makefile.am; do \
		tr -d '\r' <$$f >../$$f; \
	done

.include <bsd.port.mk>
