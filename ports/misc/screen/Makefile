# $MirOS$
# $OpenBSD: Makefile,v 1.52 2004/01/17 05:34:28 brad Exp $

COMMENT=	"multi-screen window manager"
VERSION=	4.0.2
DISTNAME=	screen-${VERSION}
PKGNAME=	${DISTNAME}p0
CATEGORIES=	misc
MASTER_SITES=	ftp://ftp.uni-erlangen.de/pub/utilities/screen/
HOMEPAGE=	http://www.gnu.org/software/screen/
RESPONSIBLE=	Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=autoconf no-autoheader
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=--with-sys-screenrc="${SYSCONFDIR}/screenrc"

FLAVORS=	static shm
FLAVOR?=

.if ${FLAVOR:L} == "static"
LDFLAGS+=	-static
.endif
.if ${FLAVOR:L} == "shm"
PATCH_LIST=	patch-* shmpatch-*
.endif

ALL_TARGET=	screen screen.info

post-extract:
	@rm -f ${WRKSRC}/doc/screen.info*

pre-build:
	@perl -pi -e s#!!sysconfdir!!#${SYSCONFDIR}#g ${WRKSRC}/doc/screen.1

post-install:
	@cd ${PREFIX}/bin && mv -f screen-${VERSION} screen
	@chmod ${BINMODE} ${PREFIX}/bin/screen
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/screen
	${INSTALL_DATA} ${WRKSRC}/etc/etcscreenrc \
	    ${PREFIX}/share/examples/screen/screenrc-sample

.include <bsd.port.mk>
