# $MirOS: ports/lang/pawn/toolkit/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

COMMENT=		embeddable C-like scripting language
DISTNAME=		pawn-3.3.3951

EXTRACT_SUFX=		.tgz
BUILD_DEPENDS+=		:mirmake->=20080411:devel/mirmake
LIB_DEPENDS+=		ffi::devel/libffi
RUN_DEPENDS+=		:pawn-docs-*:lang/pawn/doku

WRKBUILD=		${WRKDIST}/source
CPPFLAGS+=		-DMP_PREFIX=\"${PREFIX:Q}\"

post-extract:
	cd ${WRKSRC}/source/compiler && mv libpawnc.c library.c
	cd ${FILESDIR} && pax -rw . ${WRKBUILD}/

pre-install:
	${INSTALL_LIB_DIR} ${PREFIX}/libexec/pawn

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR} ${EXDIR}/{amx,pawn} \
	    ${SHDIR}/{include,xml}
	${INSTALL_DATA} ${WRKSRC}/*.txt ${DOCDIR}/
	${INSTALL_DATA} ${WRKSRC}/examples/* ${EXDIR}/pawn/
	${INSTALL_DATA} ${WRKSRC}/source/amx/examples/* ${EXDIR}/amx/
	${INSTALL_DATA} ${WRKSRC}/include/*.inc ${SHDIR}/include/
	${INSTALL_DATA} ${WRKSRC}/xml/pawndoc.* ${SHDIR}/xml/

.include <bsd.port.mk>
