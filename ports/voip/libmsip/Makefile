# $MirOS$

COMMENT=		"Session Initiation Protocol (RFC3261)"
CATEGORIES=		voip devel net
DISTNAME=		libmsip-0.3.0
HOMEPAGE=		http://www.minisip.org/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
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
