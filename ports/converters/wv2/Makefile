# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/02/25 02:35:15 naddy Exp $

COMMENT=	library providing routines to access Microsoft Word/Excel files

DISTNAME=	wv2-0.2.1
CATEGORIES=	converters
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=wvware/}
EXTRACT_SUFX=	.tar.bz2

HOMEPAGE=	http://wvware.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext devel/pkgconfig

LIB_DEPENDS+=	glib-2.0.0.0,glib-2.0.0.0::devel/glib \
		xml2::textproc/libxml \
		gsf-1::devel/libgsf,no_gnome

USE_GMAKE= Yes
USE_X11=	Yes # depends on libgsf, which needs X11
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --disable-debug \
		 --enable-static \
		 --with-libiconv="${ICONV_PREFIX}"

NO_REGRESS=	Yes

.include <bsd.port.mk>
