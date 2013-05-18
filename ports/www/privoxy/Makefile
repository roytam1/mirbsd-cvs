# $MirOS$
# $OpenBSD: Makefile,v 1.11 2004/12/11 13:29:22 alek Exp $

COMMENT=		web proxy with advanced filtering capabilities
VERSION=		3.0.6
DISTNAME=		privoxy-${VERSION}-stable-src
PKGNAME=		privoxy-${VERSION}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.privoxy.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=ijbswa/}
WRKDIST=		${WRKDIR}/${DISTNAME:S/-src//}
NO_REGRESS=		Yes
USE_GMAKE=		Yes
MAKE_FILE=		GNUmakefile
LIB_DEPENDS+=		pcre,pcreposix::devel/pcre
CONFIGURE_STYLE=	autoconf
CPPFLAGS+=		-Dunix
CONFIGURE_ARGS+=	--with-docbook=no \
			--with-user=_privoxy \
			--with-group=_privoxy

# make install is broken
do-install:
	print '%g/@@SYSCONFDIR@@/s!!${SYSCONFDIR}!g\nwq' | \
	    ed -s ${WRKSRC}/config
	${INSTALL_PROGRAM} ${WRKSRC}/privoxy ${PREFIX}/sbin/
	${INSTALL_MAN} ${WRKSRC}/privoxy.1 ${PREFIX}/man/man1/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/privoxy
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/privoxy/
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/privoxy
	${INSTALL_DATA} ${WRKSRC}/config ${PREFIX}/share/examples/privoxy/
	${INSTALL_DATA} ${WRKSRC}/default.filter ${PREFIX}/share/examples/privoxy/
	${INSTALL_DATA} ${WRKSRC}/*.action ${PREFIX}/share/examples/privoxy/
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/privoxy/templates
	${INSTALL_DATA} ${WRKSRC}/templates/* ${PREFIX}/share/examples/privoxy/templates/

.include <bsd.port.mk>
