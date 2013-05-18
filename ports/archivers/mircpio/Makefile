# $MirOS: ports/archivers/mircpio/Makefile,v 1.13 2007/02/17 19:50:23 tg Exp $
#-
# This port must not contain a patches/ directory.
# The distfile must be plain old cpio, not bcpio, odc, ..., SVR4 or tar.

COMMENT=		MirOS cpio(1), pax(1) and tar(1)
CATEGORIES=		archivers essentials
DISTNAME=		paxmirabilis-20080314
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@MirBSD.de>
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
