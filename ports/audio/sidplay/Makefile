# $OpenBSD: Makefile,v 1.3 2003/01/23 01:56:21 naddy Exp $

COMMENT=			Commodore 64 music player and SID chip emulator

DISTNAME=	sidplay-base-1.0.9
PKGNAME=	${DISTNAME:S/-base//}-0
CATEGORIES=	audio

HOMEPAGE=	http://www.geocities.com/SiliconValley/Lakes/5147/sidplay/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}packages/
EXTRACT_SUFX=	.tgz

LIB_DEPENDS=	sidplay.1::audio/libsidplay

USE_CXX=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--with-sidplay-includes=${LOCALBASE}/include \
		--with-sidplay-library=${LOCALBASE}/lib

.include <bsd.port.mk>
