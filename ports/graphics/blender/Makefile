# $MirOS: ports/graphics/blender/Makefile,v 1.6 2008/10/05 01:23:47 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/12/29 20:08:46 fgsch Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			3D creation software
VSN=			2.23
DASH_VER=		1
PKGNAME=		blender-${VSN}-${DASH_VER}
DISTNAME=		blender-creator-${VSN}-linux-glibc2.1.2-i386-static
CATEGORIES=	graphics
HOMEPAGE=	http://www.blender.nl/

PERMIT_PACKAGE_CDROM=	"no commercial use"
PERMIT_PACKAGE_FTP=	"no commercial use"
PERMIT_DISTFILES_CDROM=	"no commercial use"
PERMIT_DISTFILES_FTP=	"no commercial use"

MASTER_SITES=	ftp://ftp.cs.umn.edu/pub/blender/pub/ \
		http://www.download.blender.pl/mirror/

RUN_DEPENDS+=		::emulators/fedora

INSTALL_STRIP=
NO_BUILD=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/blender ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/blender
	${INSTALL_DATA} ${WRKSRC}/{README,copyright.txt} \
		${PREFIX}/share/examples/blender
	cd ${WRKSRC} && tar cf - plugins | \
		(cd ${PREFIX}/share/examples/blender && tar xf -)

.include <bsd.port.mk>
