# $OpenBSD: Makefile,v 1.3 2004/04/10 23:10:14 xsa Exp $

COMMENT=			enriched clone of the game Logical by Rainbow Arts

DISTNAME=	pathological-1.1.3
CATEGORIES=	games
HOMEPAGE=	http://pathological.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pathological/}

PYTHON_VER=	2.3

RUN_DEPENDS=	:python-${PYTHON_VER}*:lang/python/${PYTHON_VER} \
		:pygame-*:devel/pygame
BUILD_DEPENDS=	:netpbm-*:graphics/netpbm

USE_CXX=	Yes

NO_REGRESS=	Yes

DOCDIR=		${PREFIX}/share/doc/pathological
GAMEDIR=	${PREFIX}/share/pathological

pre-build:
	@perl -pi -e 's,%%LOCALBASE%%,${LOCALBASE},g' \
		${WRKSRC}/pathological{,.py} 
	@perl -pi -e 's,/usr/bin/python,${LOCALBASE}/bin/python${PYTHON_VER},g' \
		${WRKSRC}/pathological.py

do-build:
	cd ${WRKSRC} && \
	    ${_PASS_CC:Q} ${CFLAGS} -o write-highscores write-highscores.c && \
	    ./makehtml

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/pathological ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/write-highscores ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${GAMEDIR}/{circuits,graphics,music,sounds}
	${INSTALL_PROGRAM} ${WRKSRC}/pathological.py ${GAMEDIR}
	${INSTALL_DATA} ${WRKSRC}/circuits/all-boards ${GAMEDIR}/circuits
	${INSTALL_DATA}	${WRKSRC}/graphics/*.{jpg,png} ${GAMEDIR}/graphics
	${INSTALL_DATA} ${WRKSRC}/music/*.xm ${GAMEDIR}/music
	${INSTALL_DATA} ${WRKSRC}/sounds/*.wav ${GAMEDIR}/sounds
	${INSTALL_DATA_DIR} ${PREFIX}/share/pixmaps
	${INSTALL_DATA} ${WRKSRC}/pathological.xpm ${PREFIX}/share/pixmaps
	@gunzip ${WRKSRC}/pathological.6.gz
	${INSTALL_MAN} ${WRKSRC}/pathological.6 ${PREFIX}/man/man6
	${INSTALL_DATA_DIR} ${DOCDIR}/html
	${INSTALL_DATA} ${WRKSRC}/html/*.{html,png} ${DOCDIR}/html

.include <bsd.port.mk>
