# $MirOS: ports/emulators/qemu/snapshot/Makefile,v 1.5 2009/10/17 21:43:52 tg Exp $
# $OpenBSD: Makefile,v 1.32 2008/04/28 22:52:38 todd Exp $
# $NetBSD: Makefile,v 1.60 2009/10/11 16:04:13 asau Exp $

# no success building on other platforms yet
ONLY_FOR_PLATFORMS=	\
			MirBSD:*:i386 \
			OpenBSD:*:i386 \
			OpenBSD:*:macppc

COMMENT=		multi system emulator
DISTNAME=		qemu-0.11.0
CATEGORIES=		emulators
HOMEPAGE=		http://wiki.qemu.org/Index.html
MASTER_SITES=		http://download.savannah.gnu.org/releases/qemu/

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
FILESDIR=		${.CURDIR}/../files
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q} \
			--interp-prefix=${LOCALBASE:Q}/share/qemu/gnemul-%M \
			--cc=${_PASS_CC:T:Q} \
			--make=${GMAKE:Q} \
			--audio-card-list='ac97 es1370 sb16 adlib'
#CONFIGURE_ARGS+=	--enable-werror
CPPFLAGS+=		-DMPPREFIX=\"${LOCALBASE:Q}\"
EXTRA_XAKE_FLAGS+=	V=1
EXTRA_XAKE_FLAGS+=	INSTALL_DIR=${INSTALL_DATA_DIR:Q}
VMEM_WARNING=		Yes

# Currently, the regression tests are utterly broken.
NO_REGRESS=		Yes

post-extract:
	cp ${FILESDIR}/{{gnu-c99-math,vgafont}.h,scn.c} ${WRKSRC}/

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/qemu
	${INSTALL_SCRIPT} ${FILESDIR}/qemu-if{up,down} \
	    ${FILESDIR}/Makefile.multinode-NetBSD \
	    ${PREFIX}/share/examples/qemu/

.include <bsd.port.mk>
