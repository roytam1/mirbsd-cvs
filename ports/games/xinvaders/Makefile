# $MirOS: ports/games/xinvaders/Makefile,v 1.5 2008/03/09 19:15:55 tg Exp $
# $OpenBSD: Makefile,v 1.19 2004/05/16 23:37:58 pvalchev Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*
NOT_FOR_PLATFORM=	${LP64_PLATFORMS}

COMMENT=		shoot them nasty little bugs
DISTNAME=		xinvaders
DIST_SUBDIR=		xinvaders
PKGNAME=		xinvaders-2.0-0
CATEGORIES=		games

PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.uu.net/usenet/comp.sources.x/volume19/xinvaders/ \
		ftp://unix.hensa.ac.uk/archive/usenet/comp.sources.x/volume19/xinvaders/
DISTFILES=	part01.Z part02.Z part03.Z

EXTRACT_CASES=	*.Z) ${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive | ${_PERL_FIX_SHAR} | /bin/sh;;

CONFIGURE_STYLE=	imake
USE_X11=		Yes
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}

pre-patch:
	@cd ${WRKSRC:Q} && mv xinvaders.ma xinvaders.man

.include <bsd.port.mk>
