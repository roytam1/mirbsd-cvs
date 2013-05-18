# $MirOS: ports/voip/libosip/Makefile,v 1.3 2006/09/14 00:14:30 tg Exp $

COMMENT=			SIP telephony (VoIP) library
CATEGORIES=		comms net voip
DISTNAME=		libosip-0.9.7
HOMEPAGE=		http://www.linphone.org/?lang=us
MASTER_SITES=		http://simon.morlat.free.fr/download/0.12.2/source/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

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
