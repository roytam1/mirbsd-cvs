# $MirOS: ports/audio/flac/Makefile,v 1.2 2005/03/25 23:13:57 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2003/04/18 00:28:40 naddy Exp $

COMMENT=	"free lossless audio codec"

DISTNAME=	flac-1.1.0
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio archivers
HOMEPAGE=	http://flac.sourceforge.net/


# (L)GPL, GFDL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=flac/}

MODULES=	converters/libiconv
LIB_DEPENDS=	ogg::audio/libogg

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=	::lang/nasm
.endif

USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED} \
		--enable-3dnow \
		--with-libiconv-prefix="${LOCALBASE}" \
		--with-ogg="${LOCALBASE}"
CONFIGURE_ENV=	CPPFLAGS="-I${WRKSRC}/include" \
		XMMS_CONFIG=/usr/bin/false

# "obj" is magic to our make(1)
post-configure:
	@rm -rf ${WRKSRC}/obj

post-install:
	@cd ${PREFIX}/share/doc && mv ${DISTNAME} flac

.include <bsd.port.mk>
