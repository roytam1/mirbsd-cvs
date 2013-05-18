# $MirOS: ports/devel/bison/Makefile,v 1.4 2006/09/14 00:08:04 tg Exp $
# $OpenBSD: Makefile,v 1.34 2004/04/06 03:12:19 brad Exp $

COMMENT=			GNU parser generator
DISTNAME=       	bison-2.3
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=bison/}
HOMEPAGE=		http://www.gnu.org/software/bison/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_ENV+=		MAKEINFOFLAGS="--no-split"
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--disable-yacc

# Trust me on this one.
BUILD_DEPENDS+=		:m4->=1.4.3:lang/m4
RUN_DEPENDS+=		:m4->=1.4.3:lang/m4

.include <bsd.port.mk>
