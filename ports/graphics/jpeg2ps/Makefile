# $MirOS: ports/graphics/jpeg2ps/Makefile,v 1.5 2009/03/16 20:11:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2003/09/23 15:29:41 sturm Exp $

COMMENT=		convert jpeg to compressed PostScript

DISTNAME=		jpeg2ps-1.9
CATEGORIES=		graphics

# according to jpeg2ps.1
PERMIT_PACKAGE_CDROM=	"may not sell"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"may not sell"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.pdflib.com/fileadmin/pdflib/products/more/jpeg2ps/
HOMEPAGE=	http://www.pdflib.com/download/free-software/jpeg2ps/

REGRESS_TARGET=	test
MAKE_FLAGS=	CFLAGS='${CFLAGS} -c' LD=${_PASS_CC:T:Q}

.include <bsd.port.mk>
