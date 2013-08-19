# $OpenBSD: Makefile.inc,v 1.2 2002/11/22 02:44:05 margarida Exp $

COMMENT=			simple and performant DNS server

DISTNAME=		maradns-${VERSION}
CATEGORIES=		net

HOMEPAGE=		http://www.maradns.org


# stable: Public Domain
# devel: BSD license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_FLAGS=		CC=${_PASS_CC:T:Q} FLAGS=${CFLAGS:Q}

NO_REGRESS=		Yes