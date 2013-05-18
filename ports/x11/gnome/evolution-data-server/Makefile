# $MirOS: ports/x11/gnome/evolution-data-server/Makefile,v 1.1.7.1 2005/03/18 16:00:23 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/12/11 06:03:08 marcm Exp $

COMMENT=		"data backends for the Evolution mail/PIM suite"

DISTNAME=		evolution-data-server-1.0.3
CATEGORIES=		x11/gnome databases

HOMEPAGE=		http://www.gnome.org
MAINTAINER=		Marc Matteo <marcm@openbsd.org>

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/evolution-data-server/1.0/}
EXTRACT_SUFX=           .tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:bison-*:devel/bison \
			:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS= 		gnome-2::x11/gnome/libgnome \
			lber.7,ldap.7::databases/openldap \
			soup-2.2.7.0::devel/libsoup

USE_GMAKE=		Yes
YACC=			bison
CONFIGURE_STYLE= 	autogen
AUTOGEN=		${SHELL} ${FILESDIR}/autogen.sh
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/libdb/dist
CONFIGURE_ARGS+= 	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/evolution-data-server
CONFIGURE_ARGS+= 	--with-openldap=${LOCALBASE}

post-configure:
	cp ${WRKSRC}/libtool ${WRKSRC}/libdb/dist

.include <bsd.port.mk>
