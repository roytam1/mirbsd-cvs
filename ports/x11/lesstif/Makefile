# $MirOS$
# $OpenBSD: Makefile,v 1.49 2003/10/08 17:13:17 sturm Exp $
# $FreeBSD: Makefile,v 1.17 1998/03/28 14:12:55 steve Exp $

COMMENT=		API compatible clone of the Motif toolkit

DISTNAME=		lesstif-0.95.0
CATEGORIES=		x11
EXTRACT_SUFX=		.tar.bz2

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=lesstif/}
HOMEPAGE=		http://www.lesstif.org/


# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--enable-production
CONFIGURE_ARGS+=	--with-xdnd
CONFIGURE_ARGS+=	--disable-debug
CONFIGURE_ENV+=		AUTOMAKE_VERSION=${AUTOMAKE_VERSION}

.include <bsd.port.mk>
