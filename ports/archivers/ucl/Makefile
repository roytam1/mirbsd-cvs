# $MirOS: ports/archivers/ucl/Makefile,v 1.3 2006/02/09 09:35:35 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/05/24 02:40:42 jolan Exp $

COMMENT=			portable lossless data compression library

DISTNAME=	ucl-1.01
CATEGORIES=	archivers devel

HOMEPAGE=	http://www.oberhumer.com/opensource/ucl


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}/download/

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS=	:nasm-*:lang/nasm
.endif

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} --enable-static
MAKE_FLAGS=		CFLAGS_O=""

.include <bsd.port.mk>
