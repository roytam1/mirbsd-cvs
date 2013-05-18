# $MirOS: ports/games/bombermaze/Makefile,v 1.3 2006/02/09 11:11:34 tg Exp $
# $OpenBSD: Makefile,v 1.6 2002/12/22 08:00:17 pvalchev Exp $

IGNORE=		"might be broken, used to use Libtool"

COMMENT=			Bomberman clone for GNOME
VERSION=		0.6.6
DISTNAME=		bombermaze-${VERSION}
CATEGORIES=		games x11
HOMEPAGE=		http://www.nongnu.org/bombermaze/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://savannah.nongnu.org/download/bombermaze/

MODULES=	devel/gettext
LIB_DEPENDS=	gdk_pixbuf.2::graphics/gdk-pixbuf \
		audiofile.0::devel/libaudiofile \
		glib.1,gmodule.1::devel/glib1\
	 	gif.5::graphics/libungif \
		art_lgpl.4,gnome.36,gnomeui.46,gnomesupport.0::x11/gnome/libs

USE_GMAKE=		Yes
USE_X11=		Yes
USE_CXX=		Yes
NO_REGRESS=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV=		LIBS="-pthread"

.include <bsd.port.mk>
