# $OpenBSD: Makefile,v 1.6 2004/04/18 15:08:28 naddy Exp $

COMMENT=		"enhanced, MIME capable Berkeley Mail"

DISTNAME=		nail-10.5
CATEGORIES=		mail
HOMEPAGE=		http://nail.sourceforge.net/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=nail/}

MODULES=		converters/libiconv

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS=		--with-rcfile="${SYSCONFDIR}/nail.rc" --with-openssl
CONFIGURE_ENV+=		LIBS="-L${ICONV_PREFIX}/lib -liconv"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/nail
	${INSTALL_DATA} ${WRKSRC}/nail.rc ${PREFIX}/share/examples/nail/

.include <bsd.port.mk>
