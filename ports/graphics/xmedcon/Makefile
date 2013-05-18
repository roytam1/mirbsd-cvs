# $MirOS: ports/graphics/xmedcon/Makefile,v 1.2 2005/03/30 18:13:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2003/01/18 22:37:41 brad Exp $

COMMENT=			medical image conversion
DISTNAME=	xmedcon-0.5.2
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=xmedcon/}
HOMEPAGE=	http://xmedcon.sourceforge.net

LIB_DEPENDS=	gtk.1.2::x11/gtk+1 \
		gdk_pixbuf::graphics/gdk-pixbuf
		
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static 

.include <bsd.port.mk>
