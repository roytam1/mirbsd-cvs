# $MirOS: ports/devel/smpeg/Makefile,v 1.12 2007/08/25 14:20:01 tg Exp $
# $OpenBSD: Makefile,v 1.16 2003/12/29 13:45:30 espie Exp $

COMMENT=		mpeg video player library with sound support
DISTNAME=		smpeg-0.4.4
DASH_VER=		3
CATEGORIES=		devel graphics
HOMEPAGE=       	http://www.lokigames.com/development/smpeg.php3

# LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		ftp://ftp.lokigames.com/pub/open-source/smpeg/ \
			ftp://sunsite.auc.dk/pub/os/linux/loki/open-source/smpeg/ \
			ftp://snuffleupagus.animearchive.org/loki/open-source/smpeg/

LIB_DEPENDS+=		SDL::devel/sdl
USE_X11=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autogen no-autoheader
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-gtk-player

post-extract:
	-rm -f ${WRKSRC}/aclocal.m4

post-install:
	${INSTALL_MAN} ${FILESDIR}/smpeg.3 ${PREFIX}/man/man3/

.include <bsd.port.mk>
