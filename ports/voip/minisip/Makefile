# $MirOS: ports/voip/minisip/Makefile,v 1.3 2005/08/21 11:50:33 tg Exp $

BROKEN=			builds, but does not work correctly

COMMENT=			small, secure Voice over IP (SIP) client
CATEGORIES=		voip net
DISTNAME=		minisip-0.7.0
HOMEPAGE=		http://www.minisip.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		http://www.minisip.org/source/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		mutil.0::voip/libmutil \
			mnetutil.0::voip/libmnetutil \
			mikey.0::voip/libmikey \
			msip.0::voip/libmsip

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-textui \
			--disable-gtk

.include <bsd.port.mk>
