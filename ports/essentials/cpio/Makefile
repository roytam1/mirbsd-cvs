# $MirOS: ports/essentials/cksum/Makefile,v 1.7 2005/09/12 22:45:37 tg Exp $

COMMENT=		"MirOS cpio(1), pax(1) and tar(1)"
CATEGORIES=		essentials
DISTNAME=		paxmirabilis-20050912
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cpio/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/pax
#CPPFLAGS+=		-isystem ${.SYSMK}
#EXTRA_XAKE_FLAGS=	LDADD="-L${.SYSMK} -lmirmake"

.include <bsd.port.mk>
