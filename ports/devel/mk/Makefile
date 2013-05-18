# $MirOS: ports/devel/mk/Makefile,v 1.2 2005/03/25 23:13:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2003/03/03 00:51:37 pvalchev Exp $

COMMENT=			Streamlined replacement for make

VERSION=	2.0
DISTNAME=	mk-${VERSION}
CATEGORIES=	devel plan9
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://pdos.lcs.mit.edu/~rsc/software/
EXTRACT_SUFX=	.tgz

BUILD_DEPENDS=	fmt::devel/libfmt \
		bio::devel/libbio \
		regexp9::plan9/libregexp9

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FAKE_FLAGS=	PREFIX=${WRKINST}${PREFIX}
NO_REGRESS=	Yes

pre-build:
	@cp ${FILESDIR}/Make.OpenBSD ${WRKSRC}

.include <bsd.port.mk>
