# $MirOS$
# $OpenBSD: Makefile,v 1.34 2004/03/05 16:44:20 lebel Exp $

COMMENT=		SLang-based newsreader
CATEGORIES=		mailnews
HOMEPAGE=		http://slrn.sourceforge.net

SVN_DISTPATH=		https://slrn.svn.sourceforge.net/svnroot/slrn/trunk
SVN_DISTREV=		310
SVN_DISTFILE=		slrn

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes
USE_GMAKE=		Yes
LIB_DEPENDS=		slang.::devel/libslang

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-inews --with-ssl

.include <bsd.port.mk>
