# $MirOS: ports/essentials/cksum/Makefile,v 1.18 2006/11/07 00:32:03 tg Exp $

COMMENT=		MirOS cksum(1) with multiple hash algorithms
CATEGORIES=		essentials
DISTNAME=		cksum-20061013
EXTRACT_SUFX=		.cgz
#HOMEPAGE=		http://wiki.mirbsd.de/MirCksum
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cksum/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

WRKDIST=		${WRKDIR}/md5
CPPFLAGS+=		-isystem ${.SYSMK} -D_MIRMAKE_DEFNS

.if ${OBJECT_FMT} == "PE"
MAKE_ENV+=		AFLAGS=-DUNDERSCORES
.endif

BUILD_DEPENDS+=		:mirmake->=20061228:devel/mirmake

.include <bsd.port.mk>

_CIPHERS+=		cksum
