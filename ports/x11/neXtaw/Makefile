# $MirOS$
# $OpenBSD: Makefile,v 1.3 2003/10/08 17:13:17 sturm Exp $

COMMENT=		"libXaw widget set replacement with NeXTstep-like look"
VERSION=		0.15.1
DISTNAME=		neXtaw-${VERSION}
CATEGORIES=		x11 devel
HOMEPAGE=		http://siag.nu/neXtaw/
MASTER_SITES=		http://siag.nu/pub/neXtaw/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# simple X11
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV+=		CPPFLAGS="-I${X11BASE}/include"

NO_REGRESS=		Yes

post-install:
	${INSTALL_PROGRAM} ${WRKSRC}/programs/neXtclock/neXtclock \
	    ${PREFIX}/bin/

.include <bsd.port.mk>
