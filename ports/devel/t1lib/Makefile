# $MirOS: ports/devel/t1lib/Makefile,v 1.1.7.1 2005/03/18 15:45:37 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/04/14 18:26:38 brad Exp $

COMMENT=			Type 1 rasterizer library for UNIX/X11
DISTNAME=	t1lib-5.0.0
CATEGORIES=	devel textproc
MASTER_SITES=	${MASTER_SITE_BACKUP}

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf no-autoheader
CONFIGURE_ARGS+=${CONFIGURE_SHARED}

NO_REGRESS=	Yes

ALL_TARGET=	without_doc

.include <bsd.port.mk>
