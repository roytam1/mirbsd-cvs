# $MirOS: ports/security/libgpg-error/Makefile,v 1.1.7.1 2005/03/18 15:51:30 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/07 20:26:19 sturm Exp $

COMMENT=	"error codes for GnuPG related software"
DISTNAME=	libgpg-error-1.0
CATEGORIES=	security devel

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.gnupg.org/gcrypt/libgpg-error/ \
		ftp://gd.tuwien.ac.at/privacy/gnupg/libgpg-error/ \
		http://ftp.planetmirror.com/pub/gnupg/libgpg-error/ \
		http://sunsite.dk/pub/security/gcrypt/libgpg-error/ \
		http://ftp.linux.it/pub/mirrors/gnupg/libgpg-error/

MODULES=	devel/gettext


CONFIGURE_STYLE=autoconf
CONFIGURE_ARGS+=${CONFIGURE_SHARED}
AUTOCONF_NEW=	Yes

.include <bsd.port.mk>
