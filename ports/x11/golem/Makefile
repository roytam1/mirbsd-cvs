# $OpenBSD: Makefile,v 1.7 2004/04/09 09:52:10 espie Exp $

COMMENT=			fast and light window manager with plug-ins

DISTNAME=		golem-0.0.5
CATEGORIES=     	x11

HOMEPAGE=		http://golem.sourceforge.net/


# License: BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=golem/}

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf dest no-autoheader

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/golem
	${INSTALL_DATA} ${WRKSRC}/{THEMES,PLUGINS} ${PREFIX}/share/doc/golem

.include <bsd.port.mk>
.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
CONFIGURE_FLAGS+=	--disable-plugins
.endif
