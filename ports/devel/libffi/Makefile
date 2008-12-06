# $MirOS: ports/devel/libffi/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

COMMENT=		foreign function calling interface library
CATEGORIES=		devel
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2008/08/08
CVS_DISTMODS=		gcc/libffi gcc/config/accross.m4
CVS_DISTFILE=		libffi
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# Historic Permission Clause
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/gcc/libffi
CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes
MAKE_FLAGS+=		'libffi_la_OBJECTS=$$(libffi_la_SOURCES:T:R:=.lo)'
EXTRA_XAKE_FLAGS+=	toolexeclibdir='$$(libdir)'

post-extract:
	print '/libtool.m4/d\nwq' | ed -s ${WRKSRC}/acinclude.m4

.include <bsd.port.mk>
