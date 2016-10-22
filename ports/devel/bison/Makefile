# $MirOS: ports/devel/bison/Makefile,v 1.8 2008/11/02 02:21:50 tg Exp $
# $OpenBSD: Makefile,v 1.42 2008/07/08 00:24:17 brad Exp $

COMMENT=		GNU parser generator
DISTNAME=       	bison-2.3
DASH_VER=		3
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=bison/}
HOMEPAGE=		http://www.gnu.org/software/bison/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--disable-yacc

BUILD_DEPENDS+=		:m4->=1.4.3:lang/m4

.include <bsd.port.mk>
