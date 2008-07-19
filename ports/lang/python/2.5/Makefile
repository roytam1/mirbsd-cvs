# $MirOS: ports/lang/python/2.5/Makefile,v 1.1 2008/07/15 19:18:51 bsiegert Exp $

VERSION=		2.5
PATCHLEVEL=		.2
DASH_VER=		1

CONFIGURE_ARGS+=	--without-cxx
CONFIGURE_ENV+=	OPT='${CFLAGS}' LDFLAGS='-L${WRKSRC} -L${PREFIX}/lib'

SUBST_VARS+=		VERSION
MODGNU_RECURSE_DIRS?=	${WRKSRC}
MODGNU_RECURSE_DIRS+=	${WRKSRC}/Modules/_ctypes/libffi
USE_GMAKE=		yes
MODULES+=		devel/gettext

.include <bsd.port.mk>
