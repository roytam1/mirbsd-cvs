# $MirOS$
# $OpenBSD: Makefile,v 1.47 2004/04/06 06:33:29 brad Exp $

COMMENT=		"block-sorting file compressor, unencumbered"

DISTNAME=		bzip2-1.0.2
PKGNAME=		${DISTNAME}p1
CATEGORIES=		archivers
MASTER_SITES=		${MASTER_SITE_SOURCEWARE:=bzip2/v102/}
HOMEPAGE=		http://sources.redhat.com/bzip2/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=	Yes # not adapted for the moment

post-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}
.for dir in lib bzip2 bzip2recover
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor

post-install:
	@cd ${WRKBUILD} && makeinfo --no-split manual.texi
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bzip2
	${INSTALL_DATA} ${WRKBUILD}/*.html ${PREFIX}/share/doc/bzip2
	${INSTALL_DATA} ${WRKBUILD}/bzip2.info ${PREFIX}/info

.include <bsd.port.mk>
