# $MirOS: ports/misc/hfsplus/Makefile,v 1.4 2005/07/07 21:23:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2003/02/15 14:37:19 espie Exp $

# use NO_IGNORE=Yes to build this on OpenBSD with OpenBSD ports framework
IGNORE=		"might be broken, used to use Libtool"

# this only makes sense on macintosh (powerpc) systems.
ONLY_FOR_PLATFORM=	*:*:powerpc

COMMENT=	"hfsplus filesystem access tool"
VERSION=	1.0.4
DISTNAME=	hfsplus_${VERSION}
PKGNAME=	hfsplus-${VERSION}-0
WRKDIST=	${WRKDIR}/hfsplus-${VERSION}
CATEGORIES=	misc
EXTRACT_SUFX=	.src.tar.bz2

# GPL
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes

BUILD_DEPENDS=	::devel/autoconf/${AUTOCONF_VERSION} \
		::devel/metaauto \
		::devel/automake
LIB_DEPENDS=	utf8::misc/libutf8

USE_LIBTOOL=	Yes
USE_GMAKE=	Yes

HOMEPAGE=	http://ftp.penguinppc.org/projects/hfsplus/
MASTER_SITES=	http://ftp.penguinppc.org/projects/hfsplus/

# actually uses automake/autoheader, but that is done in pre-configure now
CONFIGURE_STYLE= gnu
CONFIGURE_ENV=	LIBS="-lutf8"
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}

pre-configure:
	@cd ${WRKDIST} && AUTOCONF_VERSION=${AUTOCONF_VERSION} ${MAKE_PROGRAM} -f Makefile.cvs all

.include <bsd.port.mk>
