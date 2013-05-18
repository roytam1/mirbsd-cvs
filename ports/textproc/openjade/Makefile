# $MirOS: ports/textproc/openjade/Makefile,v 1.3 2008/10/04 19:03:45 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/04/20 22:36:17 brad Exp $

COMMENT=			object-oriented SGML/XML parser toolkit and DSSSL engine
DISTNAME=	openjade-1.3
CATEGORIES=	textproc
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=openjade/}
HOMEPAGE=	http://openjade.sourceforge.net/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_FLAGS=	RANLIB="${RANLIB}" CFLAGS="${CFLAGS}" CC=${_PASS_CC:T:Q} CXX=${_PASS_CXX:T:Q}" -fno-implicit-templates ${CXXFLAGS}" \
		XDEFINES='-DJADE_MIF -DJADE_HTML -DSGML_CATALOG_FILES_DEFAULT=\"${PREFIX}/share/sgml/openjade/catalog\"'
FAKE_FLAGS=	prefix="${WRKINST}${PREFIX}" INSTALL="${INSTALL_PROGRAM}"

USE_GMAKE=	Yes

DOCDIR=		${PREFIX}/share/doc/openjade
SGMLDIR=	${PREFIX}/share/sgml/openjade
SGMLFILES= 	fot.dtd catalog dsssl.dtd style-sheet.dtd builtins.dsl \
		demo.sgm demo.dsl
	
VMEM_WARNING=	Yes
NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}/sp
	${INSTALL_DATA_DIR} ${DOCDIR}/images
	${INSTALL_DATA} ${WRKSRC}/jadedoc/copying.txt ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/*.htm ${DOCDIR}/sp
	${INSTALL_DATA} ${WRKSRC}/jadedoc/*.htm ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/jadedoc/images/*.gif ${DOCDIR}/images
	${INSTALL_DATA_DIR} ${SGMLDIR}
.for i in ${SGMLFILES}
	${INSTALL_DATA} ${WRKSRC}/dsssl/$i ${SGMLDIR}
.endfor

.include <bsd.port.mk>
