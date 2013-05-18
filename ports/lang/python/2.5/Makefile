# $MirOS: ports/lang/python/2.5/Makefile,v 1.15 2009/05/30 20:39:01 tg Exp $

VERSION=		2.5
PATCHLEVEL=		.4

LIB_DEPENDS+=		ffi::devel/libffi
LIB_DEPENDS+=		gdbm::databases/gdbm
LIB_DEPENDS+=		sqlite3::databases/sqlite

CONFIGURE_ARGS+=	--without-cxx
CONFIGURE_ARGS+=	--with-system-ffi
CONFIGURE_ARGS+=	--enable-unicode=ucs2
CONFIGURE_ENV+=		OPT=${CFLAGS:Q}
LDFLAGS+=		-L${WRKSRC:Q} -L${PREFIX:Q}/lib

SUBST_VARS+=		VERSION
USE_GMAKE=		yes
MODULES+=		devel/gettext

.include <mirports.sys.mk>

.if ${OStype:NInterix:NOpenBSD}
CONFIGURE_ARGS+=	--with-wctype-functions
.endif

# cover for possible hidden dependencies
.if exists(${LOCALBASE}/lib/libncursesw.la) && !exists(/usr/lib/libncursesw.a)
LIB_DEPENDS+=		ncursesw::devel/libncursesw
.endif

.include <bsd.port.mk>
