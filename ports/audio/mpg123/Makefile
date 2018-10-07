# $MirOS: ports/audio/mpg123/Makefile,v 1.12 2017/02/25 18:23:21 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/11/13 20:51:50 margarida Exp $

# might not be too hard to add more
ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		MPEG audio 1/2 Layer 1, 2 and 3 player
DISTNAME=		mpg123-0.59r
DASH_VER=		10
CATEGORIES=		audio
HOMEPAGE=		http://www.mpg123.de/

# GNU LGPLv2.1 (except libao and oldalsa audio modules, which are GPL)
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

FLAVOURS=		esd
FLAVOUR?=

.if ${FLAVOUR:L:Mesd}
LIB_DEPENDS=		esd.2::audio/esound
EXTRA_XAKE_FLAGS+=	AUDIO=esd
.endif

MPG123_VSN=		${PKGNAME:S/-${DASH_VER}$/-MirPorts-${DASH_VER}/}
CPPFLAGS+=		-DMPG123_VSN=\"${MPG123_VSN:Q}\"
MAKE_FILE=		${FILESDIR}/BSDmakefile
NO_REGRESS=		Yes

post-extract:
	cp ${FILESDIR}/{audio_openbsd,icy,uniprint}.c ${WRKSRC}/

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/mpg123
	${INSTALL_DATA} ${WRKSRC}/{COPYING,README{,.remote}} \
	    ${PREFIX}/share/mpg123/

.include <bsd.port.mk>
