# $MirOS: ports/voip/libmikey/Makefile,v 1.2 2005/08/21 11:50:29 tg Exp $

COMMENT=			Multimedia Internet KEYing protocol (RFC3830)
CATEGORIES=		voip devel net
DISTNAME=		libmikey-0.4.0
HOMEPAGE=		http://www.minisip.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		http://www.minisip.org/source/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		mutil.0::voip/libmutil

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
