# $OpenBSD: Makefile,v 1.8 2002/10/24 22:20:04 naddy Exp $

COMMENT=			premier dockable radio tuner

DISTNAME=	wmtune-1.1c
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio x11 x11/windowmaker

HOMEPAGE=	http://www.soren.org/linux/wmtune/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}dl/

MAKE_ENV=		CC=${_PASS_CC:T:Q}
USE_X11=		Yes

FLAVOURS=		zoltrix
FLAVOUR?=

.if ${FLAVOUR:L} == "zoltrix"
CFLAGS+=		-DZOLTRIX
BINMODE=		4555
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
.endif

WRKDIST=		${WRKDIR}/wmtune-1.0.1-combined/

post-extract:
	@cp files/wmtune.1 ${WRKDIST}

NO_REGRESS=		Yes

.include <bsd.port.mk>
