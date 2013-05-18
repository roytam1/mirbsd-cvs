# $MirOS: ports/x11/gnome/libbonobo/Makefile,v 1.4 2006/02/09 11:15:43 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/12/15 13:57:56 alek Exp $

COMMENT=		"GNOME component and compound document system" 

DISTNAME=		libbonobo-2.10.1
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libbonobo/2.10/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		ORBit-2,ORBitCosNaming-2::devel/ORBit \
			xml2.2.6::textproc/libxml

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--disable-gtk-doc

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/libbonobo; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/libbonobo/

.include <bsd.port.mk>
