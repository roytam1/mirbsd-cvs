# $MirOS: ports/security/stunnel/Makefile,v 1.6 2011/08/04 15:27:17 tg Exp $
# $OpenBSD: Makefile,v 1.22.4.2 2003/09/03 19:13:48 brad Exp $

COMMENT=		SSL encryption wrapper for standard network daemons
DISTNAME=		stunnel-3.26
DASH_VER=		3
CATEGORIES=		security
HOMEPAGE=		http://stunnel.mirt.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD}

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-pem-dir=${SYSCONFDIR}/ssl \
			--with-random=/dev/arandom
ALL_TARGET=		stunnel

.include <mirports.sys.mk>
.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-tcp-wrappers
.else
CONFIGURE_ARGS+=	--without-tcp-wrappers
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/stunnel ${PREFIX}/sbin/
	${INSTALL_MAN} ${WRKSRC}/stunnel.8 ${PREFIX}/man/man8/

.include <bsd.port.mk>
