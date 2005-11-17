# $MirOS: ports/emulators/qemu/Makefile,v 1.3 2005/11/15 12:25:06 tg Exp $
# $OpenBSD: Makefile,v 1.7 2005/11/05 12:11:05 todd Exp $

ONLY_FOR_PLATFORMS=	MirBSD:*:i386

COMMENT=		"fast i386 emulator with kernel module"
V_EMU=			20051117
V_QVM=			20051117
PKGNAME=		qvm86-${V_QVM}-0
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/ \
			http://savannah.nongnu.org/qvm86/
DISTFILES=		qemu-${V_EMU}.cgz \
			qvm86-${V_QVM}.cgz:0
MASTER_SITES=		#XXX

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		::textproc/texi2html
LIB_DEPENDS=		SDL::devel/sdl
USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--cc="${CC}" \
			--make="${GMAKE}" \
			--interp-prefix="${LOCALBASE}/share/qemu/gnemul-%M" \
			--target-list=i386-softmmu \
			--extra-cflags="${CFLAGS}" \
			--extra-ldflags="${LDFLAGS}" \
			--enable-adlib \
			--disable-qvm86 \
			--disable-kqemu

.include <mirports.sys.mk>
COPTS+=			-fno-stack-protector

WRKDIST=		${WRKDIR}/qemu

post-extract:
	@mv ${WRKDIR}/qvm86 ${WRKDIST}/

pre-patch:
	@cd ${WRKSRC} && ${PATCH} ${PATCH_DIST_ARGS} -l <qvm86/patch.qvm86

.include <bsd.port.mk>
