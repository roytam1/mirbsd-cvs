# $MirOS: ports/essentials/patch/Makefile,v 1.6 2008/11/08 23:03:40 tg Exp $
#-
# This port must not contain a patches/ directory.

COMMENT=		MirOS patch(1)
CATEGORIES=		essentials
DISTNAME=		patch-20091122
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/patch/}

# BSD-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/patch
.if exists(${.SYSML}/libmirmake.a)
EXTRA_XAKE_FLAGS=	LDADD="-L${.SYSMK} -lmirmake"
.endif

.include <bsd.port.mk>

_CIPHERS+=		cksum
