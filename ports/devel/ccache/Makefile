# $MirOS: ports/devel/ccache/Makefile,v 1.7 2008/09/11 21:34:42 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/09/28 17:19:14 naddy Exp $

COMMENT=		pre-processor caching program for C/C++ compilers
DISTNAME=		ccache-2.4
DASH_VER=		2
CATEGORIES=		devel
HOMEPAGE=		http://ccache.samba.org/
RESPONSIBLE=		R. Tyler Ballance <tyler@mirbsd.org>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}ftp/ccache/
CONFIGURE_STYLE=	gnu
CCACHE_DEPENDS=		#empty
REGRESS_ENV+=		CC=${_PASS_CC:T:Q}

.include <bsd.port.mk>
