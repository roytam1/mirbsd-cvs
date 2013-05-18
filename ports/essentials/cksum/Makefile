# $MirOS: ports/essentials/cksum/Makefile,v 1.27 2009/11/22 21:41:54 tg Exp $

COMMENT=		MirOS cksum(1) with multiple hash algorithms
CATEGORIES=		essentials
DISTNAME=		mircksum-20091122
DASH_VER=		1
PKGNAME=		${DISTNAME:S/^mir//}-${DASH_VER}
EXTRACT_SUFX=		.cpio.gz
#HOMEPAGE=		http://www.mirbsd.org/mircksum.htm
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cksum/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

WRKDIST=		${WRKDIR}/cksum

BUILD_DEPENDS+=		:mirmake->=20091122:devel/mirmake

post-install:
	cd ${PREFIX}/bin && ${MAKE} -f ${WRKSRC}/Makefile algos

.include <bsd.port.mk>

_CIPHERS+=		cksum
