# $MirOS: ports/essentials/cksum/Makefile,v 1.7 2005/09/12 22:45:37 tg Exp $

.if ${.SYSMK} == "/usr/share/mk"
ERRORS+=		"This port only works with MirMake"
.endif

COMMENT=		"MirOS cksum(1)"
CATEGORIES=		essentials
DISTNAME=		mircksum-20050912
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://wiki.mirbsd.de/MirCksum
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cksum/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/md5
CPPFLAGS+=		-isystem ${.SYSMK}
EXTRA_XAKE_FLAGS=	LDADD="-L${.SYSMK} -lmirmake"

.include <mirports.sys.mk>

.if ${OBJECT_FMT} == "PE"
MAKE_ENV+=		AFLAGS=-DUNDERSCORES
.endif

.include <bsd.port.mk>

_CIPHERS+=		cksum
