# $MirOS: ports/voip/libmutil/Makefile,v 1.2 2005/08/21 11:50:33 tg Exp $

COMMENT=			various C++ classes (strings, crypto, threads)
CATEGORIES=		voip devel
DISTNAME=		libmutil-0.3.0
HOMEPAGE=		http://www.minisip.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		http://www.minisip.org/source/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

# This needs to be built with -pthread yet there is not
# such option in the configure.ac. How to do this on an
# other OS such as Darwin or Interix?
CFLAGS+=		-pthread

.include <bsd.port.mk>
