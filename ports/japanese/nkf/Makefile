# very loosely based on FreeBSD 2.2.7
# $OpenBSD: Makefile,v 1.13 2004/01/17 15:58:08 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Network Kanji code conversion Filter

VERSION=	1.92
DISTNAME=	nkf-${VERSION}
PKGNAME=	ja-nkf-${VERSION}-0
CATEGORIES=	japanese textproc
DISTFILES=	nkf192.shar

HOMEPAGE=	http://www.ie.u-ryukyu.ac.jp/~kono/nkf/
MASTER_SITES=	http://www.ie.u-ryukyu.ac.jp/~kono/nkf/dist/


#		BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=${WRKDIR}
WRKSRC=${WRKDIR}/NKF

CONFIGURE_STYLE=perl

pre-extract:
	@mkdir -p ${WRKSRC}

pre-build:
	cd ${WRKDIST} && ${_PASS_CC:Q} ${CFLAGS} -o nkf nkf.c

# original english man page was rather difficult to follow
post-install:	
	${INSTALL_PROGRAM} ${WRKDIST}/nkf ${PREFIX}/bin
	${INSTALL_MAN} ${WRKDIST}/nkf.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKDIST}/nkf.doc ${PREFIX}/man/ja_JP.EUC/cat1/nkf.0

do-regress:
	cd ${WRKSRC} && perl nkf_test.pl

.include <bsd.port.mk>
