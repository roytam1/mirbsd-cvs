# $MirOS$
# $OpenBSD: Makefile,v 1.13 2003/11/27 02:22:20 pvalchev Exp $

COMMENT=	"callback framework for C++"
DISTNAME=	libsigc++-1.0.4
CATEGORIES=	devel
USE_CXX=	yes
HOMEPAGE=	http://libsigc.sf.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libsigc/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	 autoconf
DOCDIR=			 ${PREFIX}/share/doc/libsigc++/

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/* ${DOCDIR}

do-regress:
.for i in handles misc signals
	@cd ${WRKSRC}/tests/$i; ${MAKE} check-TESTS
.endfor

.include <bsd.port.mk>
