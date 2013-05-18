# $MirOS: ports/devel/luaposix/Makefile,v 1.3 2009/08/29 13:17:55 tg Exp $
# $OpenBSD: Makefile,v 1.10 2008/06/11 05:04:37 landry Exp $

COMMENT=		posix library for the lua language
DISTNAME=		luaposix-20060408
CATEGORIES=		devel
MASTER_SITES=		http://mirrors.protection.cx/~pedro/
HOMEPAGE=		http://www.tecgraf.puc-rio.br/~lhf/ftp/lua/

# Public domain
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		lang/lua
NO_REGRESS=		Yes
SHARED_ONLY=		Yes

MAKE_FILE=		${.SYSMK}/bsd.lib.mk
EXTRA_XAKE_FLAGS+=	LIB=posix \
			SHLIB_SONAME=posix.so \
			SHLIB_VERSION=- \
			SRCS=luaposix.c \
			NOPICINSTALL=no \
			_LIBS_STATIC=no \
			LIBDIR=${TRUEPREFIX:Q}/lib/lua/5.1

.if (${MACHINE_OS} == "Darwin")
LDFLAGS+=		-bundle -undefined dynamic_lookup
.endif

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/lua/5.1

.include <bsd.port.mk>
