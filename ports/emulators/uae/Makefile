# $MirOS: ports/emulators/uae/Makefile,v 1.3 2005/03/30 18:13:25 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2002/10/26 12:52:48 naddy Exp $

COMMENT=			UAE amiga emulator
DISTNAME=	uae-0.8.21
CATEGORIES=	emulators x11

MASTER_SITES=	ftp://ftp.freiburg.linux.de/pub/uae/sources/develop/

HOMEPAGE=	http://www.freiburg.linux.de/~uae

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-dga --enable-vidmode --disable-ui

MODULES=	devel/gettext
LIB_DEPENDS+=	glib.1.2,gmodule.1.2::devel/glib1\
		gtk.1.2,gdk.1.2::x11/gtk+1

NO_REGRESS=	Yes

DOCS=		COMPATIBILITY CREDITS FAQ NEWS README README.PROGRAMMERS

FILES=		mousehack timehack transdisk transrom uae-control \
		uae-control.info uae_rcli uaectrl

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/uae ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/readdisk ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/uae/amiga
	cd ${WRKSRC}/docs && ( \
	  ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/uae; \
	  ${INSTALL_DATA} unix/README ${PREFIX}/share/uae/README.unix )
	cd ${WRKSRC}/amiga && ${INSTALL_DATA} ${FILES} \
	  ${PREFIX}/share/uae/amiga

.include <bsd.port.mk>
