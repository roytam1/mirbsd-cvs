# $MirOS: ports/benchmarks/pear-Benchmark/Makefile,v 1.5 2007/04/11 17:04:18 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:32:52 avsm Exp $

COMMENT=	framework to benchmark PHP scripts or function calls

VSN=		1.2.1
DISTNAME=	Benchmark-${VSN}
PKGNAME=	pear-Benchmark-${VSN}-${DASH_VER}
CATEGORIES=	benchmarks pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

MODULES=	www/php/pear

# PHP License
PERMIT_PACKAGE_CDROM=	dependency www/php/core is not allowed for CDROM
PERMIT_PACKAGE_FTP=	dependency www/php/core is not allowed for FTP
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
