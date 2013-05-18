# $MirOS$
# $OpenBSD: Makefile,v 1.13 2003/08/24 01:21:35 jolan Exp $

# sync with mplayer archs due to dependency
ONLY_FOR_PLATFORM=	*:*:i386 *:*:powerpc OpenBSD:*:arm OpenBSD:*:amd64 #XXX

DISTNAME=		mplayer-fontmaker-0.90
CATEGORIES=		x11 multimedia
COMMENT=		subtitle fonts generator for mplayer

MODULES=		converters/libiconv
BUILD_DEPENDS=		::multimedia/mplayer:configure
DISTFILES=
NO_CHECKSUM=		Yes

post-extract:
	ln -sf ${WRKDIR}/x11/mplayer/MPlayer-* ${WRKDIST}

WRKSRC=	${WRKDIST}/TOOLS/subfont-c
ALL_TARGET=subfont
MAKE_FLAGS=OPTFLAGS='-I${X11BASE}/include/freetype2 -I${LOCALBASE}/include' \
    LDLIBS='-lm -L${X11BASE}/lib -lfreetype -L${ICONV_PREFIX}/lib -liconv'

USE_GMAKE=		Yes
USE_X11=		Yes # depends on mplayer, which needs X11
USE_CXX=		Yes # depends on mplayer, which uses CXX

OSDDIR=${PREFIX}/libdata/mplayer-osd

post-build:
	sed -e 's,^PREFIX=.*,PREFIX=${PREFIX},' \
	    ${FILESDIR}/mksubfont >${WRKBUILD}/mksubfont

NO_REGRESS=Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/subfont ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${OSDDIR}
	${INSTALL_DATA} ${WRKBUILD}/osd/osd.pfb  ${OSDDIR}
	${INSTALL_DATA} ${WRKBUILD}/encodings/osd-mplayer ${OSDDIR}/osd-encoding
	${INSTALL_PROGRAM} ${WRKBUILD}/mksubfont ${PREFIX}/bin
	${INSTALL_DATA} ${WRKBUILD}/README ${PREFIX}/share/doc/mplayer-fontmaker

PERMIT_PACKAGE_FTP=	dependency multimedia/mplayer is not allowed for FTP
PERMIT_PACKAGE_CDROM=	dependency multimedia/mplayer is not allowed for CDROM
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"Patented stuff"

.include <bsd.port.mk>
