# $OpenBSD: Makefile,v 1.7 2003/12/04 15:29:31 lebel Exp $

COMMENT=			Advanced Intrusion Detection Environment

VSN=			0.10
DISTNAME=		aide-${VSN}
CATEGORIES=		security


BUILD_DEPENDS=		::devel/bison \
			::security/mhash

HOMEPAGE=		http://www.cs.tut.fi/~rammer/aide.html

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=aide/}

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-mhash
CONFIGURE_ENV+=		YACC="bison -y"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/aide
	${INSTALL_DATA} ${WRKSRC}/doc/aide.conf ${PREFIX}/share/examples/aide

.include <bsd.port.mk>
