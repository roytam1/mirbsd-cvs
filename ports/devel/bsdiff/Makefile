# $MirOS: ports/devel/bsdiff/Makefile,v 1.1.7.1 2005/03/18 15:44:30 tg Exp $

COMMENT=			binary patch tools
DISTNAME=	bsdiff-4.1
CATEGORIES=	devel
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://www.daemonology.net/bsdiff/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_FLAGS=	BZIP2=${LOCALBASE}/bin/bzip2
FAKE_FLAGS=	PREFIX=${WRKINST}${PREFIX} WITHOUT_MAN=1
NO_REGRESS=	Yes

RUN_DEPENDS=	:bzip2-*:archivers/bzip2

BSDIFF_MAN=	${WRKBUILD}/bsdiff.1
BSDIFF_CAT=	${PREFIX}/man/cat1/bsdiff.0

BSPATCH_MAN=	${WRKBUILD}/bspatch.1
BSPATCH_CAT=	${PREFIX}/man/cat1/bspatch.0

post-install:
	@${MANLINT} ${BSDIFF_MAN}
	@${NROFF} -mandoc ${BSDIFF_MAN} >${BSDIFF_CAT} || (rm -f ${BSDIFF_CAT}; false)
	@${MANLINT} ${BSPATCH_MAN}
	@${NROFF} -mandoc ${BSPATCH_MAN} >${BSPATCH_CAT} || (rm -f ${BSPATCH_CAT}; false)
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bsdiff
	@${INSTALL_DATA} ${WRKBUILD}/LICENSE ${PREFIX}/share/doc/bsdiff

.include <bsd.port.mk>
.include <bsd.man.mk>
