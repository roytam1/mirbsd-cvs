# $MirOS: ports/devel/libunicode/Makefile,v 1.1.7.1 2005/03/18 15:44:54 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2002/12/19 01:19:52 margarida Exp $

COMMENT=			library for manipulating Unicode characters and strings
DISTNAME=	libunicode-0.4
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/libunicode/0.4/}

# LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
