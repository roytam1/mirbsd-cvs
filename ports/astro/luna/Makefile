# $OpenBSD: Makefile,v 1.5 2003/01/04 19:09:52 pvalchev Exp $

COMMENT=			display the moon's phase

DISTNAME=	luna19s
PKGNAME=	luna-1.9-0
CATEGORIES=	astro
EXTRACT_SUFX=	.lzh

PERMIT_PACKAGE_CDROM=	"copyrighted"
PERMIT_PACKAGE_FTP=	"copyrighted"
PERMIT_DISTFILES_CDROM=	"copyrighted"
PERMIT_DISTFILES_FTP=	"copyrighted"

MASTER_SITES=	ftp://ftp.vector.co.jp/pack/dos/edu/science/space/

BUILD_DEPENDS=	::archivers/lha

MAKE_ENV=	CC=${_PASS_CC:T:Q}
MAKE_FILE=	makefile
NO_REGRESS=	Yes

post-extract:
.for f in famplan.c luna.c luna.h makefile pyramid.c pyramid.h iprintf/makefile
	@cd ${WRKSRC} && sed -e \
	's#[[:cntrl:]]$$##g' < ${f} > ${f}.new && mv -f ${f}.new ${f}
.endfor

.include <bsd.port.mk>
