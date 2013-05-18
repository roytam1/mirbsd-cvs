# $OpenBSD: Makefile,v 1.5 2002/09/28 21:25:05 naddy Exp $

COMMENT=			Rich city simulation game for X

DISTNAME=		lincity-1.11
CATEGORIES=		games
HOMEPAGE=		http://www.floot.demon.co.uk/lincity.html


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.demon.co.uk/pub/unix/linux/games/ \
			ftp://ftp.sra.co.jp/pub/os/FreeBSD/distfiles/

USE_X11=		Yes
USE_CXX=		Yes

ALL_TARGET=		xlincity
NO_REGRESS=		Yes

post-extract:
	@cd ${WRKSRC}; ln -s lincity.man xlincity.man

.include <bsd.port.mk>
