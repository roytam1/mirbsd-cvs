# $OpenBSD: Makefile,v 1.16 2002/10/26 20:44:39 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			multi-way scrolling shoot'em up for X11, addictive

DISTNAME=	xkobo-1.11
CATEGORIES=	games

MASTER_SITES=	${MASTER_SITE_XCONTRIB:=games/}  \
		ftp://ftp.uoknor.edu/mirrors/X/contrib/games/

FLAVOURS=harder
FLAVOUR?=

.if ${FLAVOUR:L} == "harder"
PATCH_LIST=patch-* extra-hard
.endif


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake

ALL_TARGET=	xkobo

USE_CXX=	Yes

NO_REGRESS=	Yes

post-install: 
	${INSTALL_MAN} ${WRKSRC}/xkobo.man ${PREFIX}/man/man1/xkobo.1

.include <bsd.port.mk>
