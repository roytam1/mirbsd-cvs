# $MirOS$

ONLY_FOR_PLATFORM=	MidnightBSD:*:*
COMMENT=		x.org pkg-config reachover for MidnightBSD
DISTNAME=		xorg-reachover-20081207
CATEGORIES=		essentials x11
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://www.MidnightBSD.org/

# copyright law not applicable
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DISTFILES=		#none
NO_CHECKSUM=		Yes
NO_EXTRACT=		Yes
NO_BUILD=		Yes
WRKDIST=		${WRKDIR}

PCLINKS=		fixesproto fontconfig freetype2 kbproto renderproto \
			x11 xcursor xfixes xft xrender

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/pkgconfig
	cd ${PREFIX}/lib/pkgconfig && for name in ${PCLINKS}; do \
		ln -s /usr/local/lib/$$name.pc $$name.pc; \
	done

.include <bsd.port.mk>
