# $MirOS: ports/sysutils/fam/Makefile,v 1.5 2008/05/01 00:56:44 tg Exp $

COMMENT=		file alteration monitor

VERSION=		2.7.0
DASH_VER=		3
DISTNAME=		fam-${VERSION}
CATEGORIES=		sysutils devel

HOMEPAGE=		http://oss.sgi.com/projects/fam/
MASTER_SITES=		ftp://oss.sgi.com/projects/fam/download/stable/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.if ${OStype} == "MirBSD" || ${OStype} == "OpenBSD"
CPPFLAGS+=              -DHAVE_KQUEUE

pre-configure:
	echo "H\n%s,@MONITOR_FUNCS@,IMonKQueue,g\n%s,@LIBS@,@LIBS@ -pthread,g\nwq" \
	| ed ${WRKSRC}/src/Makefile.in
.endif

post-extract:
	cp ${FILESDIR}/IMonKQueue.c++ ${WRKSRC}/src
	cp ${FILESDIR}/imon-compat.h ${WRKSRC}/src
	chmod 644 ${WRKSRC}/configure

post-install:
	echo "======== ${PREFIX}"
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/fam
	mv ${WRKINST}/etc/fam.conf ${PREFIX}/share/examples/fam

.include <bsd.port.mk>
