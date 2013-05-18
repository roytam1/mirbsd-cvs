# $MirOS: ports/games/uqm/Makefile,v 1.7 2008/10/04 19:03:09 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/03/31 03:42:16 jolan Exp $

# 64-bit issues, unaligned memory access
ONLY_FOR_PLATFORM=	*:*:i386 *:*:powerpc

COMMENT=			ur-quan masters: sdl port of star control 2
COMMENT-3domusic=			ur-quan masters: 3DO music content
COMMENT-remix1=			ur-quan masters: remix pack number one
COMMENT-remix2=			ur-quan masters: remix pack number two
COMMENT-voice=			ur-quan masters: speech content

VER=			0.3
DISTNAME=		uqm-${VER}-source
CATEGORIES=		games x11
PDIST=			${DISTNAME}.tgz
CDIST=			uqm-${VER}-content.zip
MDIST=			uqm-${VER}-3domusic.zip
VDIST=			uqm-${VER}-voice.zip
RM1DIST=		uqm-remix-pack1.zip
RM2DIST=		uqm-remix-pack2.zip
DISTFILES=		${PDIST} ${CDIST}
SUPDISTFILES=		${MDIST} ${VDIST} ${RM1DIST} ${RM2DIST}
DIST_SUBDIR=		uqm
CATEGORIES=		games x11
PKGNAME=		uqm-${VER}-0
PKGNAME-3domusic=	uqm-3domusic-${VER}-0
PKGNAME-remix1=		uqm-remix1-${VER}-0
PKGNAME-remix2=		uqm-remix2-${VER}-0
PKGNAME-voice=		uqm-voice-${VER}-0
EXTRACT_ONLY=		${PDIST}
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sc2/}
HOMEPAGE=		http://sc2.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	"Unresolved licensing issues"
PERMIT_PACKAGE_FTP=	"Unresolved licensing issues"
PERMIT_DISTFILES_CDROM=	"Unresolved licensing issues"
PERMIT_DISTFILES_FTP=	"Unresolved licensing issues"

LIB_DEPENDS=	SDL_image::devel/sdl-image \
		vorbis.0,vorbisfile.1::audio/libvorbis

NO_REGRESS=	Yes
USE_GMAKE=	Yes
USE_X11=	Yes
USE_CXX=	Yes

PSEUDO_FLAVOURS=	no_3domusic no_remix1 no_remix2 no_voice
FLAVOUR?=

MULTI_PACKAGES=
.if !${FLAVOUR:L:Mno_3domusic}
DISTFILES+=	${MDIST}
MULTI_PACKAGES+=-3domusic
.endif
.if !${FLAVOUR:L:Mno_remix1}
DISTFILES+=	${RM1DIST}
MULTI_PACKAGES+=-remix1
.endif
.if !${FLAVOUR:L:Mno_remix2}
DISTFILES+=	${RM2DIST}
MULTI_PACKAGES+=-remix2
.endif
.if !${FLAVOUR:L:Mno_voice}
DISTFILES+=	${VDIST}
MULTI_PACKAGES+=-voice
.endif

SUBPACKAGE?=

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-3domusic"
PKG_ARCH=	*
RUN_DEPENDS=	::games/uqm
. endif
. if ${SUBPACKAGE} == "-remix1"
PKG_ARCH=	*
RUN_DEPENDS=	::games/uqm
. endif
. if ${SUBPACKAGE} == "-remix2"
PKG_ARCH=	*
RUN_DEPENDS=    ::games/uqm
. endif
. if ${SUBPACKAGE} == "-voice"
PKG_ARCH=	*
RUN_DEPENDS=	::games/uqm
. endif
.endif

WRKSRC=		${WRKDIR}/${PKGNAME}

do-configure:
.if (${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "i386" || \
     ${MACHINE_ARCH} == "vax")
	@sed -e "s|@PREFIX@|${PREFIX}|g ; s|@ENDIAN@|undef|g" \
		${FILESDIR}/config.h > ${WRKSRC}/src/config.h
.else
	@sed -e "s|@PREFIX@|${PREFIX}|g ; s|@ENDIAN@|define|g" \
		${FILESDIR}/config.h > ${WRKSRC}/src/config.h
.endif
	@sed -e "s|@CC@|"${_PASS_CC:T:Q}"|g ; s|@CFLAGS@|${CFLAGS}|g ; \
		s|@LOCALBASE@|${LOCALBASE}|g ; s|@PREFIX@|${PREFIX}|g ; \
		s|@X11BASE@|${X11BASE}|g" ${FILESDIR}/build.vars \
		> ${WRKSRC}/build.vars

do-build:
	cd ${WRKBUILD}; ./build.sh uqm

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/uqm
	${INSTALL_DATA_DIR} ${PREFIX}/share/uqm/content/packages/addons/uqmremix
	${INSTALL_DATA} ${WRKBUILD}/doc/users/manual.txt \
		${PREFIX}/share/doc/uqm
	${INSTALL_DATA} ${WRKBUILD}/content/version \
		${PREFIX}/share/uqm/content
	${INSTALL_DATA} ${FULLDISTDIR}/${CDIST} \
		${PREFIX}/share/uqm/content/packages
.if !${FLAVOUR:L:Mno_3domusic}
	${INSTALL_DATA} ${FULLDISTDIR}/${MDIST} \
		${PREFIX}/share/uqm/content/packages
.endif
.if !${FLAVOUR:L:Mno_remix1}
	${INSTALL_DATA} ${FULLDISTDIR}/${RM1DIST} \
		${PREFIX}/share/uqm/content/packages/addons/uqmremix
.endif
.if !${FLAVOUR:L:Mno_remix2}
	${INSTALL_DATA} ${FULLDISTDIR}/${RM2DIST} \
		${PREFIX}/share/uqm/content/packages/addons/uqmremix
.endif
.if !${FLAVOUR:L:Mno_voice}
	${INSTALL_DATA} ${FULLDISTDIR}/${VDIST} \
		${PREFIX}/share/uqm/content/packages
.endif
	${INSTALL_PROGRAM} ${WRKBUILD}/uqm ${PREFIX}/bin

.include <bsd.port.mk>
