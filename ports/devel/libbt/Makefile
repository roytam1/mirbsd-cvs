# $OpenBSD: Makefile,v 1.2 2004/04/18 01:04:28 jolan Exp $

COMMENT=			c reimplementation of the BitTorrent core protocols
DISTNAME=	libbt-1.01
CATEGORIES=	devel net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libbt/}

HOMEPAGE=	http://libbt.sourceforge.net/


# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

NO_REGRESS=	Yes
USE_X11=	Yes	# for makedepend

LIB_DEPENDS=	curl.2.2::net/curl

CONFIGURE_STYLE=gnu

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/libbt
	${INSTALL_DATA} ${WRKBUILD}/src/libbt.a ${PREFIX}/lib
.for p in btcheck btget btlist
	${INSTALL_PROGRAM} ${WRKBUILD}/src/${p} ${PREFIX}/bin
.endfor
.for i in benc bitset bterror bts context peer random segmenter strbuf stream \
	types util
	${INSTALL_DATA} ${WRKSRC}/include/${i}.h ${PREFIX}/include/libbt
.endfor
	${INSTALL_MAN} ${WRKSRC}/man/*.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
