# $MirOS: ports/x11/libxklavier/Makefile,v 1.4 2007/07/03 19:54:42 bsiegert Exp $

COMMENT=		printer driver for QPDL printers under CUPS

VERSION=		2.0.0
DISTNAME=		splix-${VERSION}
CATEGORIES=		print
EXTRACT_SUFX=		.tar.bz2

HOMEPAGE=		http://splix.ap2c.org/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=splix/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		cups,cupsimage::print/cups
LIB_DEPENDS+=		jbig::graphics/jbigkit

USE_CXX=		Yes
USE_GMAKE=		Yes
NO_REGRESS=		Yes

.include <bsd.port.mk>
