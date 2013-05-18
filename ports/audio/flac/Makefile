# $MirOS: ports/audio/flac/Makefile,v 1.7 2006/02/01 17:51:55 tg Exp $
# $OpenBSD: Makefile,v 1.18 2003/04/18 00:28:40 naddy Exp $

COMMENT=		"free lossless audio codec"
DISTNAME=		flac-1.1.2
PKGNAME?=		${DISTNAME}-1
CATEGORIES=		audio archivers
HOMEPAGE=		http://flac.sourceforge.net/

# (L)GPL, GFDL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=flac/}

MODULES=		converters/libiconv
LIB_DEPENDS=		ogg::audio/libogg

# for two .m4 files (no actual code)
BUILD_DEPENDS+=		::devel/gettext

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=		::lang/nasm
.endif

USE_CXX=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-3dnow \
			--with-libiconv-prefix="${ICONV_PREFIX}" \
			--with-ogg="${LOCALBASE}"
CONFIGURE_ENV+=		ac_cv_path_XMMS_CONFIG=false \
			ac_cv_prog_DOXYGEN=false
CPPFLAGS+=		-I${WRKSRC}/include

# "obj" is magic to our make(1)
post-configure:
	@rm -rf ${WRKSRC}/obj

post-install:
	@cd ${PREFIX}/share/doc && mv ${DISTNAME} flac

.include <bsd.port.mk>
