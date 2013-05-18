# $MirOS: ports/x11/ion/Makefile,v 1.2 2005/07/07 21:28:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2003/10/08 17:13:16 sturm Exp $

BROKEN=		actually _needs_ libltdl, huh

# hah, friendly? not to porters, at least.
COMMENT=			light, keyboard friendly window manager
V=		20040316
DV=		-1
DISTNAME=	ion-3ds-${V}${DV}
PKGNAME=	ion-$V-0
HOMEPAGE=	http://modeemi.cs.tut.fi/~tuomov/ion/
CATEGORIES=	x11
MASTER_SITES=	http://modeemi.cs.tut.fi/~tuomov/ion/dl/ \
		ftp://rt.fm/pub/ion/

# GNU LGPLv2.1 or newer
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
USE_X11=		Yes

LIB_DEPENDS+=		lua.5::lang/lua
MAKE_ENV+=		SYSCONFDIR="$(SYSCONFDIR)"

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

NO_REGRESS=		Yes

.include <bsd.port.mk>
