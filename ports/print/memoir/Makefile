# $MirOS: ports/print/memoir/Makefile,v 1.3 2007/04/13 19:32:38 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/05/27 18:21:00 sturm Exp $

RBROKEN=		unfetchable distfiles

COMMENT=	typeset fiction, non-fiction and mathematical books

DISTNAME=	memoir-1.61p0
CATEGORIES=	print

# LPPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_CASES=	*) cp ${FULLDISTDIR}/$$archive ${WRKDIST};;

MASTER_SITES=	${MASTER_SITE_TEX_CTAN:=macros/latex/contrib/memoir/}

DISTFILES=	memhfixc.sty memman.pdf memman.ist \
			memoir.dtx memoir.ins mempatch.sty
DIST_SUBDIR=	${DISTNAME}

RUN_DEPENDS=	:teTeX_base-*:print/teTeX/base
BUILD_DEPENDS=	${RUN_DEPENDS}

CLS_DIR=	${PREFIX}/share/texmf-local/tex/latex/memoir
DOC_DIR=	${PREFIX}/share/texmf-local/doc/latex/memoir

USE_X11=		Yes # depends on t1lib, which needs X11
USE_CXX=		Yes # depends on teTeX, which uses CXX

pre-extract:
		@mkdir -p ${WRKDIST}

do-build:
		@cd ${WRKBUILD}; latex memoir.ins; \
			latex memoir.dtx; makeindex -s gind.ist memoir; \
			latex memoir.dtx; latex memoir.dtx;

do-install:
		${INSTALL_DATA_DIR} ${CLS_DIR} ${DOC_DIR}
		${INSTALL_DATA} ${WRKDIST}/{memoir.cls,mem*.clo,mem*.sty} ${CLS_DIR}
		${INSTALL_DATA} ${WRKDIST}/{memoir.{dvi,dtx},memman.pdf} ${DOC_DIR}

NO_REGRESS=	Yes

.include <bsd.port.mk>
