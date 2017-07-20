# $MirOS$

COMMENT=		lzip compression and decompression copyfree tools
DISTNAME=		pdlzip-1.8
CATEGORIES=		archivers
HOMEPAGE=		http://www.nongnu.org/lzip/pdlzip.html
MASTER_SITES=		http://download.savannah.gnu.org/releases/lzip/pdlzip/

# 2-clause BSD; see also DESCR
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q} \
			--datarootdir=${PREFIX:Q}/share \
			--infodir=${PREFIX:Q}/info \
			--mandir=${PREFIX:Q}/man
EXTRA_MAKE_FLAGS+=	CPPFLAGS=${CPPFLAGS:Q} \
			CFLAGS=${CFLAGS:Q} \
			LDFLAGS=${LDFLAGS:Q}
REGRESS_TARGET=		check

.include <bsd.port.mk>
