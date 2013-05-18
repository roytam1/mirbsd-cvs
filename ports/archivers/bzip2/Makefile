# $MirOS: ports/archivers/bzip2/Makefile,v 1.5 2006/09/14 00:06:46 tg Exp $
# $OpenBSD: Makefile,v 1.47 2004/04/06 06:33:29 brad Exp $

COMMENT=		block-sorting file compressor, unencumbered
VERSION=		1.0.3
DISTNAME=		bzip2-${VERSION}
CATEGORIES=		archivers
HOMEPAGE=		http://www.bzip.org/
MASTER_SITES=		${HOMEPAGE}${VERSION}/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes	# not adapted for the moment

post-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}
.for dir in lib bzip2 bzip2recover
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor

.include <bsd.port.mk>
