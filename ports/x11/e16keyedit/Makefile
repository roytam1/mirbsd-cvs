# $MirOS: ports/x11/e16keyedit/Makefile,v 1.3 2006/09/14 00:15:11 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/10/08 17:13:15 sturm Exp $

COMMENT=		edit enlightenment\'s keybindings

DISTNAME=		e16keyedit-0.2
CATEGORIES=     	x11


# X11
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.enlightenment.org/enlightenment/e16utils/

LIB_DEPENDS=		gdk_imlib.19::graphics/imlib \
			gtk.1.2,gdk.1.2::x11/gtk+1
RUN_DEPENDS=		:enlightenment-0.16*:x11/enlightenment

USE_X11=		Yes
USE_CXX=		Yes # depends on enlightenment, whose dependencies use CXX
NO_REGRESS=		Yes

.include <bsd.port.mk>
