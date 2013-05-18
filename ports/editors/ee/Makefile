# $MirOS: ports/editors/ee/Makefile,v 1.2 2005/06/23 15:46:12 tg Exp $
# $OpenBSD: Makefile,v 1.2 2002/10/26 00:39:15 naddy Exp $

COMMENT=			easy to use text editor
VERSION=		1.4.6
DISTNAME=		ee-${VERSION}
CATEGORIES=     	editors
HOMEPAGE=		http://mahon.cwx.net/

# Artistic
PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes 
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}sources/
EXTRACT_SUFX=		.src.tgz

WRKDIST=		${WRKDIR}/easyedit-${VERSION}
MAKE_ENV=		SYSCONFDIR=${SYSCONFDIR}

NO_REGRESS=		Yes

do-install:
	print '1,$$g:%%SYSCONFDIR%%:s::${SYSCONFDIR}:g\nwq' \
	    | ed -s ${WRKSRC}/ee.1
	${INSTALL_PROGRAM} ${WRKDIST}/ee ${PREFIX}/bin/ee
	${INSTALL_MAN} ${WRKDIST}/ee.1	${PREFIX}/man/man1/ee.1

.include <bsd.port.mk>
