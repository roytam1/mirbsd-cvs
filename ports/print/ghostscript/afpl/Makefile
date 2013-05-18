# $MirOS: ports/print/ghostscript/afpl/Makefile,v 1.5 2005/12/29 20:04:59 tg Exp $
# $OpenBSD: Makefile,v 1.20 2004/05/23 18:51:59 sturm Exp $

COMMENT=		"AFPL PostScript interpreter"
VERSION=		8.53
DISTNAME=		ghostscript-${VERSION}
CATEGORIES=		print lang textproc
DIR=			AFPL/gs${VERSION:S/.//}
MASTER_SITES=		${GS_SITES}
MASTER_SITES1=		${PDF_SITES}
HOMEPAGE=		http://www.cs.wisc.edu/~ghost/

SUBST_VARS+=		VERSION
DIST_SUBDIR=		gs

# Aladdin license
# License: COPY GPL BSD
PERMIT_DISTFILES_CDROM=	"Aladdin wants fee for commercial redistribution"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"Aladdin wants fee for commercial redistribution"
PERMIT_PACKAGE_FTP=	Yes

JPEGDIR=		graphics/jpeg
PNGDIR=			graphics/png

BUILD_DEPENDS+=		::${JPEGDIR}:patch ::${PNGDIR}:patch
RUN_DEPENDS+=		:gs-fonts-std-*:print/ghostscript/fonts-std
MODULES+=		graphics/png

WRKDIST=		${WRKDIR}/${DISTNAME}
WRKSRC=			${WRKDIST}/src
WRKBUILD=		${WRKDIST}
BASE_FLAGS=		INSTALL_PROGRAM='${INSTALL_SCRIPT}' \
			INSTALL_DATA='${INSTALL_DATA}' \
			SHARE_LIBPNG=1 \
			SHARE_ZLIB=1 \
			CFLAGS_STANDARD='${CFLAGS}' \
			XLDFLAGS=-L${LOCALBASE}/lib \
			XINCLUDE=-I${X11BASE}/include \
			XLIBS='Xt SM ICE Xext X11' \
			XLIBDIRS=-L${X11BASE}/lib \
			GLOBJDIR=./objects \
			GLGENDIR=./objects \
			PSOBJDIR=./objects \
			PSGENDIR=./objects \
			STDLIBS='-pthread -lm'

PDFDIR=			share/ghostscript/${VERSION}/lib

BASE_FLAGS+=		DEVICE_DEVS1='\
$$(DD)x11.dev $$(DD)x11alpha.dev $$(DD)x11cmyk.dev $$(DD)x11cmyk2.dev \
$$(DD)x11cmyk4.dev $$(DD)x11cmyk8.dev $$(DD)x11gray2.dev \
$$(DD)x11gray4.dev $$(DD)x11mono.dev $$(DD)cljet5.dev $$(DD)deskjet.dev \
$$(DD)djet500.dev $$(DD)laserjet.dev $$(DD)ljet2p.dev $$(DD)ljet3.dev \
$$(DD)ljet3d.dev $$(DD)ljet4.dev $$(DD)ljetplus.dev $$(DD)lj5mono.dev \
$$(DD)lj5gray.dev $$(DD)lp2563.dev $$(DD)oce9050.dev $$(DD)faxg3.dev \
$$(DD)faxg32d.dev $$(DD)faxg4.dev $$(DD)tiffcrle.dev $$(DD)tiffg3.dev \
$$(DD)tiffg32d.dev $$(DD)tiffg4.dev $$(DD)epswrite.dev $$(DD)pdfwrite.dev \
$$(DD)pswrite.dev $$(DD)pxlmono.dev $$(DD)pxlcolor.dev $$(DD)bit.dev \
$$(DD)bitrgb.dev $$(DD)bitcmyk.dev $$(DD)bmpmono.dev $$(DD)bmp16.dev \
$$(DD)bmp256.dev $$(DD)bmp16m.dev $$(DD)cgmmono.dev $$(DD)cgm8.dev \
$$(DD)cgm24.dev $$(DD)jpeg.dev $$(DD)jpeggray.dev $$(DD)miff24.dev \
$$(DD)pcxmono.dev $$(DD)pcxgray.dev $$(DD)pcx16.dev $$(DD)pcx256.dev \
$$(DD)pcx24b.dev $$(DD)pcxcmyk.dev $$(DD)pbm.dev $$(DD)pbmraw.dev \
$$(DD)pgm.dev $$(DD)pgmraw.dev $$(DD)pgnm.dev $$(DD)pgnmraw.dev \
$$(DD)pnm.dev $$(DD)pnmraw.dev $$(DD)ppm.dev $$(DD)ppmraw.dev \
$$(DD)pkm.dev $$(DD)pkmraw.dev $$(DD)plan9bm.dev $$(DD)pngmono.dev \
$$(DD)pnggray.dev $$(DD)png16.dev $$(DD)png256.dev $$(DD)png16m.dev \
$$(DD)psmono.dev $$(DD)psgray.dev $$(DD)psrgb.dev $$(DD)tiff12nc.dev \
$$(DD)tiff24nc.dev $$(DD)tiffgray.dev $$(DD)tiff32nc.dev $$(DD)tiffsep.dev \
$$(DD)tifflzw.dev $$(DD)tiffpack.dev $$(DD)ap3250.dev \
$$(DD)appledmp.dev $$(DD)bj10e.dev $$(DD)bj200.dev $$(DD)bjc600.dev \
$$(DD)bjc800.dev $$(DD)cdeskjet.dev $$(DD)cdjcolor.dev \
$$(DD)cdjmono.dev $$(DD)cdj500.dev $$(DD)cdj550.dev \
$$(DD)declj250.dev $$(DD)djet500c.dev $$(DD)dnj650c.dev $$(DD)epson.dev \
$$(DD)eps9mid.dev $$(DD)eps9high.dev $$(DD)epsonc.dev $$(DD)hl7x0.dev \
$$(DD)ibmpro.dev $$(DD)imagen.dev $$(DD)iwhi.dev $$(DD)iwlo.dev \
$$(DD)iwlq.dev $$(DD)jetp3852.dev \
$$(DD)lbp8.dev $$(DD)lips3.dev \
$$(DD)lj250.dev $$(DD)lj4dith.dev $$(DD)lp8000.dev \
$$(DD)lq850.dev $$(DD)m8510.dev $$(DD)necp6.dev $$(DD)oki182.dev \
$$(DD)okiibm.dev $$(DD)paintjet.dev $$(DD)pj.dev $$(DD)pjetxl.dev \
$$(DD)pjxl.dev $$(DD)pjxl300.dev $$(DD)r4081.dev $$(DD)sj48.dev \
$$(DD)st800.dev $$(DD)stcolor.dev $$(DD)t4693d2.dev $$(DD)t4693d4.dev \
$$(DD)t4693d8.dev $$(DD)tek4696.dev $$(DD)uniprint.dev \
$$(DD)dfaxhigh.dev $$(DD)dfaxlow.dev $$(DD)cif.dev \
$$(DD)sgirgb.dev $$(DD)ps2write.dev'


MAKE_FLAGS=		${BASE_FLAGS} prefix=${PREFIX}
CFLAGS+=		-DSYS_TYPES_HAS_STDINT_TYPES
ALL_TARGET=		all
INSTALL_TARGET=		install

FLAVORS=		A4 gtk
FLAVOR?=		A4

.if ${FLAVOR:U:MA4}
CFLAGS+=		-DA4
.endif

.if ${FLAVOR:L:Mgtk}
LIB_DEPENDS+=		gtk.1::x11/gtk+1
ALL_TARGET+=		so
INSTALL_TARGET+=	soinstall
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
.else
end_install=
.endif

NO_REGRESS=		Yes

FAKE_FLAGS=		${BASE_FLAGS} prefix=${WRKINST}${PREFIX}

post-extract:
	ln -s ${WRKDIR}/${JPEGDIR}/jpeg* ${WRKDIST}/jpeg
	ln -s ${WRKDIR}/${PNGDIR}/libpng* ${WRKDIST}/libpng

do-configure:
	cd ${WRKBUILD} && ln -s ${WRKSRC}/unix-gcc.mak Makefile

pre-build:
	mkdir -p ${WRKDIST}/objects
	mkdir -p ${WRKDIST}/bin
	mkdir -p ${WRKDIST}/soobj
	mkdir -p ${WRKDIST}/sobin

post-install:
	chmod 600 ${PREFIX}/bin/gs && strip ${PREFIX}/bin/gs
	chmod ${BINMODE} ${PREFIX}/bin/gs
	cd ${PREFIX}/man/man1 && \
		ln -sf ps2ps.1 eps2eps.1 && \
		ln -sf gslp.1 gsbj.1 && \
		ln -sf gslp.1 gsdj.1 && \
		ln -sf gslp.1 gsdj500.1 && \
		ln -sf gslp.1 gslj.1 && \
		ln -sf ps2pdf.1 ps2pdf12.1 && \
		ln -sf ps2pdf.1 ps2pdf13.1 && \
		ln -sf ps2pdf.1 ps2pdf14.1
	cd ${PREFIX}/man/de/man1 && \
		ln -sf ps2pdf.1 ps2pdf12.1 && \
		ln -sf ps2pdf.1 ps2pdf13.1 && \
		ln -sf ps2pdf.1 ps2pdf14.1 && \
		ln -sf ps2ps.1 eps2eps.1

.include <bsd.port.mk>
