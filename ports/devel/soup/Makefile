# $MirOS: ports/devel/soup/Makefile,v 1.8 2006/06/03 14:10:28 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2003/12/04 23:07:25 pvalchev Exp $

COMMENT=			SOAP (Simple Object Access Protocol) implementation in C

DISTNAME=		soup-0.7.11
PKGNAME=		${DISTNAME}-4
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/soup/0.7/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		glib.1.2,gmodule.1.2::devel/glib1 \
			popt::devel/popt \
			xml2.2.6::textproc/libxml

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-libxml=2
CONFIGURE_ARGS+=	--disable-glib2
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
