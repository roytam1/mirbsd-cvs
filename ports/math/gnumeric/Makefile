# $MirOS: ports/math/gnumeric/Makefile,v 1.5 2007/08/18 22:32:02 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2004/12/22 06:02:26 marcm Exp $

COMMENT=		spreadsheet application for GNOME

VERSION=		1.7.11
DASH_VER=		1
DISTNAME=		gnumeric-${VERSION}
CATEGORIES=    		math x11/gnome

HOMEPAGE=		http://www.gnome.org/projects/gnumeric/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnumeric/1.7/}

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		::textproc/p5-XML-Parser
B_R_DEPENDS+=		::textproc/scrollkeeper
LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
LIB_DEPENDS+=		gnomeprintui-2-2::x11/gnome/libgnomeprintui
LIB_DEPENDS+=		gsf-1.11,gsf-gnome-1.11::devel/libgsf,-gnome
LIB_DEPENDS+=		goffice-0::x11/gnome/goffice

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-gnome
CONFIGURE_ARGS+=	--without-gda
CONFIGURE_ARGS+=	--without-gb
CONFIGURE_ARGS+=	--without-guile
CONFIGURE_ARGS+=	--without-psiconv
CONFIGURE_ARGS+=	--without-paradox
CONFIGURE_ARGS+=	--without-long-double
CONFIGURE_ARGS+=	--without-perl
CONFIGURE_ARGS+=	--without-python
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnumeric
SUBST_VARS=		VERSION

post-patch:
	@ln -s /usr/bin/true ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
