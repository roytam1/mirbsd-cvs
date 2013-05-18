# $MirOS: ports/emulators/qemu/Makefile,v 1.5 2006/09/14 00:09:10 tg Exp $
# $OpenBSD: Makefile,v 1.7 2005/11/05 12:11:05 todd Exp $

# no success on other platforms yet
ONLY_FOR_PLATFORMS=	MirBSD:*:* \
			OpenBSD:*:amd64 OpenBSD:*:i386 OpenBSD:*:macppc

COMMENT=		fast multi-system emulator
DISTNAME=		qemu-0.7.2
PKGNAME=		${DISTNAME}-2
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/
MASTER_SITES=		${HOMEPAGE}

PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		::textproc/texi2html
LIB_DEPENDS=		SDL::devel/sdl
USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--cc=${CC:Q} \
			--make=${GMAKE:Q} \
			--interp-prefix=${LOCALBASE:Q}/share/qemu/gnemul-%M \
			--extra-cflags=${CFLAGS:M*:Q} \
			--extra-ldflags=${LDFLAGS:M*:Q} \
			--enable-adlib \
			--disable-kqemu

.include <mirports.sys.mk>
.if ${MACHINE_ARCH} == "amd64"
PATCH_LIST=		patch-* misc-*
.endif

.include <bsd.port.mk>
