# $OpenBSD: Makefile,v 1.26 2004/03/02 07:57:21 brad Exp $

COMMENT=			gtk+ chess board interface

DISTNAME=	eboard-0.9.0
PKGNAME=	${DISTNAME}-0
CATEGORIES=	games x11

HOMEPAGE=	http://eboard.sourceforge.net/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=eboard/}

LIB_DEPENDS=		Imlib.19,gdk_imlib::graphics/imlib

MODULES=		devel/gettext

USE_X11=		Yes
USE_CXX=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf

DOCS=	Crafty.txt FICS-Timeseal.txt GNUChess4.txt GNUChess5.txt \
	Scripts.txt Sjeng.txt Themes.txt

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/eboard
	cd ${WRKSRC}/Documentation; ${INSTALL_DATA} ${DOCS} \
		${PREFIX}/share/doc/eboard

.include <bsd.port.mk>
