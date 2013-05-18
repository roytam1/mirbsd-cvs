# $MirOS: ports/games/xinvaders/Makefile,v 1.3 2005/07/07 21:21:24 bsiegert Exp $
# $OpenBSD: Makefile,v 1.19 2004/05/16 23:37:58 pvalchev Exp $

NOT_FOR_PLATFORM=	${LP64_PLATFORMS}

COMMENT=			shoot them nasty little bugs

DISTNAME=       xinvaders
DIST_SUBDIR=	xinvaders
PKGNAME=	xinvaders-2.0-0
CATEGORIES=	games


PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.uu.net/usenet/comp.sources.x/volume19/xinvaders/ \
		ftp://unix.hensa.ac.uk/archive/usenet/comp.sources.x/volume19/xinvaders/
DISTFILES=	part01.Z part02.Z part03.Z

EXTRACT_CASES=	*.Z) ${GZIP_CMD} -dc ${FULLDISTDIR}/$$archive | ${_PERL_FIX_SHAR} | /bin/sh;;

CONFIGURE_STYLE=	imake

WRKDIST=	${WRKDIR}

pre-patch:
	@cd $(WRKSRC) ; mv xinvaders.ma xinvaders.man

NO_REGRESS=	Yes

.include <bsd.port.mk>
