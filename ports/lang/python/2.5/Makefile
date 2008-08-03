# $MirOS: ports/lang/python/2.5/Makefile,v 1.3 2008/08/03 21:30:02 tg Exp $

VERSION=		2.5
PATCHLEVEL=		.2
DASH_VER=		2

CONFIGURE_ARGS+=	--without-cxx
CONFIGURE_ENV+=		OPT=${CFLAGS:Q} \
			LDFLAGS=-L${WRKSRC:Q}\ -L${PREFIX:Q}/lib

SUBST_VARS+=		VERSION
MODGNU_RECURSE_DIRS?=	${WRKSRC}
MODGNU_RECURSE_DIRS+=	${WRKSRC}/Modules/_ctypes/libffi
USE_GMAKE=		yes
MODULES+=		devel/gettext

.include <bsd.port.mk>
