# $MirOS: ports/audio/mpg123/Makefile,v 1.2 2005/07/07 21:17:22 bsiegert Exp $
# $OpenBSD: Makefile,v 1.30 2003/11/13 20:51:50 margarida Exp $

COMMENT=	"MPEG audio 1/2 Layer 1, 2 and 3 player"
DISTNAME=	mpg123-0.59r
PKGNAME=	${DISTNAME}-3
CATEGORIES=	audio
HOMEPAGE=	http://www.mpg123.de/

# Long, unclear license in ${WRKSRC}/COPYING.
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.mpg123.de/mpg123/ \
		http://www-ti.informatik.uni-tuebingen.de/~hippm/mpg123/ \
		ftp://ftp.tu-clausthal.de/pub/unix/audio/mpg123/ \
		http://ftp.tu-clausthal.de/pub/unix/audio/mpg123
MASTER_SITES0=	ftp://ftp.kame.net/pub/kame/misc/
MASTER_SITES1=	http://www.unix-ag.org/Linux-Alpha/Packages/

PATCHFILES=	mpg123-059r-v6-20000713b.diff.gz:0 \
		l3.diff.gz:1
PATCH_DIST_STRIP= -p1

FLAVORS=	esd
FLAVOR?=

.if ${FLAVOR:L:Mesd}
LIB_DEPENDS=	esd.2::audio/esound
ALL_TARGET=	mirbsd-esd
.else
ALL_TARGET=	mirbsd
.endif

post-patch:
	@cp ${FILESDIR}/audio_openbsd.c ${FILESDIR}/term.c ${WRKSRC}

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/mpg123 ${PREFIX}/bin
	${INSTALL_MAN} ${WRKBUILD}/mpg123.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/mpg123
	${INSTALL_DATA} ${WRKSRC}/COPYING ${PREFIX}/share/mpg123

NO_REGRESS=	Yes

.include <bsd.port.mk>
