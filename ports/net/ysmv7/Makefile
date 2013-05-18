# $OpenBSD: Makefile,v 1.9 2004/04/09 09:52:10 espie Exp $

COMMENT=			ICQ console client with encryption support

DISTNAME=		ysmv7_2_9_2
PKGNAME=		${DISTNAME:S/_/-/:S/_/./g}-0
CATEGORIES=		net

HOMEPAGE=		http://ysmv7.sourceforge.net/

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=ysmv7/}


MODULES=		converters/libiconv

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tgz

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes

NO_REGRESS=		Yes

.include <bsd.port.mk>
