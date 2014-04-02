# $MirOS: ports/audio/flac/Makefile,v 1.11 2007/03/21 10:39:31 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2003/04/18 00:28:40 naddy Exp $

COMMENT=		free lossless audio codec
DISTNAME=		flac-1.1.2
DASH_VER=		3
CATEGORIES=		audio archivers
HOMEPAGE=		http://flac.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=flac/}

# (L)GPL, GFDL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

USE_ICONV?=		any
USE_ICONV+=		oldm4

MODULES+=		devel/gettext
LIB_DEPENDS=		ogg::audio/libogg

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
