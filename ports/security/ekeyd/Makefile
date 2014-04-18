# $MirOS: ports/security/ekeyd/Makefile,v 1.3 2012/01/15 13:47:46 tg Exp $

COMMENT=		driver daemons for the Simtec EntropyKey
CATEGORIES=		sysutils security
DISTNAME=		ekeyd-1.1.5
DASH_VER=		1
HOMEPAGE=		http://www.entropykey.co.uk/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Historic Permission Clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

#MASTER_SITES=		${HOMEPAGE}res/download/
MASTER_SITES=		${MASTER_SITE_DEBIAN:=e/ekeyd/}
DISTFILES=		${DISTNAME:S/-/_/}.orig.tar.gz
WRKSRC=			${WRKDIST}/host

USE_GMAKE=		Yes
NO_REGRESS=		Yes
B_R_DEPENDS+=		:lua->=5.1:lang/lua
B_R_DEPENDS+=		::devel/luaposix
B_R_DEPENDS+=		:luasocket->=2.0.1-1:net/luasocket
# only for ulusbd
#LIB_DEPENDS+=		usb::devel/libusb

EXTRA_XAKE_FLAGS+=	PREFIX=${TRUEPREFIX:Q} \
			SYSCONFPREFIX=${SYSCONFDIR:Q}/entropykey \
			MANPREFIX=${TRUEPREFIX:Q}/man/man \
			IN_MIRPORTS=1
.if ${SYSCONFDIR} != "/etc"
EXTRA_XAKE_FLAGS+=	RUNTIMEPREFIX=${LOCALBASE:Q}/db/run
.endif
# disable ulusbd
EXTRA_XAKE_FLAGS+=	BUILD_ULUSBD=no

DOCS=			AUTHORS COPYING ChangeLog THANKS doc/*

post-install:
	mv ${WRKINST}${SYSCONFDIR}/entropykey ${PREFIX}/share/examples/ekeyd
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ekeyd
	cd ${WRKDIST} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/ekeyd/
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/ekeyd/munin
	${INSTALL_DATA} ${WRKDIST}/munin/* ${PREFIX}/share/examples/ekeyd/munin/

.include <bsd.port.mk>
