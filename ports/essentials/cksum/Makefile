# $MirOS: ports/essentials/cksum/Makefile,v 1.12 2006/05/26 22:08:55 tg Exp $

.if ${.SYSMK} == "/usr/share/mk"
IGNORE+=		"only works with MirMake"
.endif

COMMENT=		"MirOS cksum(1)"
CATEGORIES=		essentials
DISTNAME=		cksum-20060526
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
LDADD+=			-L${.SYSMK} -lmirmake

.if ${OBJECT_FMT} == "PE"
MAKE_ENV+=		AFLAGS=-DUNDERSCORES
.endif

.include <bsd.port.mk>

_CIPHERS+=		cksum
