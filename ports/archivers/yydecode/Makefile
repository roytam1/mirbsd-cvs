# $MirOS: ports/x11/libxklavier/Makefile,v 1.5 2008/07/27 14:02:44 bsiegert Exp $

COMMENT=		decoder for yEnc binaries

VERSION=		0.2.10
DISTNAME=		yydecode-${VERSION}
CATEGORIES=		archivers mailnews

HOMEPAGE=		http://yydecode.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=yydecode/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

# regression tests are missing files
NO_REGRESS=		Yes

.include <bsd.port.mk>
