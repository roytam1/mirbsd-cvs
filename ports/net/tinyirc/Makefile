# $MirOS: ports/net/tinyirc/Makefile,v 1.1 2008/12/20 18:25:48 tg Exp $

COMMENT=		minimalistic IRC client
VERSION=		2008/12/29
DISTNAME=		${CVS_DISTFILE}-${VERSION:S!/!!g}
CATEGORIES=		net
MCZ_FETCH=		Yes
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		${VERSION} 23:59:59
CVS_DISTMODS=		contrib/code/Snippets/tinyirc.c
CVS_DISTFILE=		tinyirc
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/contrib/code/Snippets
MAKE_FILE=		tinyirc.c

.include <bsd.port.mk>
