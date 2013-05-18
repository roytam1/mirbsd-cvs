# $MirOS: ports/multimedia/xawtv/Makefile,v 1.4 2006/02/09 11:12:11 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/11/16 16:17:58 sturm Exp $

ONLY_FOR_PLATFORM=	*:*:i386 *:*:macppc
COMMENT=			TV viewing application
DISTNAME=		xawtv-3.90
DISTFILES=		${DISTNAME:S,-,_,}.tar.gz
CATEGORIES=		x11 graphics multimedia
HOMEPAGE=		http://bytesex.org/xawtv/
MASTER_SITES=		${HOMEPAGE}

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		jpeg.62::graphics/jpeg \
			aa.1.3::graphics/aalib \
			png.2::graphics/png
MODULES+=		devel/pkgconfig

.if ${MACHINE_ARCH} == "i386"
FLAVORS=		mmx
FLAVOR?=
.  if ${FLAVOR:L:Mmmx}
CONFIGURE_ARGS+=	--enable-mmx
.  else
CONFIGURE_ARGS+=	--disable-mmx
.  endif
.endif

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-aa --disable-motif \
			--disable-alsa --disable-lirc

MAKE_FLAGS=	verbose=yes SYSCONFDIR="${SYSCONFDIR}"
NO_REGRESS=	Yes
USE_GMAKE=	Yes

post-install:
	@perl -pi -e "s,/etc/X11,${SYSCONFDIR}," ${PREFIX}/man/man5/xawtvrc.5
	${INSTALL_DATA} ${WRKSRC}/x11/Xawtv.ad \
	    ${PREFIX}/lib/X11/app-defaults/Xawtv

.include <bsd.port.mk>
