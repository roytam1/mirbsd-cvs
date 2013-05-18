# $MirOS: ports/graphics/xsane/Makefile,v 1.2 2005/03/30 18:13:33 bsiegert Exp $
# Original from: Antoine Jacoutot <ajacoutot@lphp.org>

COMMENT=	"scanner frontend for SANE"

DISTNAME=	xsane-0.95
CATEGORIES=	graphics

MASTER_SITES=	ftp://ftp.sane-project.org/pub/sane/xsane/ \
		http://gd.tuwien.ac.at/hci/sane/xsane/ \
		ftp://gd.tuwien.ac.at/hci/sane/xsane/ \
		ftp://ftp.no.mostang.com/pub/sane/xsane/ \
		ftp://ftp2.sane-project.org/pub/sane/xsane/ \
		ftp://sunsite.uio.no/pub/sane/xsane/

HOMEPAGE=	http://www.xsane.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext graphics/png
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1 \
		jpeg.62::graphics/jpeg \
		tiff.35::graphics/tiff 

USE_X11=			Yes
USE_GMAKE=			Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader

CONFIGURE_ARGS+=	--disable-gtk2 \
			--disable-gimp2
CONFIGURE_ARGS+=	--disable-gimp

.include <bsd.port.mk>
