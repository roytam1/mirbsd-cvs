# $MirOS: ports/essentials/cpio/Makefile,v 1.3 2005/11/10 20:12:35 tg Exp $
#-
# This port must not contain a patches/ directory.

COMMENT=		"MirOS cpio(1), pax(1) and tar(1)"
CATEGORIES=		essentials
DISTNAME=		paxmirabilis-20051110
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cpio/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/pax

# For bootstrapping
EXTRACT_CASES+=		*.cpio.gz) ${GZIP_CMD} -dc \
			    ${FULLDISTDIR}/$$archive | cpio -id ;;

.include <bsd.port.mk>

_CIPHERS+=		cksum
