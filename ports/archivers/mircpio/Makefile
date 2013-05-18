# $MirOS: ports/archivers/mircpio/Makefile,v 1.23 2012/02/16 20:43:54 tg Exp $
#-
# This port must not contain a patches/ directory.
# The distfile must be plain old cpio, not bcpio, odc, ..., SVR4 or tar.

COMMENT=		MirOS cpio(1), pax(1) and tar(1)
CATEGORIES=		archivers essentials
DISTNAME=		paxmirabilis-20120520
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@MirBSD.org>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/cpio/}

# 3-clause UCB
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/pax
EXTRA_MAKE_FLAGS+=	MACROS='-mdoc -rg1'

# For bootstrapping
EXTRACT_CASES+=		*.cpio.gz) ${GZIP_CMD} -dc \
			    ${FULLDISTDIR}/$$archive | pax -r ;;

post-install:
.for _dir _ext in bin '' man/cat1 .0
.  for _name in cpio pax tar
	cd ${PREFIX}/${_dir} && ln ${_name}${_ext} mir${_name}${_ext}
.  endfor
.endfor

.include <bsd.port.mk>

_CIPHERS+=		cksum
