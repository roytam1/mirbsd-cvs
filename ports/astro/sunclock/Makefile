# $OpenBSD: Makefile,v 1.3 2004/02/04 07:39:18 sturm Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			display the phase of the Sun on a map of the Earth
COMMENT-maps=			additional maps of the Earth for sunclock

VERSION=		3.50pre1
DISTNAME=		sunclock-${VERSION}
PKGNAME-maps=		sunclock-maps-${VERSION}-0
CATEGORIES=		astro

HOMEPAGE=		http://frmas.free.fr/li_1.htm


MASTER_SITES=		ftp://ftp.ac-grenoble.fr/ge/geosciences/
SUPDISTFILES=		sunclock_jpeg_medium_maps-1.0.tgz \
			sunclock_jpeg_big_maps-1.0.tgz \
			sunclock_huge_earthmap.jpg
EXTRACT_SUFX=		.tgz

USE_X11=		Yes
CONFIGURE_STYLE=	imake
NO_REGRESS=		Yes

PSEUDO_FLAVOURS=	no_maps
FLAVOUR?=	no_maps

MULTI_PACKAGES=
.if !${FLAVOUR:L:Mno_maps}
MULTI_PACKAGES+= -maps
.endif
SUBPACKAGE?=

.if defined(PACKAGING) && ${SUBPACKAGE} == "-maps"
PERMIT_PACKAGE_CDROM=	"no license for additional maps"
PERMIT_PACKAGE_FTP=	"no license for additional maps"
PERMIT_DISTFILES_CDROM=	"no license for additional maps"
PERMIT_DISTFILES_FTP=	"no license for additional maps"

RUN_DEPENDS=    ::astro/sunclock

PKG_ARCH=	*
.else
# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	jpeg.62::graphics/jpeg
.endif

.if ${MULTI_PACKAGES:M-maps} # with maps
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${SUPDISTFILES}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

post-extract:
	tar -xzf ${FULLDISTDIR}/sunclock_jpeg_medium_maps-1.0.tgz \
		-C ${WRKSRC}/vmf -s '#jpeg/medium#.#'
	tar -xzf ${FULLDISTDIR}/sunclock_jpeg_big_maps-1.0.tgz \
		-C ${WRKSRC}/vmf -s '#jpeg/big#.#'
	cp ${FULLDISTDIR}/sunclock_huge_earthmap.jpg ${WRKSRC}/vmf/

.else # no maps
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/sunclock ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/sunclock.man ${PREFIX}/man/man1/sunclock.1
	${INSTALL_DATA_DIR} ${PREFIX}/share/sunclock
	${INSTALL_DATA} ${WRKSRC}/Sunclockrc ${PREFIX}/share/sunclock/
	${INSTALL_DATA_DIR} ${PREFIX}/share/sunclock/earthmaps
	${INSTALL_DATA_DIR} ${PREFIX}/share/sunclock/earthmaps/vmf
	${INSTALL_DATA_DIR} ${PREFIX}/share/sunclock/i18n
	${INSTALL_DATA_DIR} ${PREFIX}/share/sunclock/wm_icons/
	${INSTALL_DATA} ${WRKSRC}/wm_icons/* ${PREFIX}/share/sunclock/wm_icons/
	${INSTALL_DATA} ${WRKSRC}/vmf/* ${PREFIX}/share/sunclock/earthmaps/vmf/
	${INSTALL_DATA} ${WRKSRC}/i18n/Sunclock.* ${PREFIX}/share/sunclock/i18n/

.include <bsd.port.mk>
