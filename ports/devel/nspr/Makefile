# $MirOS: ports/devel/nspr/Makefile,v 1.5 2006/09/14 00:08:28 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/01/29 21:57:53 pvalchev Exp $
# $FreeBSD: /repoman/r/pcvs/ports/devel/nspr/Makefile,v 1.13 2003/12/13 21:30:19 peter Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:*

COMMENT=		Netscape Portable Runtime
VERSION=		4.8.2
DISTNAME=		nspr-${VERSION}
CATEGORIES=		devel
HOMEPAGE=		http://www.mozilla.org/projects/nspr/index.html

# MPL - Mozilla Public License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://ftp.mozilla.org/pub/mozilla.org/nspr/releases/v${VERSION}/src/

USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--disable-debug \
			--with-pthreads

WRKSRC=			${WRKDIST}/mozilla/nsprpub

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/nspr
	cd ${WRKSRC}/dist/include && tar cfL - . | \
		(cd ${PREFIX}/include && tar -xf -)
	cd ${WRKSRC}/dist/lib && tar cf - . | \
		(cd ${PREFIX}/lib && tar -xf -)
	${INSTALL_SCRIPT} ${WRKSRC}/config/nspr-config ${PREFIX}/bin

do-regress:
	cd ${WRKSRC}/pr/tests && env ${MAKE_ENV} ${MAKE_PROGRAM} ${MAKE_FLAGS} runtests

.include <bsd.port.mk>
