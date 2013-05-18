# $OpenBSD: Makefile,v 1.8 2004/05/08 06:44:19 sturm Exp $

COMMENT=			XML security library
COMMENT-docs=			XML security library documentation

VERSION=	1.2.5
DISTNAME=	xmlsec1-${VERSION}
PKGNAME=	xmlsec-${VERSION}-0
PKGNAME-docs=	xmlsec-docs-${VERSION}-0
CATEGORIES=	security

HOMEPAGE=	http://www.aleksey.com/xmlsec/

# MIT Licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.aleksey.com/xmlsec/download/ \
		ftp://ftp.aleksey.com/pub/xmlsec/releases/ \
		ftp://ftp.xmlsoft.org/xmlsec/releases/ \
		ftp://ftp.rpmfind.net/pub/XML/xmlsec/releases/

MULTI_PACKAGES=		-docs
SUBPACKAGE?=

.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=		*
.endif

.if ${SUBPACKAGE} != "-docs"
MODULES=		converters/libiconv devel/pkgconfig
LIB_DEPENDS=		xslt.2::textproc/libxslt \
			gnutls.12::security/gnutls
.endif

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-gnutls="${LOCALBASE}"

REGRESS_DEPENDS=	::security/xmlsec
REGRESS_FLAGS=		ABS_BUILDDIR="${WRKSRC}"

.include <bsd.port.mk>
