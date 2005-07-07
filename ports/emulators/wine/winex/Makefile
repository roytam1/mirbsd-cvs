# $MirOS: ports/emulators/wine/winex/Makefile,v 1.2 2005/04/10 21:49:52 tg Exp $

BROKEN=			builds but stalls in WaitForWin16Mutex

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=		"Microsoft Windows® 3.1/95/NT/Games emulator for Unix®"
CATEGORIES=		emulators
DISTNAME=		winex-cvs-${V}
PKGNAME=		wine-${V}_winex-0
V=			20040225
VER=			"ReWind/WineX CVS version $(V)"
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=		http://www.transgaming.com/

# Aladdin, GNU LGPLv2.1, MIT-style
PERMIT_PACKAGE_CDROM=	"Aladdin licence, wants fee"
PERMIT_PACKAGE_FTP=	"must come with distfile, restricts"
PERMIT_DISTFILES_CDROM=	"Aladdin licence, wants fee"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD}

WRKDIST=		${WRKDIR}/winex
EXTRACT_SUFX=		.cgz

USE_X11=		yes
USE_GMAKE=		yes
CONFIGURE_STYLE=        gnu dest
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/tools/
CONFIGURE_ARGS+=	--enable-opengl --disable-osmesa  # OSmesa too old

#.include <bsd.own.mk>
#.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--disable-pthreads
CPPFLAGS+=		-DASSUME_BSDSAFE_VFORK
#.else
#CONFIGURE_ARGS+=	--enable-pthreads	# not yet
#CPPFLAGS+=		-pthread
#LDFLAGS+=		-pthread
#.endif

CFLAGS+=		-fno-stack-protector

post-configure:
	cd ${WRKSRC} && ${MAKE_PROGRAM} depend
	echo '#define	WINE_RELEASE_INFO	$(VER)' \
	    >${WRKSRC}/include/wine/version.h
	echo $(VER) >${WRKSRC}/VERSION

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/wine
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/config \
	    ${PREFIX}/share/wine/config.sample
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/generic.ppd \
	    ${PREFIX}/share/wine/
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/system.ini \
	    ${PREFIX}/share/wine/

NO_REGRESS=		yes

.include <bsd.port.mk>
