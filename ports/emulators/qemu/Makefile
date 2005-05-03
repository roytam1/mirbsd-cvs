# $MirOS: ports/emulators/qemu/Makefile,v 1.1.7.1 2005/03/18 15:45:54 tg Exp $

COMMENT=		"fast multi-system emulator"
DISTNAME=		qemu-0.7.0
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
CONFIGURE_ARGS+=	--cc="${CC}" \
			--make="${GMAKE}" \
			--ggi-path="${LOCALBASE}" \
			--extra-cflags="${CFLAGS}" \
			--extra-ldflags="${LDFLAGS}"

.include <bsd.port.mk>
