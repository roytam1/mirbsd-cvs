# $MirOS$

COMMENT=		deflate compression library
CATEGORIES=		essentials
DISTNAME=		zlib-1.2.8
HOMEPAGE=		http://zlib.net/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# zlib
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE} \
			${MASTER_SITE_SOURCEFORGE:=libpng/}

do-patch:
	@echo
	@echo This port is mostly for downloading.
	@echo Only really of interest on Interix…
	@echo
	@exit 1

.include <bsd.port.mk>
