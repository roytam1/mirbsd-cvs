# $MirOS$
# $OpenBSD: Makefile,v 1.9 2013/03/21 08:45:18 ajacoutot Exp $

COMMENT=		free OpenGL Utility Toolkit
DISTNAME=		freeglut-2.8.0
CATEGORIES=		graphics devel
HOMEPAGE=		http://freeglut.sourceforge.net/

# X11
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=freeglut/}

USE_X11=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.62
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-replace-glut \
			--enable-warnings=no

NO_REGRESS=		Yes

.include <bsd.port.mk>
