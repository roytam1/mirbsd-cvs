# $MirOS: ports/essentials/cpio/Makefile,v 1.3 2005/11/10 20:12:35 tg Exp $
#-
# This port must not contain a patches/ directory.

COMMENT=		"MirOS patch(1)"
CATEGORIES=		essentials
DISTNAME=		patch-20051110
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/patch/}

# BSD-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/patch

.include <bsd.port.mk>

_CIPHERS+=		cksum
