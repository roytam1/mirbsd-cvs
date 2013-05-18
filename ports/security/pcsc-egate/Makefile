# $MirOS: ports/security/pcsc-egate/Makefile,v 1.3 2005/07/07 21:26:12 bsiegert Exp $

COMMENT=			Smartcard backend driver for egate tokens
DISTNAME=		ifd-egate-0.05
PKGNAME=		${DISTNAME}-2
CATEGORIES=		security
MASTER_SITES=		http://secure.netroedge.com/~phil/egate/
HOMEPAGE=		http://www.linuxnet.com/sourcedrivers.html

# 3-clause UCB licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
LIB_DEPENDS+=		usb.7::devel/libusb
BUILD_DEPENDS+=		:pcsc-lite->=1.2:security/pcsc-lite
RUN_DEPENDS+=		:pcsc-lite->=1.2:security/pcsc-lite

INSTALL_TARGET=		myinstall

post-extract:
	cp ${FILESDIR}/Makefile ${WRKSRC}

.include <bsd.port.mk>
