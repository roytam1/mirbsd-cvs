# $MirOS: ports/databases/gdbm/Makefile,v 1.1.7.1 2005/03/18 15:44:08 tg Exp $
# $OpenBSD: Makefile,v 1.21 2002/11/22 02:37:37 margarida Exp $

COMMENT=			GNU dbm

VERSION=		1.8.3
DISTNAME=		gdbm-${VERSION}
CATEGORIES=		databases

HOMEPAGE=		http://www.gnu.org/software/gdbm/

MASTER_SITES=		${MASTER_SITE_GNU:=gdbm/}


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

AUTOCONF_NEW=		Yes
CONFIGURE_STYLE= 	autoconf gnu dest
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

NO_REGRESS=	Yes

.include <bsd.port.mk>
