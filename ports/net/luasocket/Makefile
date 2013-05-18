# $MirOS: ports/net/luasocket/Makefile,v 1.5 2009/11/14 21:13:13 tg Exp $
# $OpenBSD: Makefile,v 1.17 2009/08/22 20:28:40 robert Exp $

COMMENT=		network support for the lua language
DISTNAME=		luasocket-2.0.2
CATEGORIES=		net
HOMEPAGE=		http://w3.impa.br/~diego/software/luasocket/home.html

# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://files.luaforge.net/releases/luasocket/luasocket/${DISTNAME}/

BUILD_DEPENDS+=		:mirmake->=20090830:devel/mirmake
MODULES=		lang/lua
NO_REGRESS=		Yes
SHARED_ONLY=		Yes
MAKE_FILE=		${.CURDIR}/Makefile.luasocket
EXTRA_XAKE_FLAGS+=	LUALIBDIR=${TRUEPREFIX:Q}/lib/lua/5.1
EXTRA_XAKE_FLAGS+=	MAKEFILE_BUNDLE=${.CURDIR}/Makefile.bundle

SHAREDIR=		${PREFIX:Q}/share/lua/5.1

pre-install:
	${INSTALL_DATA_DIR} ${SHAREDIR}/{mime,socket} \
	    ${PREFIX:Q}/lib/lua/5.1/{mime,socket} \
	    ${PREFIX:Q}/share/doc/luasocket \
	    ${PREFIX:Q}/share/examples/luasocket/{etc,test}

post-install:
	${INSTALL_DATA} ${WRKSRC}/{LICENSE,NEW,README} ${WRKSRC}/doc/* \
	    ${PREFIX}/share/doc/luasocket/
	${INSTALL_DATA} ${WRKSRC}/samples/* ${PREFIX}/share/examples/luasocket/
	${INSTALL_DATA} ${WRKSRC}/etc/* \
	    ${PREFIX}/share/examples/luasocket/etc/
	${INSTALL_DATA} ${WRKSRC}/test/* \
	    ${PREFIX}/share/examples/luasocket/test/
	cd ${WRKSRC}/src && \
	    ${INSTALL_DATA} {ltn12,mime,socket}.lua ${SHAREDIR}/ && \
	    ${INSTALL_DATA} {ftp,http,smtp,tp,url}.lua ${SHAREDIR}/socket/

.include <bsd.port.mk>
