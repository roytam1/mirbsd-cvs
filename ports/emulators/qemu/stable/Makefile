# $MirOS: ports/emulators/qemu/stable/Makefile,v 1.3 2008/10/04 19:03:06 tg Exp $
# $OpenBSD: Makefile,v 1.7 2005/11/05 12:11:05 todd Exp $

# no success on other platforms yet
ONLY_FOR_PLATFORMS=	MirBSD:*:* \
			OpenBSD:*:amd64 OpenBSD:*:i386 OpenBSD:*:macppc

COMMENT=		fast multi-system emulator
DISTNAME=		qemu-0.7.2
DASH_VER=		4
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
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q} \
			--cc=${_PASS_CC:T:Q} \
			--make=${GMAKE:Q} \
			--interp-prefix=${LOCALBASE:Q}/share/qemu/gnemul-%M \
			--extra-cflags=${CFLAGS:M*:Q} \
			--extra-ldflags=${LDFLAGS:M*:Q} \
			--enable-adlib
CONFIGURE_ARGS+=	--enable-werror

.include <mirports.sys.mk>

FILESDIR=		${.CURDIR}/../files

.if ${MACHINE_ARCH} == "amd64"
PATCH_LIST=		patch-* misc-*
.endif

post-extract:
	cp ${FILESDIR}/{gnu-c99-math,kqemu,vgafont}.h ${WRKSRC}/

.include <bsd.port.mk>
