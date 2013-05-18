# $MirOS$
# $OpenBSD: Makefile,v 1.2 2003/03/02 21:38:18 pvalchev Exp $

ONLY_FOR_PLATFORMS= OpenBSD:*:* MirBSD:*:*

COMMENT=	extensible formatted print C library

VERSION=	2.0
DISTNAME=	libfmt-${VERSION}
CATEGORIES=	devel plan9
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://pdos.lcs.mit.edu/~rsc/software/
EXTRACT_SUFX=	.tgz

BUILD_DEPENDS=	::devel/libutf

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FAKE_FLAGS=	PREFIX=${WRKINST}${PREFIX}
REGRESS_TARGET=	test
REGRESS_DEPENDS=${BUILD_DEPENDS}

pre-build:
	@cp ${FILESDIR}/Make.OpenBSD ${WRKSRC}
	@cp ${FILESDIR}/Make.OpenBSD ${WRKSRC}/Make.MirBSD

.include <bsd.port.mk>
