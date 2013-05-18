# $MirOS: ports/devel/ORBit/Makefile,v 1.6 2006/02/09 11:11:16 tg Exp $
# $OpenBSD: Makefile,v 1.14 2004/12/10 20:33:58 marcm Exp $

COMMENT=			high-performance CORBA Object Request Broker
DISTNAME=		ORBit2-2.12.4
CATEGORIES=		devel
HOMEPAGE=		http://www.labs.redhat.com/orbit/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/ORBit2/2.12/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		IDL-2::devel/libIDL \
			gmodule-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0::devel/glib\
			popt::devel/popt

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-indent

# XXX you can't compile this with an existing ORBit installed...
# LDFLAGS="-L${LOCALBASE}/lib" messes it up but is needed to detect popt

.include <bsd.port.mk>
