# $MirOS: ports/math/grace/Makefile,v 1.6 2008/10/16 19:43:54 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/01/11 11:12:52 sturm Exp $
# $FreeBSD: ports/math/grace/Makefile,v 1.18 2001/04/25 05:59:19 lkoeller Exp $

COMMENT=		GRaphing, Advanced Computation and Exploration of data
DISTNAME=		grace-5.1.14
CATEGORIES=		math
HOMEPAGE=		http://plasma-gate.weizmann.ac.il/Grace/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

GRACE_SITES=	ftp://plasma-gate.weizmann.ac.il/pub/grace/src/ \
		ftp://ftp.fu-berlin.de/unix/graphics/grace/src/ \
		ftp://ftp.u-aizu.ac.jp/pub/SciEng/math/grace/src/ \
		ftp://freedom7.swmed.edu/pub/mirrors/grace/src/
MASTER_SITES=	${GRACE_SITES} ${GRACE_SITES:S/\/$/\/old\//g} \
		${MASTER_SITE_FINK}

CONFIGURE_STYLE=	gnu
MODGNU_RECURSE_DIRS=	${WRKSRC}/ac-tools
CONFIGURE_ARGS+=	--with-bundled-xbae \
			--with-extra-incpath=${LOCALBASE}/include:${LOCALBASE}/include/libpng \
			--with-extra-ldpath=${LOCALBASE}/lib \
			--enable-grace-home=${PREFIX}/grace

LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		t1.5::devel/t1lib \
		tiff.35::graphics/tiff \
		pdf.2::print/pdflib
MODULES+=		graphics/png

FLAVOURS=	no_x11 fftw netcdf xmhtml
FLAVOUR?=

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
NO_REGRESS=		Yes
.  if ${FLAVOUR:L:Mxmhtml}
ERRORS+=	"Fatal: Flavours 'no_x11' and 'xmhtml' are mutually exclusive."
.  endif
.else
# 'make regress' needs X11 running
REGRESS_IS_INTERACTIVE=	Yes
REGRESS_FLAGS=		DISPLAY=${DISPLAY}
USE_X11=		Yes
USE_MOTIF=		openmotif
.  if ${FLAVOUR:L:Mxmhtml}
LIB_DEPENDS+=		XmHTML.1::www/xmhtml
CONFIGURE_ARGS+=	--enable-xmhtml
.  else
CONFIGURE_ARGS+=	--disable-xmhtml
.  endif
.endif

.if ${FLAVOUR:L:Mfftw}
LIB_DEPENDS+=		fftw.2::math/fftw
CONFIGURE_ARGS+=	--with-fftw
.else
CONFIGURE_ARGS+=	--without-fftw
.endif

.if ${FLAVOUR:L:Mnetcdf}
LIB_DEPENDS+=		netcdf.1::math/netcdf
CONFIGURE_ARGS+=	--enable-netcdf
.else
CONFIGURE_ARGS+=	--disable-netcdf
.endif

.include <bsd.port.mk>
