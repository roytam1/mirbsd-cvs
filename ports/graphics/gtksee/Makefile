# $MirOS: ports/graphics/gtksee/Makefile,v 1.3 2006/02/09 09:35:54 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/04/18 23:20:28 jcs Exp $

COMMENT=	"image viewer similar to ACDSee for Windows"

DISTNAME=	gtksee-0.5.0
CATEGORIES=	graphics

MASTER_SITES=	http://www.physik.TU-Berlin.DE/~ibex/ports/distfiles/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1 \
		jpeg.62::graphics/jpeg \
		tiff.35::graphics/tiff
RUN_DEPENDS=	:bzip-*:archivers/bzip \
		:bzip2-*:archivers/bzip2
MODULES+=		graphics/png

USE_X11=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+=--with-im-libs="${PREFIX}/lib" \
		--with-im-incs="${PREFIX}/include"

.include <bsd.port.mk>
