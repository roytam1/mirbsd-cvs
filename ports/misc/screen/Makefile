# $MirOS: ports/misc/screen/Makefile,v 1.10 2006/09/14 00:11:20 tg Exp $
# $OpenBSD: Makefile,v 1.52 2004/01/17 05:34:28 brad Exp $

NOT_FOR_PLATFORM=	Interix:*:*

COMMENT=		multi-screen window manager
VERSION=		4.0.3
DISTNAME=		screen-${VERSION}
CATEGORIES=		misc
MASTER_SITES=		ftp://ftp.uni-erlangen.de/pub/utilities/screen/
HOMEPAGE=		http://www.gnu.org/software/screen/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-colors256 \
			--enable-rxvt_osc
CONFIGURE_ARGS+=	--with-sys-screenrc=${SYSCONFDIR:Q}/screenrc

FLAVORS=		static shm
FLAVOR?=

.include <mirports.sys.mk>

.if ${FLAVOR:L} == "static"
LDFLAGS+=		-static
.endif
.if ${FLAVOR:L} == "shm"
PATCH_LIST=		patch-* shmpatch-*
.endif

ALL_TARGET=		screen screen.info

post-extract:
	@rm -f ${WRKSRC}/doc/screen.info*

post-install:
	cd ${PREFIX}/bin && mv -f screen-${VERSION} screen
	chmod ${BINMODE} ${PREFIX}/bin/screen
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
