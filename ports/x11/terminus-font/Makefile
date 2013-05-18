# $MirOS: ports/x11/terminus-font/Makefile,v 1.2 2005/12/16 10:31:47 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/01/30 17:04:48 lebel Exp $

COMMENT=			fixed width fonts especially for long hacking sessions
DISTNAME=		terminus-font-4.16
CATEGORIES=		x11
HOMEPAGE=		http://www.is-vn.bg/hamster/jimmy-en.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.is-vn.bg/hamster/ \
			http://legonet.org/~salan/distfiles/

CONFIGURE_STYLE=	simple
NO_REGRESS=		Yes
USE_X11=		Yes

ALL_TARGET=		pcf

FONTDIR=		${PREFIX}/lib/X11/fonts/terminus

do-install:
	${GZIP_CMD} ${WRKSRC}/*.pcf
	${INSTALL_DATA_DIR} ${FONTDIR}
	${INSTALL_DATA} ${WRKSRC}/*.pcf.gz ${FONTDIR}/
	cd ${FONTDIR} && ${X11BASE}/bin/mkfontdir; \
	    sed -e 's/.pcf.gz//' fonts.dir | fgrep terminus >fonts.alias

.include <bsd.port.mk>
