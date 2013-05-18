# $MirOS$
# $OpenBSD: Makefile,v 1.36 2009/06/24 14:19:06 jolan Exp $

COMMENT=		powerful, light-weight programming language
DISTNAME=		lua-5.1.4
CATEGORIES=		lang
HOMEPAGE=		http://www.lua.org/

# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		http://www.lua.org/ftp/ \
			http://www.tecgraf.puc-rio.br/lua/ftp/ \
			http://ftp.gwdg.de/pub/languages/lua/ \
			http://mirrors.sunsite.dk/lua/ \
			http://ftp.ntua.gr/pub/lang/lua/ \
			http://ftp.chg.ru/pub/lang/lua/

SHARED_ONLY=		Yes
#SHARED_LIBS=		lua 5.1
EXTRA_XAKE_FLAGS+=	LIBlua_VERSION=5.1
CFLAGS+=		${PICFLAG}
NO_REGRESS=		Yes

.if (${MACHINE_OS} == "Darwin")
EXTRA_XAKE_FLAGS+=	PLAT=macosx
.else
EXTRA_XAKE_FLAGS+=	PLAT=bsd
.endif

post-build:
	sed 's!^prefix=.*$$!prefix='${PREFIX:Q}'!' ${WRKSRC}/etc/lua.pc \
	    >${WRKBUILD}/etc/lua.pc.inst

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/pkgconfig
	${INSTALL_DATA} ${WRKBUILD}/etc/lua.pc.inst \
	    ${PREFIX}/lib/pkgconfig/lua.pc

.include <bsd.port.mk>
