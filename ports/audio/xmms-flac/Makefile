# $MirOS: ports/audio/xmms-flac/Makefile,v 1.4 2006/02/02 21:09:38 tg Exp $
# $OpenBSD: Makefile,v 1.8 2003/10/23 01:36:27 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			XMMS input plugin for playing FLAC files

VERSION=	1.1.0
PKGNAME=	xmms-flac-${VERSION}-0
DISTNAME=	flac-${VERSION}
CATEGORIES=	audio
HOMEPAGE=	http://flac.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=flac/}
MASTER_SITES0=	ftp://ftp.debian.org/debian/pool/main/f/flac/ \
		ftp://ftp.de.debian.org/debian/pool/main/f/flac/
PATCHFILES=	flac_${VERSION}-10.diff.gz:0
PATCH_DIST_STRIP= -p1

LIB_DEPENDS=	xmms.3::audio/xmms \
		FLAC.5::audio/flac
MODULES+=	converters/libiconv

USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	--with-libiconv-prefix="${ICONV_PREFIX}" \
		--with-ogg="${LOCALBASE}" \
		--with-xmms-prefix="${LOCALBASE}"

MAKE_FILE=	${FILESDIR}/Makefile

# "obj" is magic to our make(1)
post-configure:
	@rm -rf ${WRKSRC}/obj

NO_REGRESS=	Yes

.include <bsd.port.mk>
