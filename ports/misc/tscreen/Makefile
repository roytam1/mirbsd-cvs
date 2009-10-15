# $MirOS: ports/misc/screen/Makefile,v 1.27 2009/10/03 16:20:21 tg Exp $
# $OpenBSD: Makefile,v 1.52 2004/01/17 05:34:28 brad Exp $

NOT_FOR_PLATFORM=	Interix:*:*

COMMENT=		multi-screen window manager
VERSION=		0.4.9
DISTNAME=		tscreen-${VERSION}
CATEGORIES=		misc
MASTER_SITES=		${HOMEPAGE}dist/
HOMEPAGE=		http://www.steve.org.uk/Software/tscreen/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv3
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-colors256 \
			--enable-rxvt_osc
CONFIGURE_ARGS+=	--with-sys-screenrc=${SYSCONFDIR:Q}/tscreenrc
EXTRA_MAKE_FLAGS+=	BRANDING=-D'PORT_VERSION=\"-${DASH_VER}\"'

FLAVOURS=		static shm
FLAVOUR?=

.include <mirports.sys.mk>

.if ${FLAVOUR:L} == "static"
LDFLAGS+=		-static
.endif
.if ${FLAVOUR:L} == "shm"
PATCH_LIST=		patch-* shmpatch-*
.endif

ALL_TARGET=		tscreen tscreen.info

post-extract:
	@rm -f ${WRKSRC}/doc/tscreen.info*

post-install:
	cd ${PREFIX}/bin && rm -f tscreen && \
	    mv tscreen-${VERSION} tscreen && chmod ${BINMODE} tscreen
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/tscreen
	${INSTALL_DATA} ${WRKSRC}/etc/etcscreenrc \
	    ${PREFIX}/share/examples/tscreen/tscreenrc
.for _f _m in ${PREFIX}/man/man1/tscreen.1 ${MANMODE} \
    ${PREFIX}/share/examples/tscreen/tscreenrc ${DOCMODE}
	chmod 600 ${_f}
	print '%g#@@SYSCONFDIR@@#s##${SYSCONFDIR}#g\nwq' | \
	    ed -s ${_f}
	chmod ${_m} ${_f}
.endfor
	${INSTALL_DATA} ${WRKSRC}/terminfo/screencap \
	    ${WRKSRC}/terminfo/screeninfo.src \
	    ${PREFIX}/share/examples/tscreen/

.include <bsd.port.mk>
