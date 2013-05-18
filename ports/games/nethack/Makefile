# $OpenBSD: Makefile,v 1.31 2003/02/25 00:15:02 espie Exp $
# $FreeBSD: Makefile,v 1.13 1997/12/25 22:29:17 asami Exp $

COMMENT=			dungeon explorin', hackin', game.  Piece of cake
DISTNAME=	nethack-3.4.1
CATEGORIES=	games

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=nethack/} \
		ftp://ftp.nethack.org/pub/nethack/nh341/src/ \
		ftp://ftp.uu.net/pub/games/nethack/sources/ \
		${MASTER_SITE_GNU:=nethack/}
DISTFILES=	nethack-341.tgz

HOMEPAGE=	http://nethack.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FAKE_FLAGS=PREFIX=${PREFIX} DESTDIR=${WRKINST}

NHDIR=	${PREFIX}/lib/nethackdir
MAKE_ENV+= NHDIR=${NHDIR} NETHACKCONFIG=${NETHACKCONFIG}

FLAVOURS=no_x11 qt
FLAVOUR?=

.if ${FLAVOUR:L} == "no_x11"
NETHACKCONFIG=${FILESDIR}/simple-config
.elif ${FLAVOUR:L} == "qt"
SED_PLIST=|sed -e '/^!%%no_x11%%/d'
NETHACKCONFIG=${FILESDIR}/qt-config
MODULES=	x11/qt3
MODQT_MT=	Yes
.else
NETHACKCONFIG=${FILESDIR}/x-config
USE_X11=	Yes
.endif

RUN_DEPENDS=:hackdata-*:games/hackdata

NO_REGRESS=	Yes

do-configure:
	@cd ${WRKSRC}/sys/unix; ${SH} setup.sh symlinks

post-build:
	@cd ${WRKSRC}/util && ${MAKE_ENV} make recover

post-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/util/recover ${PREFIX}/bin
	@cd ${WRKSRC}/doc && \
	    ${INSTALL_MAN} nethack.6 recover.6 ${PREFIX}/man/man6
.if ${FLAVOUR:L} == ""
	${INSTALL_DATA_DIR} ${PREFIX}/lib/X11/app-defaults
	@cd ${WRKSRC}/win/X11 && cp NetHack.ad NetHack && \
	    ${INSTALL_DATA} NetHack ${PREFIX}/lib/X11/app-defaults
.endif

.include <bsd.port.mk>
