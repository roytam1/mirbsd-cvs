# $OpenBSD: Makefile,v 1.13 2004/05/25 10:21:30 xsa Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			afterstep clock with some language extensions

DISTNAME=	asclock-2.0.12
CATEGORIES=	x11

MASTER_SITES=	${MASTER_SITE_AFTERSTEP:=apps/asclock/} \
		http://www.tigr.net/afterstep/download/asclock/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

THEMES=		Freeamp Newstone Orb Stone beats classic penguin shaped
CLASSICS=	beats classic shaped
LANGUAGES=	english german portuguese dutch norwegian italian \
		swedish spanish hungarian breton french czech russian \
		ukrainian slovene indonesian danish hebrew japanese

FLAVOURS=	${THEMES:L} ${LANGUAGES}
FLAVOUR?=	classic english

CONFIGURE_STYLE= imake
USE_X11=	Yes

pre-configure:
	@THEMES='${THEMES}' CLASSICS='${CLASSICS}' LANGUAGES='${LANGUAGES}' \
	     WRKSRC=${WRKSRC} FLAVOUR='${FLAVOUR}' perl -w ${FILESDIR}/configure conf

NO_REGRESS=	Yes

.include <bsd.port.mk>
