# $MirOS: ports/emulators/qemu/Makefile,v 1.8 2007/06/30 02:31:28 tg Exp $
# $OpenBSD: Makefile,v 1.32 2008/04/28 22:52:38 todd Exp $

# no success building on other platforms yet
ONLY_FOR_PLATFORMS=	\
			MirBSD:*:i386 \
			OpenBSD:*:amd64 \
			OpenBSD:*:i386 \
			OpenBSD:*:macppc

COMMENT=		multi system emulator
DISTNAME=		qemu-0.9.1
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/
MASTER_SITES=		${HOMEPAGE}

# GPLv2/LGPLv2/BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

BUILD_DEPENDS+=		::textproc/texi2html
LIB_DEPENDS+=		SDL::devel/sdl
USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q} \
			--cc=${CC:Q} \
			--interp-prefix=${LOCALBASE:Q}/share/qemu/gnemul-%M \
			--extra-cflags=${CFLAGS:M*:Q} \
			--extra-ldflags=${LDFLAGS:M*:Q} \
			--enable-adlib \
			--disable-vnc-tls
#CONFIGURE_ARGS+=	--enable-werror
CPPFLAGS+=		-DMPPREFIX=\"${LOCALBASE:Q}\"

# Currently, the regression tests are utterly broken.
REGRESS_TARGET=		test test2

.if ${MACHINE_ARCH} == "amd64"
PATCH_LIST=		patch-* misc-*
.endif

post-extract:
	cp ${FILESDIR}/{{gnu-c99-math,vgafont}.h,scn.c} ${WRKSRC}/

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/qemu
	${INSTALL_SCRIPT} ${FILESDIR}/qemu-if{up,down} \
	    ${PREFIX}/share/examples/qemu/

.include <bsd.port.mk>
