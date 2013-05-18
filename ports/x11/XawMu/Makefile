# $MirOS: ports/x11/XawMu/Makefile,v 1.2 2005/07/07 21:29:30 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2003/12/30 23:16:01 pvalchev Exp $

COMMENT=			modern look Athena widgets
VERSION=		1.5
DISTNAME=		XawM-${VERSION}u
PKGNAME=		XawMu-${VERSION}-0
CATEGORIES=		x11 devel
HOMEPAGE=		http://xawm.sourceforge.net/
MASTER_SITES=		http://siag.nu/pub/widgets/

# X11/badly worded
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED}

NO_REGRESS=		Yes

.include <bsd.port.mk>
