# $MirOS: ports/devel/libglade/Makefile,v 1.11 2007/06/21 17:01:38 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/12/22 06:31:05 espie Exp $

COMMENT=		library for loading GLADE interface files at runtime
VSN=			2.6.1
DISTNAME=		libglade-${VSN}
PKGNAME=		libglade2-${VSN}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://www.gnome.org
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libglade/2.6/}
EXTRACT_SUFX=           .tar.bz2

# GNU LGPLv2.0
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig
LIB_DEPENDS=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
			xml2::textproc/libxml

USE_X11=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 	--enable-static
CONFIGURE_ARGS+= 	--with-xml-catalog=${LOCALBASE}/db/xmlcatalog

# Build the libglade-convert script even if we don't have Python.
# Other ports that need it will have to have a python-expat *_DEPENDS.
post-install:
	@sed 's,@PYTHON@,${LOCALBASE}/bin/python,' \
	    ${WRKSRC}/libglade-convert.in \
	    >${PREFIX}/bin/libglade-convert

.include <bsd.port.mk>
