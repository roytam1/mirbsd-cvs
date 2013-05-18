# $MirOS: ports/archivers/unrar/Makefile,v 1.3 2006/02/09 11:11:00 tg Exp $
# $OpenBSD: Makefile,v 1.23 2004/02/23 00:33:34 naddy Exp $

COMMENT=			extract, list, and test RAR archives

DISTNAME=	unrarsrc-3.3.6
PKGNAME=	unrar-3.30-0
CATEGORIES=	archivers
USE_CXX=	Yes

HOMEPAGE=	http://www.rarlab.com/

# Restrictive
PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	"may not modify"
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}rar/

# - exceptions don't work on sparc64
.if ${MACHINE_ARCH} == "sparc64"
PATCH_LIST=	patch-* gcc-patch-*
.endif

WRKDIST=	${WRKDIR}/unrar

MAKE_FILE=	makefile.unix
EXTRA_MAKE_FLAGS=	DEFINES=""

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/unrar ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/unrar
	${INSTALL_MAN} ${WRKSRC}/readme.txt ${WRKSRC}/license.txt \
		${PREFIX}/share/doc/unrar

NO_REGRESS=	Yes

.include <bsd.port.mk>
