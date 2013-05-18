# $MirOS: ports/voip/libmsip/Makefile,v 1.2 2005/08/21 11:50:30 tg Exp $

COMMENT=			Session Initiation Protocol (RFC3261)
CATEGORIES=		voip devel net
DISTNAME=		libmsip-0.3.0
HOMEPAGE=		http://www.minisip.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		http://www.minisip.org/source/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		mutil.0::voip/libmutil \
			mnetutil.0::voip/libmnetutil

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
