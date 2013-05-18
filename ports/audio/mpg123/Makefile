# $MirOS: ports/audio/mpg123/Makefile,v 1.3 2006/02/09 11:11:06 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/11/13 20:51:50 margarida Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		MPEG audio 1/2 Layer 1, 2 and 3 player
DISTNAME=		mpg123-0.59r
PKGNAME=		${DISTNAME}-4
CATEGORIES=		audio
HOMEPAGE=		http://www.mpg123.de/

# See the COPYING file installed with the package.
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=	http://www.mpg123.de/mpg123/ \
		http://www-ti.informatik.uni-tuebingen.de/~hippm/mpg123/ \
		ftp://ftp.tu-clausthal.de/pub/unix/audio/mpg123/ \
		http://ftp.tu-clausthal.de/pub/unix/audio/mpg123
MASTER_SITES0=	ftp://ftp.kame.net/pub/kame/misc/
MASTER_SITES1=	http://www.unix-ag.org/Linux-Alpha/Packages/

PATCHFILES=		mpg123-059r-v6-20000713b.diff.gz:0 \
			l3.diff.gz:1
PATCH_DIST_STRIP=	-p1

FLAVORS=		esd
FLAVOR?=

OBJECTS=		term.o
CPPFLAGS+=		-DOPENBSD -DREAL_IS_FLOAT -DTERM_CONTROL -DINET6 \
			-DUSE_MMAP
ALL_TARGET=		mpg123-make
EXTRA_XAKE_FLAGS+=	OBJECTS=${OBJECTS:Q}

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+=		-DROT_I386 -DI386_ASSEM -DPENTIUM_OPT
OBJECTS+=		decode_i386.o decode_i586.o dct64_i386.o
.else
OBJECTS+=		decode.o dct64.o
.endif

.if ${FLAVOR:L:Mesd}
LIB_DEPENDS=		esd.2::audio/esound
OBJECTS+=		audio_esd.o
.else
OBJECTS+=		audio_openbsd.o
.endif

post-patch:
	@cp ${FILESDIR}/audio_openbsd.c ${FILESDIR}/term.c ${WRKSRC}/

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/mpg123 ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/mpg123.1 ${PREFIX}/man/man1/
	${INSTALL_DATA_DIR} ${PREFIX}/share/mpg123
	${INSTALL_DATA} ${WRKSRC}/COPYING ${PREFIX}/share/mpg123/

NO_REGRESS=	Yes

.include <bsd.port.mk>
