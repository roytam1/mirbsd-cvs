# $MirOS: ports/net/dctc/Makefile,v 1.3 2006/02/09 09:36:07 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/18 17:38:37 naddy Exp $

COMMENT=		"Direct Connect clone"

DISTNAME=		dctc-0.68.0
CATEGORIES=		net
HOMEPAGE=		http://ac2i.homelinux.com/dctc/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=    	glib.1.2,gthread.1.2::devel/glib1

CONFIGURE_STYLE= 	autoconf
CPPFLAGS+=		-DMSG_NOSIGNAL=0

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/dctc; \
	    cp -R ${WRKSRC}/Documentation/* ${PREFIX}/share/doc/dctc/

.include <bsd.port.mk>
