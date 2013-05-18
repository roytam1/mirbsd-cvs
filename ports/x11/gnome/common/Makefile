# $MirOS: ports/x11/gnome/common/Makefile,v 1.2 2005/12/29 19:06:14 bsiegert Exp $

COMMENT=			common files for GNOME applications

VERSION=		2.12.0
DISTNAME=		gnome-common-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/


MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-common/2.12/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu old
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--disable-gtk-doc

post-install:
	${INSTALL_DATA} ${FILESDIR}/gtk-doc.m4 ${PREFIX}/share/aclocal

.include <bsd.port.mk>
