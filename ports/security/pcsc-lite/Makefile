# $MirOS: ports/security/pcsc-lite/Makefile,v 1.6 2007/04/16 18:29:53 bsiegert Exp $

COMMENT=		Smartcard middleware
DISTNAME=		pcsc-lite-1.2.0
PKGNAME=		${DISTNAME}-2
CATEGORIES=		security
MASTER_SITES=		http://alioth.debian.org/download.php/419/
HOMEPAGE=		http://alioth.debian.org/projects/pcsclite/

# UCB-style licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		debug
FLAVOUR?=

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-libusb=${LOCALBASE} \
			--enable-usbdropdir=${LOCALBASE}/libexec/pcsc/drivers \
			--enable-muscledropdir=${LOCALBASE}/libexec/pcsc/services
CONFIGURE_ENV+=		PTHREAD_LIBS=-pthread PTHREAD_CFLAGS=-pthread

LIB_DEPENDS+=		usb.7::devel/libusb
USE_GMAKE=		Yes
USE_CXX=		Yes # depends on libusb, which uses CXX

.include <mirports.sys.mk>
.if ${FLAVOUR:L:Mdebug}
CFLAGS+=		-DPCSC_DEBUG -DATR_DEBUG
CONFIGURE_ARGS+=	--enable-debug --enable-debugatr
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/pcsc-lite
	mv ${WRKINST}/etc/reader.conf ${PREFIX}/share/examples/pcsc-lite/

.include <bsd.port.mk>
