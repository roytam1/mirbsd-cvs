# $MirOS: ports/devel/bsdiff/Makefile,v 1.2 2006/09/14 00:08:05 tg Exp $

COMMENT=	binary patch tools
DISTNAME=	bsdiff-4.3
CATEGORIES=	devel
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://www.daemonology.net/bsdiff/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_FLAGS+=	BZIP2=${LOCALBASE}/bin/bzip2
FAKE_FLAGS+=	PREFIX=${WRKINST}${PREFIX} WITHOUT_MAN=1
NO_REGRESS=	Yes

LIB_DEPENDS=	bz2::archivers/bzip2

BSDIFF_MAN=	${WRKBUILD}/bsdiff.1
BSDIFF_CAT=	${PREFIX}/man/cat1/bsdiff.0

BSPATCH_MAN=	${WRKBUILD}/bspatch.1
BSPATCH_CAT=	${PREFIX}/man/cat1/bspatch.0

post-install:
	${NROFF} ${BSDIFF_MAN} >${BSDIFF_CAT} || (rm -f ${BSDIFF_CAT}; false)
	${NROFF} ${BSPATCH_MAN} >${BSPATCH_CAT} || (rm -f ${BSPATCH_CAT}; false)

.include <bsd.port.mk>
.include <bsd.man.mk>
