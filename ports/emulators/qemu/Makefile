# $MirOS$

COMMENT=		"fast x86-32 emulator"
DISTNAME=		qemu-0.6.1
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/
MASTER_SITES=		${HOMEPAGE}

PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		SDL::devel/sdl
USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--cc="${CC}" \
			--make="${GMAKE}" \
			--extra-cflags="${CFLAGS}" \
			--extra-ldflags="${LDFLAGS}"

.include <bsd.port.mk>
