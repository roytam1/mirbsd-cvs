# $MirOS: ports/net/tinyirc/Makefile,v 1.5 2009/12/28 14:55:00 tg Exp $

COMMENT=		minimalistic IRC client
CATEGORIES=		net
MCZ_FETCH=		Yes
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2009/12/27 23:59:59
PKGNAME=		${CVS_DISTFILE}-${CVS_DISTDATE:M*/*:S!/!!g}-${DASH_VER}
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
