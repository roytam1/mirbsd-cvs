# $MirOS: ports/misc/screen/Makefile,v 1.35 2017/11/28 20:49:25 tg Exp $
# $OpenBSD: Makefile,v 1.52 2004/01/17 05:34:28 brad Exp $

NOT_FOR_PLATFORM=	Interix:*:*

COMMENT=		multi-screen window manager
VERSION=		4.0.3
DASH_VER=		21
DISTNAME=		screen-${VERSION}
CATEGORIES=		misc
HOMEPAGE=		http://www.gnu.org/software/screen/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PATCHFILES=		patch-bumpandcollapse.diff:0
PATCH_DIST_STRIP=	-p1
MASTER_SITES=		http://ftp.uni-erlangen.de/pub/utilities/screen/ \
			ftp://ftp.uni-erlangen.de/pub/utilities/screen/
MASTER_SITES0=		http://quesera.com/reynhout/misc/screen+bumpandcollapse/

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-colors256 \
			--enable-rxvt_osc
CONFIGURE_ARGS+=	--with-sys-screenrc=${SYSCONFDIR:Q}/screenrc
EXTRA_MAKE_FLAGS+=	BRANDING=-D'PORT_VERSION=\"-${DASH_VER}\"'

FLAVOURS=		static shm
FLAVOUR?=

.include <mirports.sys.mk>

.if ${FLAVOUR:L:Mstatic}
LDFLAGS+=		-static
.endif
.if ${FLAVOUR:L:Mshm}
CONFIGURE_ARGS+=	--enable-shm
.endif

ALL_TARGET=		screen screen.info

post-extract:
	@rm -f ${WRKSRC}/doc/screen.info*

post-install:
	cd ${PREFIX}/bin && rm -f screen && \
	    mv screen-${VERSION} screen && chmod ${BINMODE} screen
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/screen
	${INSTALL_DATA} ${WRKSRC}/etc/etcscreenrc \
	    ${PREFIX}/share/examples/screen/screenrc
.for _f _m in ${PREFIX}/man/man1/screen.1 ${MANMODE} \
    ${PREFIX}/share/examples/screen/screenrc ${DOCMODE}
	chmod 600 ${_f}
	print '%g#@@SYSCONFDIR@@#s##${SYSCONFDIR}#g\nwq' | \
	    ed -s ${_f}
	chmod ${_m} ${_f}
.endfor
	${INSTALL_DATA} ${WRKSRC}/terminfo/screencap \
	    ${WRKSRC}/terminfo/screeninfo.src \
	    ${PREFIX}/share/examples/screen/

.include <bsd.port.mk>
