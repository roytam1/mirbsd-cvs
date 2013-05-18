# $MirOS: ports/print/ghostscript/esp/Makefile,v 1.7 2006/11/08 18:59:12 bsiegert Exp $

COMMENT=		ESP Ghostscript, a PostScript interpreter
VERSION=		8.15.3
DISTNAME=		espgs-${VERSION}-source
PKGNAME=		ghostscript-${VERSION}-${DASH_VER}
CATEGORIES=		print
HOMEPAGE=		http://www.cups.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.easysw.com/pub/ghostscript/${VERSION}/ \
			ftp://ftp2.easysw.com/pub/ghostscript/${VERSION}/ \
			ftp://ftp.funet.fi/pub/mirrors/ftp.easysw.com/pub/ghostscript/${VERSION}/  \
			ftp://ftp.mpg.goe.ni.schule.de/pub/internet/printing/ghostscript/${VERSION}/  \
			ftp://ftp.ntua.gr/pub/gnu/ghostscript/${VERSION}/  \
			ftp://ftp.fisek.com.tr/pub/ghostscript/${VERSION}/ 

EXTRACT_SUFX=		.tar.bz2
WRKDIST=		${WRKDIR}/${DISTNAME:S/-source//}

LIB_DEPENDS=		jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
RUN_DEPENDS=		:gs-fonts-std-*:print/ghostscript/fonts-std
MODULES+=		graphics/png converters/libiconv devel/pkgconfig

FAKE_FLAGS=		BINMODE=${BINMODE} \
			SHAREMODE=${SHAREMODE}
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf dest no-autoheader
AUTOCONF_NEW=		Yes

CONFIGURE_ENV+=		DSOFLAGS="${LDFLAGS}"
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --with-ijs \
			--with-fontpath=${LOCALBASE}/share/ghostscript/fonts \
			--without-omni

NO_REGRESS=		Yes

FLAVORS=		no_x11 cups
FLAVOR?=

.include <mirports.sys.mk>

CFLAGS+=		-DA4

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
USE_X11=		Yes
CONFIGURE_ARGS+=	--with-x
.endif

.if ${FLAVOR:L:Mcups}
USE_CXX=		Yes  # depends on cups, which needs C++
LIB_DEPENDS+=		cups.2::print/cups \
			cupsimage.2::print/cups
CONFIGURE_ARGS+=	--enable-cups
.else
CONFIGURE_ARGS+=	--disable-cups
.endif

LIBFILES=		${WRKSRC}/lib/Fontmap ${WRKSRC}/lib/Fontmap.GS

pre-build:
	mkdir -p ${WRKDIST}/obj
	mkdir -p ${WRKDIST}/bin

pre-install:
	${INSTALL_PROGRAM_DIR} ${PREFIX}/bin
	${INSTALL_MAN_DIR} ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/libexec/cups/filter
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/cups

post-install:
.if ${FLAVOR:L:Mcups}
	${INSTALL_DATA} ${WRKSRC}/pstoraster/pstoraster.convs \
		${PREFIX}/share/examples/cups
.endif

.include <bsd.port.mk>
