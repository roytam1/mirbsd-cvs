# $MirOS: ports/devel/boehm-gc/Makefile,v 1.9 2007/05/28 13:38:47 bsiegert Exp $
# $OpenBSD: Makefile,v 1.29 2004/03/04 17:49:26 espie Exp $
# $FreeBSD: Makefile,v 1.4 1999/01/10 20:12:06 steve Exp $

NOT_FOR_PLATFORM=	*:*:hppa {Open,Mir}BSD:*:powerpc *:*:vax

COMMENT=	garbage collection and memory leak detection for C and C++
VERSION=	6.8
DASH_VER=	1
DISTNAME=	gc${VERSION}
PKGNAME=	boehm-gc-${VERSION}-${DASH_VER}
CATEGORIES=	devel
MASTER_SITES=	${HOMEPAGE}gc_source/
HOMEPAGE=	http://www.hpl.hp.com/personal/Hans_Boehm/gc/

# BSD-style, lacks permission to sell
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	Yes

MAKE_ENV=	CP="cp" \
		INSTALL_DATA="${INSTALL_DATA}" \
		INSTALL_MAN="${INSTALL_MAN}"

CONFIGURE_STYLE=autogen no-autoheader
AUTOCONF_NEW=	Yes
AUTOMAKE_VERSION= 1.9
CONFIGURE_ARGS= ${CONFIGURE_SHARED} --enable-full-debug

# XXX the below causes failures still
#	--enable-redirect-malloc 

WRKDIST=	${WRKDIR}/gc${VERSION}

post-patch:
	@mv ${WRKSRC}/doc/gc.man ${WRKSRC}/doc/gc.man.in
	@sed -e "s,@PREFIX@,${PREFIX},g" ${WRKSRC}/doc/gc.man.in > \
		${WRKSRC}/doc/gc.man

post-install:
	${INSTALL_DATA} ${WRKSRC}/doc/gc.man ${PREFIX}/man/man3/gc.3
	${INSTALL_DATA_DIR} ${PREFIX}/include/private
	${INSTALL_DATA} ${WRKSRC}/include/gc{,_{cpp,backptr,gcj,mark,typed}}.h ${PREFIX}/include
	${INSTALL_DATA} ${WRKSRC}/include/private/gc{config,_{hdrs,locks,priv,pmark}}.h ${PREFIX}/include/private

REGRESS_TARGET=	check-TESTS

.include <bsd.port.mk>
