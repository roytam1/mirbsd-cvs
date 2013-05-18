# $MirOS: ports/devel/silc-toolkit/Makefile,v 1.2 2005/07/07 21:20:30 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/04/11 21:25:13 jolan Exp $

COMMENT=			toolkit for the development of SILC applications
DISTNAME=	silc-toolkit-0.9.12
PKGNAME=	${DISTNAME}-1
CATEGORIES=	devel
MASTER_SITES=	http://www.silcnet.org/download/toolkit/sources/
HOMEPAGE=	http://www.silcnet.org/software/developers/toolkit/

BROKEN=		Include files need updating

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS+=	gmp::devel/gmp
MODULES=	converters/libiconv
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=${CONFIGURE_SHARED} \
		--enable-ipv6 \
		--without-irssi \
		--without-silcd \
		--with-gmp \
		--with-docdir=${PREFIX}/share/doc/silc \
		--includedir=${PREFIX}/include/silc

.if (${MACHINE_ARCH} != "i386")
CONFIGURE_ARGS+=	--disable-asm
.endif

.include <bsd.port.mk>
