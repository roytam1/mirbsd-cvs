# $MirOS: X11/depends/freetype2/Makefile,v 1.9 2013/08/06 19:07:53 tg Exp $

.include "../Makefile.inc"
.include <bsd.own.mk>

SHLIB_VERSION=		11.3
SUBST_VARS+=		-e 's!@X11BASE@!${X11BASE}!g'
SUBST_VARS+=		-e 's!@ft_version@!2.3.12!g'

all: prereq
prereq: freetype-config freetype2.pc

freetype-config: freetype-config.in
	sed ${SUBST_VARS} <$> >$@

freetype2.pc: freetype2.in
	sed ${SUBST_VARS} <$> >$@

FT2_DIR=		${.CURDIR}/../../xc/extras/freetype2

CPPFLAGS+=		-I${FT2_DIR}/include
CPPFLAGS+=		-DFT2_BUILD_LIBRARY
CPPFLAGS+=		-DMBSD_BUILD

.PATH:			${FT2_DIR}/builds/unix

.for module in autofit autohint base bdf cache cff cid gxvalid gzip lzw \
    otlayout otvalid pcf pfr psaux pshinter psnames raster sfnt smooth \
    tools truetype type1 type42 winfonts
.PATH:			${FT2_DIR}/src/${module}
.endfor

.if ${MKC_USAP:L} != "yes"
CPPFLAGS+=		-DTT_CONFIG_OPTION_BYTECODE_INTERPRETER
.endif

LIB=			freetype
NOMAN=			Yes

  SRCS+=		ftsystem.c
  SRCS+=		ftinit.c
  SRCS+=		afangles.c
  SRCS+=		afcjk.c
  SRCS+=		afdummy.c
  SRCS+=		afglobal.c
  SRCS+=		afhints.c
  SRCS+=		afindic.c
  SRCS+=		aflatin.c
# SRCS+=		aflatin2.c
  SRCS+=		afloader.c
  SRCS+=		afmodule.c
  SRCS+=		afmparse.c
  SRCS+=		afwarp.c
  SRCS+=		bdfdrivr.c
  SRCS+=		bdflib.c
  SRCS+=		cffcmap.c
  SRCS+=		cffdrivr.c
  SRCS+=		cffgload.c
  SRCS+=		cffload.c
  SRCS+=		cffobjs.c
  SRCS+=		cffparse.c
  SRCS+=		cidgload.c
  SRCS+=		cidload.c
  SRCS+=		cidobjs.c
  SRCS+=		cidparse.c
  SRCS+=		cidriver.c
  SRCS+=		ftadvanc.c
  SRCS+=		ftapi.c
  SRCS+=		ftbbox.c
  SRCS+=		ftbdf.c
  SRCS+=		ftbitmap.c
  SRCS+=		ftcalc.c
  SRCS+=		ftcbasic.c
  SRCS+=		ftccache.c
  SRCS+=		ftccmap.c
  SRCS+=		ftcglyph.c
  SRCS+=		ftcid.c
  SRCS+=		ftcimage.c
  SRCS+=		ftcmanag.c
  SRCS+=		ftcmru.c
  SRCS+=		ftcsbits.c
  SRCS+=		ftdbgmem.c
  SRCS+=		ftfstype.c
  SRCS+=		ftgasp.c
  SRCS+=		ftgloadr.c
  SRCS+=		ftglyph.c
  SRCS+=		ftgrays.c
  SRCS+=		ftgxval.c
  SRCS+=		ftgzip.c
  SRCS+=		ftlcdfil.c
  SRCS+=		ftlzw.c
  SRCS+=		ftmm.c
  SRCS+=		ftobjs.c
  SRCS+=		ftotval.c
  SRCS+=		ftoutln.c
  SRCS+=		ftpatent.c
  SRCS+=		ftpfr.c
  SRCS+=		ftraster.c
  SRCS+=		ftrend1.c
  SRCS+=		ftrfork.c
  SRCS+=		ftsmooth.c
  SRCS+=		ftsnames.c
  SRCS+=		ftstream.c
  SRCS+=		ftstroke.c
  SRCS+=		ftsynth.c
  SRCS+=		fttrigon.c
  SRCS+=		fttype1.c
  SRCS+=		ftutil.c
  SRCS+=		ftwinfnt.c
  SRCS+=		ftxf86.c
  SRCS+=		gxvbsln.c
  SRCS+=		gxvcommn.c
  SRCS+=		gxvfeat.c
  SRCS+=		gxvjust.c
  SRCS+=		gxvkern.c
  SRCS+=		gxvlcar.c
  SRCS+=		gxvmod.c
  SRCS+=		gxvmort.c
  SRCS+=		gxvmort0.c
  SRCS+=		gxvmort1.c
  SRCS+=		gxvmort2.c
  SRCS+=		gxvmort4.c
  SRCS+=		gxvmort5.c
  SRCS+=		gxvmorx.c
  SRCS+=		gxvmorx0.c
  SRCS+=		gxvmorx1.c
  SRCS+=		gxvmorx2.c
  SRCS+=		gxvmorx4.c
  SRCS+=		gxvmorx5.c
  SRCS+=		gxvopbd.c
  SRCS+=		gxvprop.c
  SRCS+=		gxvtrak.c
  SRCS+=		otvbase.c
  SRCS+=		otvcommn.c
  SRCS+=		otvgdef.c
  SRCS+=		otvgpos.c
  SRCS+=		otvgsub.c
  SRCS+=		otvjstf.c
  SRCS+=		otvmath.c
  SRCS+=		otvmod.c
  SRCS+=		pcfdrivr.c
  SRCS+=		pcfread.c
  SRCS+=		pcfutil.c
  SRCS+=		pfrcmap.c
  SRCS+=		pfrdrivr.c
  SRCS+=		pfrgload.c
  SRCS+=		pfrload.c
  SRCS+=		pfrobjs.c
  SRCS+=		pfrsbit.c
  SRCS+=		psauxmod.c
  SRCS+=		psconv.c
  SRCS+=		pshalgo.c
  SRCS+=		pshglob.c
  SRCS+=		pshmod.c
  SRCS+=		pshrec.c
  SRCS+=		psmodule.c
  SRCS+=		psobjs.c
  SRCS+=		sfdriver.c
  SRCS+=		sfobjs.c
  SRCS+=		t1afm.c
  SRCS+=		t1cmap.c
  SRCS+=		t1decode.c
  SRCS+=		t1driver.c
  SRCS+=		t1gload.c
  SRCS+=		t1load.c
  SRCS+=		t1objs.c
  SRCS+=		t1parse.c
  SRCS+=		t42drivr.c
  SRCS+=		t42objs.c
  SRCS+=		t42parse.c
  SRCS+=		ttbdf.c
  SRCS+=		ttcmap.c
  SRCS+=		ttdriver.c
  SRCS+=		ttgload.c
  SRCS+=		ttgxvar.c
  SRCS+=		ttinterp.c
  SRCS+=		ttkern.c
  SRCS+=		ttload.c
  SRCS+=		ttmtx.c
  SRCS+=		ttobjs.c
  SRCS+=		ttpload.c
  SRCS+=		ttpost.c
  SRCS+=		ttsbit.c
  SRCS+=		winfnt.c

  INCS+=		config/ftconfig.h
  INCS+=		config/ftheader.h
  INCS+=		config/ftmodule.h
  INCS+=		config/ftoption.h
  INCS+=		config/ftstdlib.h
  INCS+=		freetype.h
  INCS+=		ftadvanc.h
  INCS+=		ftbbox.h
  INCS+=		ftbdf.h
  INCS+=		ftbitmap.h
  INCS+=		ftcache.h
  INCS+=		ftchapters.h
  INCS+=		ftcid.h
  INCS+=		fterrdef.h
  INCS+=		fterrors.h
  INCS+=		ftgasp.h
  INCS+=		ftglyph.h
  INCS+=		ftgxval.h
  INCS+=		ftgzip.h
  INCS+=		ftimage.h
  INCS+=		ftincrem.h
  INCS+=		ftlist.h
  INCS+=		ftlcdfil.h
  INCS+=		ftlzw.h
  INCS+=		ftmac.h
  INCS+=		ftmm.h
  INCS+=		ftmodapi.h
  INCS+=		ftmoderr.h
  INCS+=		ftotval.h
  INCS+=		ftoutln.h
  INCS+=		ftpfr.h
  INCS+=		ftrender.h
  INCS+=		ftsizes.h
  INCS+=		ftsnames.h
  INCS+=		ftstroke.h
  INCS+=		ftsynth.h
  INCS+=		ftsystem.h
  INCS+=		fttrigon.h
  INCS+=		fttypes.h
  INCS+=		ftwinfnt.h
  INCS+=		ftxf86.h
  INCS+=		t1tables.h
  INCS+=		ttnameid.h
  INCS+=		tttables.h
  INCS+=		tttags.h
  INCS+=		ttunpat.h

beforeinstall:
	@mkdir -p ${DESTDIR}${X11BASE}/include/freetype2/freetype/config
.for _i in ${INCS}
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${FT2_DIR}/include/freetype/${_i} \
	    ${DESTDIR}${X11BASE}/include/freetype2/freetype/${_i}
.endfor
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${FT2_DIR}/builds/unix/ft2unix.h \
	    ${DESTDIR}${X11BASE}/include/freetype2/ft2build.h
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    freetype-config ${DESTDIR}${BINDIR}/
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE} \
	    freetype2.pc ${DESTDIR}${X11BASE}/lib/pkgconfig/

.include <bsd.lib.mk>