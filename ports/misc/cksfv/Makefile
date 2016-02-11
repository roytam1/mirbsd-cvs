# $MirOS: ports/misc/cksfv/Makefile,v 1.6 2009/11/22 15:48:49 tg Exp $

COMMENT=		checksummer for .sfv files
VERSION=		1.3
CATEGORIES=		archivers misc net
DISTNAME=		cksfv-${VERSION}
DASH_VER=		4
HOMEPAGE=		http://www.fodder.org/cksfv/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

MAKE_FILE=		BSDmakefile
CPPFLAGS+=		-DVERSION=\"${VERSION}\"

pre-patch:
	cp ${FILESDIR}/BSDmakefile ${FILESDIR}/cksfv.1 ${WRKSRC}/

.include <bsd.port.mk>
