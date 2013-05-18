# $MirOS: ports/net/nmap/Makefile,v 1.6 2008/10/16 19:44:01 tg Exp $
# $OpenBSD: Makefile,v 1.49 2004/05/16 08:38:12 jolan Exp $

COMMENT=		scan ports and fingerprint stack of network hosts
DISTNAME=		nmap-5.00
CATEGORIES=		net security
HOMEPAGE=		http://nmap.org/
MASTER_SITES=		${HOMEPAGE}dist/
EXTRACT_SUFX=		.tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= 	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-libpcap=/usr
CONFIGURE_ARGS+=	--with-libpcre=${LOCALBASE}
CONFIGURE_ARGS+=	--with-libdnet=included
MODGNU_RECURSE_DIRS=	${WRKSRC}/nbase ${WRKSRC}/nsock ${WRKSRC}/ncat \
			${WRKSRC}/libdnet-stripped ${WRKSRC}

USE_CXX=		Yes
USE_GMAKE=		Yes

# XXX workaround linking issue on hppa
.if ${MACHINE_ARCH:Mhppa}
PATCH_LIST=	patch-* hppa-*
.endif

FLAVOURS=	no_x11
FLAVOUR?=

LIB_DEPENDS+=	pcre::devel/pcre
# WTF does he have libdnet 1.12 from? latest version on sf is 1.11
#LIB_DEPENDS+=	dnet::net/libdnet
#MODULES=	lang/python
#B_R_DEPENDS+=	${_MODPY_BUILD_DEPENDS}

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=--without-zenmap
.else
USE_X11=	Yes
# need pygtk2
.endif

NO_REGRESS=	Yes

.include <bsd.port.mk>
