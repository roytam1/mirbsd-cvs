# $MirOS: ports/essentials/cksum/Makefile,v 1.14 2006/06/23 15:30:14 tg Exp $

COMMENT=		"MirOS cksum(1)"
CATEGORIES=		essentials
DISTNAME=		cksum-20060623
EXTRACT_SUFX=		.cgz
HOMEPAGE=		http://wiki.mirbsd.de/MirCksum
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cksum/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

WRKDIST=		${WRKDIR}/cksum
CPPFLAGS+=		-isystem ${.SYSMK} -D_MIRMAKE_DEFNS

.if ${OBJECT_FMT} == "PE"
MAKE_ENV+=		AFLAGS=-DUNDERSCORES
.endif

.include <bsd.port.mk>

_CIPHERS+=		cksum
