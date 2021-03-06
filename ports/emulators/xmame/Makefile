# $MirOS: ports/emulators/xmame/Makefile,v 1.8 2007/04/03 19:42:51 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/10/11 01:37:55 brad Exp $

COMMENT=		emulates arcade machines and old home computers
COMMENT-mame=		emulates a massive variety of arcade machines
COMMENT-mess=		emulates game consoles and old home computers

VERSION=		0.56.2
DISTNAME=		xmame-${VERSION}

CATEGORIES=		emulators games
MASTER_SITES=		${HOMEPAGE}/download/ \
			ftp://ftp.kaupp.cx/pub/xmame/
MASTER_SITES0=		http://www.mame.net/zips/
MASTER_SITES1=		http://www.sys2064.com/files/mame/
MASTER_SITES2=		${MASTER_SITE_BACKUP}

HOMEPAGE=		http://x.mame.net


HISCORE_FILE=	hsdat7.zip
HISTORY_FILE=	history.zip
CHEAT_FILE=	cheat.zip
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${HISCORE_FILE}:0 ${HISTORY_FILE}:1 \
		${CHEAT_FILE}:2

# Need to know endianness
ONLY_FOR_PLATFORM=	*:*:alpha *:*:hppa *:*:i386 *:*:m68k *:*:powerpc *:*:sparc

PERMIT_PACKAGE_CDROM=	"may not sell"
PERMIT_PACKAGE_FTP=	"may not sell"
PERMIT_DISTFILES_CDROM=	"may not sell"
PERMIT_DISTFILES_FTP=	"may not sell"

EXTRACT_SUFX=	.tar.bz2

VMEM_WARNING=	Yes

USE_GMAKE=	Yes
USE_X11=	Yes

MULTI_PACKAGES=	-mame -mess

PKGNAME=	xmame+xmess-${VERSION}-0
PKGNAME-mame=	xmame-${VERSION}-0
PKGNAME-mess=	xmess-${VERSION}-0

VIDEOF=		x11 gl sdl

FLAVOURS=	${VIDEOF} esd
FLAVOUR?=	x11 

EXFL?=
EXFI?=

# Video flavours are mutually exclusive
.for i in ${FLAVOUR:L}
.  if ${VIDEOF:L:M${i}}
EXFL+=		${i}
.    if empty (EXFI)
EXFI+=		${i}
.    endif
.  endif
.endfor
.if   ${EXFL} != ${EXFI}
ERRORS+=	"Fatal: Mutually exclusive flavours: ${EXFL}."
DISPLAY_METHOD=
.endif

# Default video flavour is X11
.if empty(EXFI)
FLAVOUR+=	x11
.endif

.if ${FLAVOUR:L:Msdl}
DISPLAY_METHOD= SDL
LIB_DEPENDS+=	SDL.:sdl-*-!no_x11:devel/sdl
.elif ${FLAVOUR:L:Mgl}
DISPLAY_METHOD=	xgl
LIB_DEPENDS+=	jpeg.::graphics/jpeg
.else
DISPLAY_METHOD=	x11
.endif

.if ${FLAVOUR:L:Mesd}
MAKE_FLAGS+=	SOUND_ESOUND=1
LIB_DEPENDS+=	esd::audio/esound
.endif

MAKE_ENV=	PREFIX="${PREFIX}"
MAKE_FILE=	Makefile.OpenBSD
FAKE_FLAGS=	${MAKE_FLAGS}
MAKE_FLAGS+=	ARCH=openbsd \
		DISPLAY_METHOD="${DISPLAY_METHOD}" \
		INCLUDES="-I${LOCALBASE}/include" LIBS="-L${LOCALBASE}/lib" \
		X11INC="-I${X11BASE}/include" X11LIB="-L${X11BASE}/lib" \
		GLLIBS="-pthread" \
		INSTALL_PROGRAM_DIR="${INSTALL_PROGRAM_DIR}" \
		INSTALL_MAN_DIR="${INSTALL_MAN_DIR}" \
		INSTALL_DATA_DIR="${INSTALL_DATA_DIR}" \
		INSTALL_PROGRAM="${INSTALL_PROGRAM}" \
		INSTALL_PROGRAM_SUID="${INSTALL_PROGRAM}" \
		INSTALL_MAN="${INSTALL_MAN}" \
		INSTALL_DATA="${INSTALL_DATA}" \
		SYSCONFDIR="${SYSCONFDIR}" \
		JOY_USB=1

DOCS=	changes.mame changes.mess changes.opengl changes.unix credits.mess \
	dga2.txt gamelist.mame gamelist.mess imgtool.txt liesmich.unix \
	messroms.txt multiplayer-readme.txt old-changes.mess readme.mame \
	readme.mess xmame-doc-1.html xmame-doc-2.html xmame-doc-3.html \
	xmame-doc-4.html xmame-doc-5.html xmame-doc-6.html xmame-doc-7.html \
	xmame-doc-8.html xmame-doc.html xmame-doc.lyx xmame-doc.man.skel \
	xmame-doc.txt xmame-gdoc-1.html xmame-gdoc-2.html xmame-gdoc-3.html \
	xmame-gdoc-4.html xmame-gdoc-5.html xmame-gdoc-6.html \
	xmame-gdoc-7.html xmame-gdoc-8.html xmame-gdoc.html xmame.css

.if   ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=	nasm::lang/nasm
MAKE_FLAGS+=	MY_CPU=i386 \
		X86_ASM_68000=1 \
		NASM_FMT="-f elf" \
		ASM_STRIP="src/unix/contrib/porting/strip_"
.  if   ${DISPLAY_METHOD} == "x11"
MAKE_FLAGS+=	X11_DGA=1
.  elif ${DISPLAY_METHOD} != "SDL"
MAKE_FLAGS+=	JOY_I386=1
.  endif
.elif ${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "m68k"
MAKE_FLAGS+=	MY_CPU=${MACHINE_ARCH}
.elif ${MACHINE_ARCH} == "hppa" || ${MACHINE_ARCH} == "powerpc" || \
      ${MACHINE_ARCH} == "sparc"
MAKE_FLAGS+=	MY_CPU=risc
.endif

NO_REGRESS=	Yes

post-extract:
	${UNZIP} -u ${FULLDISTDIR}/${HISCORE_FILE} -d ${WRKDIR}
	${UNZIP} -u ${FULLDISTDIR}/${HISTORY_FILE} -d ${WRKDIR}
	${UNZIP} -u ${FULLDISTDIR}/${CHEAT_FILE} -d ${WRKDIR}
	cp ${WRKSRC}/doc/xmame.6 ${WRKSRC}/doc/xmess.6

post-patch:
	@cp ${FILESDIR}/${MAKE_FILE} ${WRKSRC}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xmame/img
	${INSTALL_DATA} ${WRKSRC}/doc/img/xmame.jpg \
		${PREFIX}/share/doc/xmame/img
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/xmame
.for i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/doc/${i} ${PREFIX}/share/doc/xmame
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/xmame
	${INSTALL_DATA} ${FILESDIR}/xmame-${DISPLAY_METHOD}rc \
		${PREFIX}/share/xmame/xmamerc
	perl -i -pe 's:%%PREFIX%%:${TRUEPREFIX}:' ${PREFIX}/share/xmame/xmamerc
	${INSTALL_DATA} ${WRKDIR}/*.dat ${PREFIX}/share/xmame
	${INSTALL_DATA} ${WRKDIR}/*.txt ${PREFIX}/share/doc/xmame
	${INSTALL_DATA_DIR} ${PREFIX}/share/xmess
	${INSTALL_DATA} ${FILESDIR}/xmess-${DISPLAY_METHOD}rc \
		${PREFIX}/share/xmess/xmessrc
	perl -i -pe 's:%%PREFIX%%:${TRUEPREFIX}:' ${PREFIX}/share/xmess/xmessrc
	${INSTALL_DATA} ${WRKSRC}/doc/sysinfo.dat ${PREFIX}/share/xmess

.include <bsd.port.mk>
