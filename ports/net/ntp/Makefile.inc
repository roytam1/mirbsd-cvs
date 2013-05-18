# $OpenBSD: Makefile.inc,v 1.5 2004/02/04 07:39:18 sturm Exp $

COMMENT=			network time protocol implementation
COMMENT-doc=			network time protocol documentation

DISTNAME=	ntp-${NTP_VERSION}
PKGNAME=	ntp-${NTP_VERSION:C/-rc.*//}-0
PKGNAME-doc=	ntp-doc-${NTP_VERSION:C/-rc.*//}-0
CATEGORIES=	net
MASTER_SITES=	http://www.eecis.udel.edu/~ntp/ntp_spool/ntp4/ \
		ftp://ftp.udel.edu/pub/ntp/ntp4/ \
		ftp://ftp.cs.umn.edu/ftp00/ftp.udel.edu/pub/ntp/ntp4/

HOMEPAGE=	http://www.ntp.org/


PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	Yes

MULTI_PACKAGES=	-doc
SUBPACKAGE?=

.if defined(PACKAGING) && ${SUBPACKAGE} == "-doc"
PKG_ARCH=	*
.endif

AUTOCONF_NEW=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= --bindir='${PREFIX}/sbin' \
	 	--enable-accurate-adjtime --disable-IRIG

post-patch:
	@touch ${WRKSRC}/aclocal.m4 ${WRKSRC}/config.h.in ${WRKSRC}/version
	@find ${WRKSRC} -type f -name "Makefile.in" -exec touch {} \;

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ntp
	@cd ${WRKSRC}/html && pax -rw * ${PREFIX}/share/doc/ntp
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/ntp
	@cd ${WRKSRC}/conf && pax -rw * ${PREFIX}/share/examples/ntp

