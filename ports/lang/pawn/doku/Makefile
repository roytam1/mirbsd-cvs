# $MirOS: ports/lang/pawn/doku/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

COMMENT=		language and toolkit documentation for Pawn
DISTNAME=		pawn-docs-20080808

DIST_SUBDIR=		${DISTNAME}
DISTFILES=		pawn-gs.pdf \
			pawn-lang.pdf \
			pawn-imp.pdf \
			amxfixed.pdf \
			amxfloat.pdf \
			amxfile.pdf \
			amxdgram.pdf \
			amxprocess.pdf \
			amxstring.pdf \
			amxtime.pdf \
			smalldebug.zip \
			smallrnd.zip

NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	${INSTALL_DATA_DIR} ${DOCDIR} ${EXDIR}/rnd/{amx,include}
	${INSTALL_DATA} ${WRKDIR}/*.pdf ${WRKSRC}/DebugProc.txt ${DOCDIR}/
	${INSTALL_DATA} ${WRKSRC}/amx/rnd.c ${EXDIR}/rnd/amx/
	${INSTALL_DATA} ${WRKSRC}/examples/* ${WRKSRC}/rnd.txt ${EXDIR}/rnd/
	${INSTALL_DATA} ${WRKSRC}/include/*.inc ${EXDIR}/rnd/include/

.include <bsd.port.mk>
