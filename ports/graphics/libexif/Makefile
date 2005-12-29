# $MirOS: ports/graphics/libexif/Makefile,v 1.5 2005/07/07 21:21:46 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2003/01/21 02:21:59 naddy Exp $

COMMENT=		"extract digital camera info tags from JPEG images"
DISTNAME=		libexif-0.6.13
CATEGORIES=		graphics
HOMEPAGE=		http://sourceforge.net/projects/libexif/

# GNU LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libexif/}

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ENV+=		ac_cv_path_DOXYGEN=false
MODULES+=		devel/pkgconfig

pre-configure:
	@cd ${WRKSRC} && touch AUTHORS NEWS ChangeLog ABOUT-NLS COPYING

.include <bsd.port.mk>
