# $MirOS: ports/x11/neXtaw/Makefile,v 1.4 2006/09/14 00:15:30 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/10/08 17:13:17 sturm Exp $

COMMENT=			libXaw widget set replacement with NeXTstep-like look
VERSION=		0.15.1
DISTNAME=		neXtaw-${VERSION}
CATEGORIES=		x11 devel
HOMEPAGE=		http://siag.nu/neXtaw/
MASTER_SITES=		http://siag.nu/pub/neXtaw/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# simple X11
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

NO_REGRESS=		Yes

post-install:
	${INSTALL_PROGRAM} ${WRKSRC}/programs/neXtclock/neXtclock \
	    ${PREFIX}/bin/

.include <bsd.port.mk>
