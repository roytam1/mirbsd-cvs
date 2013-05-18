# $MirOS: ports/emulators/wine/rewind/Makefile,v 1.7 2005/10/10 20:01:46 tg Exp $

BROKEN=			this port is not complete

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Microsoft Windows 3.1/95/NT emulator for Unix
CATEGORIES=		emulators
V=			200xyyzz
DISTNAME=		rewind-cvs-$(V)
PKGNAME=		rewind-${V}-0
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://rewind.sf.net/

# X11 Licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD}

WRKDIST=		${WRKDIR}/rewind
EXTRACT_SUFX=		.tgz

USE_X11=		yes
CONFIGURE_STYLE=        gnu dest
CONFIGURE_ARGS+=	--enable-opengl --without-reentrant-x

post-configure:
	cd ${WRKSRC} && ${MAKE_PROGRAM} depend
	echo '#define	WINE_RELEASE_INFO	$(VER)' \
	    >${WRKSRC}/include/wine/version.h
	echo $(VER) >${WRKSRC}/VERSION

REGRESS_FLAGS=HOME=${WRKDIR}/regress DISPLAY=${DISPLAY}
REGRESS_IS_INTERACTIVE=Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/wine
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/config \
	    ${PREFIX}/share/wine/config.sample
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/generic.ppd \
	    ${PREFIX}/share/wine/
	${INSTALL_DATA} ${WRKSRC}/documentation/samples/system.ini \
	    ${PREFIX}/share/wine/

pre-regress:
	mkdir -p ${WRKDIR}/regress/.wine \
	    ${WRKDIR}/regress/c/windows/system \
	    ${WRKDIR}/regress/c/windows/fonts
	sed -e 's,@@WIN@@,${WRKDIR}/regress/c,' \
	    <${WRKSRC}/documentation/samples/config \
	    >${WRKDIR}/regress/.wine/config
	@echo '========================================================='
	@echo ' The regression test needs to access your DISPLAY (X11).'
	@echo ' As a quick fix, type "xhost +" before and "xhost -"'
	@echo ' after the test, to allow any host (i.e. root, too) to'
	@echo ' connect to your X-Window session. Note this is a huge'
	@echo ' security risk and highly deprecated.'
	@echo '========================================================='

.include <bsd.port.mk>
