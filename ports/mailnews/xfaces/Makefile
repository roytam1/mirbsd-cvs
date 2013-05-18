# $MirOS: ports/mailnews/xfaces/Makefile,v 1.1.7.1 2005/03/18 15:49:59 tg Exp $
# $OpenBSD: Makefile,v 1.21 2002/10/27 17:21:40 naddy Exp $

COMMENT=			mail image display for X11
DISTNAME=	xfaces-3.3
CATEGORIES=	mail

# xfaces-sounds.tar.gz only in LOCAL_PORTS
MASTER_SITES=	ftp://ftp.cs.indiana.edu/pub/faces/xfaces/ \
		ftp://odie.physik2.uni-rostock.de/pub/ \
		${MASTER_SITE_LOCAL}
DISTFILES=	${DISTNAME}.tar.Z xfaces-sounds.tar.gz

# licencing? they say PERMIT_*=No w/o reason.
PERMIT_DISTFILES_CDROM=	OpenBSD says no, but does not give a reason either.
PERMIT_DISTFILES_FTP=	OpenBSD says no, but does not give a reason either.
PERMIT_PACKAGE_CDROM=	OpenBSD says no, but does not give a reason either.
PERMIT_PACKAGE_FTP=	OpenBSD says no, but does not give a reason either.

LIB_DEPENDS=	compface::mailnews/faces

CONFIGURE_STYLE=imake

post-extract:
	@ln -sf ../sounds ${WRKSRC}

NO_REGRESS=	Yes

pre-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/sounds
	@${INSTALL_DATA_DIR} ${PREFIX}/include/X11/pixmaps

.include <bsd.port.mk>
