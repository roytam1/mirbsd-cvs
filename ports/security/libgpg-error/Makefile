# $MirOS: ports/security/libgpg-error/Makefile,v 1.6 2007/03/20 18:28:26 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/07 20:26:19 sturm Exp $

COMMENT=		error codes for GnuPG related software
DISTNAME=		libgpg-error-1.6
# I hate you…
EXTRACT_SUFX=		.tar.bz2
CATEGORIES=		security devel
HOMEPAGE=		http://www.gnupg.org/related_software/libgpg-error/index.en.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.gnupg.org/gcrypt/libgpg-error/ \
			ftp://gd.tuwien.ac.at/privacy/gnupg/libgpg-error/ \
			ftp://sunsite.dk/pub/security/gcrypt/libgpg-error/ \
			ftp://ftp.linux.it/pub/mirrors/gnupg/libgpg-error/ \
			ftp://pgp.iijlab.net/pub/pgp/libgpg-error/ \
			ftp://ring.aist.go.jp/pub/net/gnupg/libgpg-error/

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-nls
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
