# $MirOS: ports/benchmarks/pear-Benchmark/Makefile,v 1.4 2006/09/14 00:07:25 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:32:52 avsm Exp $

COMMENT=	framework to benchmark PHP scripts or function calls

V=		1.2.1
DISTNAME=	Benchmark-${V}
PKGNAME=	pear-Benchmark-${V}-0
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
