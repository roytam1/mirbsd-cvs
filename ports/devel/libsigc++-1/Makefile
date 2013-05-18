# $MirOS: ports/devel/libsigc++/Makefile,v 1.1 2005/03/18 15:44:54 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/11/27 02:22:20 pvalchev Exp $

COMMENT=		callback framework for C++
DISTNAME=		libsigc++-1.0.4
CATEGORIES=		devel
HOMEPAGE=		http://libsigc.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libsigc/}

PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-libtool-lock
USE_CXX=		Yes
DOCDIR=			${PREFIX}/share/doc/libsigc++

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/* ${DOCDIR}/

do-regress:
.for i in handles misc signals
	@cd ${WRKSRC}/tests/$i; ${MAKE} check-TESTS
.endfor

.include <bsd.port.mk>
