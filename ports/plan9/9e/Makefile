# $MirOS: ports/plan9/9e/Makefile,v 1.1 2006/03/31 00:37:23 tg Exp $

COMMENT=			Simple Plan 9 mkfs extractor
CATEGORIES=		archivers plan9
DISTNAME=		9e-20060330
DIST_SUBDIR=		${DISTNAME}
DISTFILES=		9e.tgz
HOMEPAGE=		http://morphisms.net/~wkj/Software/9e/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${HOMEPAGE}

PERMIT_DISTFILES_CDROM=	no licence at all
PERMIT_DISTFILES_FTP=	no licence at all
PERMIT_PACKAGE_CDROM=	no licence at all
PERMIT_PACKAGE_FTP=	no licence at all

WRKDIST=		${WRKDIR}/9e

do-configure:
	print 'PROG=9e\nNOMAN=yes\n.include <bsd.prog.mk>' >${WRKSRC}/Makefile

.include <bsd.port.mk>
