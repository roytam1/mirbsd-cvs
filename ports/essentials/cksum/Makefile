# $MirOS: ports/essentials/cksum/Makefile,v 1.20 2008/02/10 11:38:43 bsiegert Exp $

COMMENT=		MirOS cksum(1) with multiple hash algorithms
CATEGORIES=		essentials
DISTNAME=		cksum-20080309
EXTRACT_SUFX=		.cgz
#HOMEPAGE=		http://www.mirbsd.org/mircksum.htm
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cksum/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

WRKDIST=		${WRKDIR}/cksum
#CPPFLAGS+=		-isystem ${.SYSMK} -D_MIRMAKE_DEFNS

BUILD_DEPENDS+=		:mirmake->=20080309:devel/mirmake

.include <bsd.port.mk>

_CIPHERS+=		cksum
