# $MirOS: ports/graphics/aalib/Makefile,v 1.5 2007/02/22 22:57:50 tg Exp $
# $OpenBSD: Makefile,v 1.18 2003/04/06 01:15:10 margarida Exp $

COMMENT=		ascii art library
DISTNAME=		aalib-1.4rc4
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=aa-project/}
HOMEPAGE=		http://aa-project.sourceforge.net/aalib/

# GNU LGPL v2.0
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/aalib-1.4.0
#CONFIGURE_STYLE=	autogen
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	--enable-static \
			${CONFIGURE_SHARED}

FLAVOURS=		no_x11
FLAVOUR?=

.if ${FLAVOUR:L} == "no_x11"
CONFIGURE_ARGS+=	--without-x
.else
USE_X11=		Yes
.endif

post-extract:
	-rm -f ${WRKSRC}/doc/*.info*

.include <bsd.port.mk>
