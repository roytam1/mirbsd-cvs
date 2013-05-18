# $MirOS: ports/archivers/bzip2/Makefile,v 1.4 2005/07/07 21:16:52 bsiegert Exp $
# $OpenBSD: Makefile,v 1.47 2004/04/06 06:33:29 brad Exp $

COMMENT=			block-sorting file compressor, unencumbered

VERSION=		1.0.3
DISTNAME=		bzip2-${VERSION}
PKGNAME=		${DISTNAME}-0
CATEGORIES=		archivers
HOMEPAGE=		http://www.bzip.org/
MASTER_SITES=		${HOMEPAGE}${VERSION}/

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

.include <bsd.port.mk>
