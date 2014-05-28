# $MirOS: ports/devel/libffi/Makefile,v 1.5 2014/04/09 21:11:37 tg Exp $

COMMENT=		foreign function calling interface library
CATEGORIES=		devel
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
DISTNAME=		libffi-3.0.8
DASH_VER=		1
HOMEPAGE=		http://sourceware.org/libffi/

# Historic Permission Clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		ftp://sourceware.org/pub/libffi/
MODULES+=		devel/pkgconfig
REGRESS_DEPENDS+=	::devel/dejagnu

CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	CCASFLAGS=-D_ASM_SOURCE

.include <bsd.port.mk>
