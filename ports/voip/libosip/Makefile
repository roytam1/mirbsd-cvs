# $MirOS: ports/voip/libosip/Makefile,v 1.2 2005/09/01 20:59:16 tg Exp $

COMMENT=			SIP telephony (VoIP) library
CATEGORIES=		comms net voip
DISTNAME=		libosip-0.9.7
HOMEPAGE=		http://www.linphone.org/?lang=us
MASTER_SITES=		http://simon.morlat.free.fr/download/0.12.2/source/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-pthread \
			--enable-semaphore \
			${CONFIGURE_SHARED}

.include <bsd.port.mk>
