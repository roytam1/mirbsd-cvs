# $MirOS: ports/archivers/bzip2/Makefile,v 1.6 2006/11/16 20:13:02 tg Exp $
# $OpenBSD: Makefile,v 1.47 2004/04/06 06:33:29 brad Exp $

COMMENT=		block-sorting file compressor, unencumbered
VERSION=		1.0.4
DISTNAME=		bzip2-${VERSION}
CATEGORIES=		archivers
HOMEPAGE=		http://www.bzip.org/
MASTER_SITES=		${HOMEPAGE}${VERSION}/

# BSD-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes	# not adapted for the moment

post-extract:
	cp ${FILESDIR}/Makefile ${WRKSRC}/
.for dir in lib bzip2 bzip2recover
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor

.include <bsd.port.mk>
