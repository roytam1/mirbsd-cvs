# $MirOS: ports/audio/libsidplay/Makefile,v 1.4 2005/11/03 18:39:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2002/09/14 20:09:31 naddy Exp $

COMMENT=			C64 music player and SID chip emulator library
DISTNAME=		libsidplay-1.36.59
PKGNAME=		${DISTNAME}-1
CATEGORIES=		audio
HOMEPAGE=		http://www.geocities.com/SiliconValley/Lakes/5147/sidplay/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}packages/
EXTRACT_SUFX=		.tgz
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
.if ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--enable-optfixpoint --enable-optendian
.endif

.include <bsd.port.mk>
