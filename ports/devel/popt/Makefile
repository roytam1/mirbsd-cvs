# $MirOS: ports/devel/popt/Makefile,v 1.6 2006/12/28 19:30:04 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/07/15 16:50:22 jolan Exp $

COMMENT=		getopt(3)-like library with a number of enhancements
DISTNAME=		popt-1.7
DASH_VER=		2
CATEGORIES=		devel
MASTER_SITES=		ftp://ftp.rpm.org/pub/rpm/dist/rpm-4.1.x/ \
			ftp://ftp.mirror.ac.uk/sites/ftp.rpm.org/pub/rpm/dist/rpm-4.1.x/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_MAKE_FLAGS=	libpopt_la_LDFLAGS="-version-info 3:0:3" # XXX WTF?
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-nls
MODULES+=		converters/libiconv

.include <bsd.port.mk>
