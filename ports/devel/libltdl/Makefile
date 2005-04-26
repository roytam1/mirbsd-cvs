# $MirOS: ports/devel/libltdl/Makefile,v 1.1.7.1 2005/03/18 15:44:51 tg Exp $

COMMENT=		Libtool dynamic linking library
CATEGORIES=		devel
V=			1.5.16
DISTNAME=		libtool-${V}
PKGNAME=		ltdl-${V}
MASTER_SITES=		${MASTER_SITE_GNU:=libtool/}
HOMEPAGE=		http://www.gnu.org/software/libtool/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
AUTOCONF_NEW=		Yes
WRKSRC=			${WRKDIST}/libltdl
EXTRA_MAKE_FLAGS=	LIBADD_DL=
EXTRA_FAKE_FLAGS=	mkdir_p='mkdir -p'

post-extract:
	mv ${WRKDIST}/ltdl.m4 ${WRKSRC}/
	print 'm4_include([ltdl.m4])' >${WRKSRC}/acinclude.m4

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/libtool
	${INSTALL_DATA} ${WRKSRC}/ltdl.m4 ${PREFIX}/share/libtool/

.include <bsd.port.mk>
