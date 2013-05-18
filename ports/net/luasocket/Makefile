# $MirOS: ports/net/luasocket/Makefile,v 1.2 2009/08/29 13:04:28 tg Exp $
# $OpenBSD: Makefile,v 1.17 2009/08/22 20:28:40 robert Exp $

COMMENT=		network support for the lua language
DISTNAME=		luasocket-2.0.1
CATEGORIES=		net
MASTER_SITES=		http://luaforge.net/frs/download.php/1589/
HOMEPAGE=		http://www.cs.princeton.edu/~diego/professional/luasocket/

# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

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
