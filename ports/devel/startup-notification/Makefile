# $MirOS: ports/devel/startup-notification/Makefile,v 1.2 2005/10/16 11:08:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2004/12/10 20:34:00 marcm Exp $

COMMENT=			library for tracking application startup

DISTNAME=		startup-notification-0.8
CATEGORIES=		devel x11 x11/gnome

HOMEPAGE=		http://www.freedesktop.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/startup-notification/0.8/}
EXTRACT_SUFX=		.tar.bz2

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
