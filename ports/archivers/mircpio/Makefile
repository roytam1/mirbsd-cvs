# $MirOS: ports/archivers/mircpio/Makefile,v 1.11 2006/09/14 00:06:49 tg Exp $
#-
# This port must not contain a patches/ directory.
# The distfile must be plain old cpio, not bcpio, odc, ..., SVR4 or tar.

COMMENT=		MirOS cpio(1), pax(1) and tar(1)
CATEGORIES=		archivers essentials
DISTNAME=		paxmirabilis-20060829
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
			    ${FULLDISTDIR}/$$archive | pax -r ;;

.include <bsd.port.mk>

_CIPHERS+=		cksum
