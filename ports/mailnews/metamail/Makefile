# $MirOS: ports/mailnews/metamail/Makefile,v 1.2 2005/07/07 21:22:50 bsiegert Exp $
# $OpenBSD: Makefile,v 1.19 2004/02/28 20:19:48 naddy Exp $

COMMENT=			MIME implementation

DISTNAME=	mm2.7
PKGNAME=	metamail-2.7-1
CATEGORIES=	mail

MASTER_SITES=	ftp://thumper.bellcore.com/pub/nsb/
EXTRACT_SUFX=	.tar.Z

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/${DISTNAME}/src

NO_REGRESS=	Yes
# mkfontdir used
USE_X11=	Yes

post-configure:
	@perl -pi -e "s,%%SYSCONFDIR%%,${SYSCONFDIR}," ${WRKSRC}/config.h

pre-install:
	@cd ${WRKSRC}/bin && rm -f *.orig

.include <bsd.port.mk>
