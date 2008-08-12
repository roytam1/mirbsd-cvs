# $MirOS: ports/lang/python/2.5/Makefile,v 1.7 2008/08/12 09:38:13 tg Exp $

VERSION=		2.5
PATCHLEVEL=		.2
DASH_VER=		5

LIB_DEPENDS+=		ffi::devel/libffi
LIB_DEPENDS+=		sqlite3::databases/sqlite

CONFIGURE_ARGS+=	--without-cxx
CONFIGURE_ARGS+=	--with-system-ffi
CONFIGURE_ENV+=		OPT=${CFLAGS:Q} \
			LDFLAGS=-L${WRKSRC:Q}\ -L${PREFIX:Q}/lib

SUBST_VARS+=		VERSION
MODGNU_RECURSE_DIRS?=	${WRKSRC}
MODGNU_RECURSE_DIRS+=	${WRKSRC}/Modules/_ctypes/libffi
USE_GMAKE=		yes
MODULES+=		devel/gettext

.include <mirports.sys.mk>

.if ${OStype:NInterix:NOpenBSD}
CONFIGURE_ARGS+=	--with-wctype-functions
.endif

.include <bsd.port.mk>
