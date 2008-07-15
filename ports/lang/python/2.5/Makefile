# $MirOS: ports/lang/python/2.3/Makefile,v 1.8 2007/12/29 16:57:34 bsiegert Exp $

VERSION=		2.5
PATCHLEVEL=		.2
DASH_VER=		0

CONFIGURE_ARGS+=	--without-cxx
CONFIGURE_ENV+=	OPT='${CFLAGS}' LDFLAGS='-L${WRKSRC}'

SUBST_VARS+=		VERSION
USE_GMAKE=		yes

.include <bsd.port.mk>
