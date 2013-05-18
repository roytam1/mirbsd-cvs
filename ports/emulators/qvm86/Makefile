# $MirOS: ports/emulators/qvm86/Makefile,v 1.7 2006/02/01 15:42:15 tg Exp $
# $OpenBSD: Makefile,v 1.7 2005/11/05 12:11:05 todd Exp $

BROKEN=			problems with network, sound, etc.

ONLY_FOR_PLATFORMS=	MirBSD:*:i386

COMMENT=			fast i386 emulator with kernel module
PKGNAME=		${_CVS_DISTF0:R}-0
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/ \
			http://savannah.nongnu.org/qvm86/
CVS_DISTREPO=		anoncvs@savannah.nongnu.org:/cvsroot/qemu
CVS_DISTDATE=		2005/11/17 15:00
CVS_DISTMODS=		qemu
CVS_DISTFILE=		qemu
CVS_DISTREPO0=		anoncvs@savannah.nongnu.org:/cvsroot/qvm86
CVS_DISTDATE0=		2005/11/17 15:00
CVS_DISTMODS0=		qvm86
CVS_DISTFILE0=		qvm86

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
			--disable-kqemu

.include <mirports.sys.mk>
COPTS+=			-fno-stack-protector

WRKDIST=		${WRKDIR}/qemu
QVMLKMFILES=		Makefile.bsdlkm lkm
LKMDIR=			${TRUEPREFIX}/share/qemu/lkm

MAKE_ENV+=		BSDMAKE=/usr/bin/make
MAKE_ENV+=		LKMDIR=${LKMDIR}

SMKVER!=		print $$((${OSver:R} * 256 + ${OSver:E}))
.if ${SMKVER} < 2106
IGNORE+=		"requires a newer system make(1), please upgrade"
.endif

post-extract:
	@mv ${WRKDIR}/qvm86 ${WRKDIST}/
	@cd ${FILESDIR} && find ${QVMLKMFILES} -type f \
	    | cpio -pdu ${WRKDIST}/qvm86/

pre-patch:
	@cd ${WRKSRC} && ${PATCH} ${PATCH_DIST_ARGS} -l <qvm86/patch.qvm86

pre-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${LKMDIR}

.include <bsd.port.mk>
