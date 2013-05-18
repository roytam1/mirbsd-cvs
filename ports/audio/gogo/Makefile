# $MirOS: ports/audio/gogo/Makefile,v 1.5 2005/07/07 21:17:16 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2002/10/24 22:20:03 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			686 class CPU optimized mp3 encoder
DISTNAME=	gogo226a	
PKGNAME=	gogo-2.26a-0
CATEGORIES=	audio
MASTER_SITES=	http://www.kurims.kyoto-u.ac.jp/~shigeo/soft/gogo2/src/
HOMEPAGE=	http://homepage1.nifty.com/herumi/gogo_e.html
EXTRACT_SUFX=	.tgz

BUILD_DEPENDS=	::lang/nasm

PERMIT_PACKAGE_CDROM=	MP3 patent, mp3licensing.com/details/software.html
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	MP3 patent. decoders are free. encoders are not.
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes
MAKE_FLAGS=	E3DN=''
NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gogo
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gogo/japandoc
	${INSTALL_MAN} ${WRKSRC}/*.txt ${PREFIX}/share/doc/gogo
	${INSTALL_DATA} ${WRKSRC}/japandoc/* ${PREFIX}/share/doc/gogo/japandoc

.include <bsd.port.mk>
