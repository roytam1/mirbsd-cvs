# $MirOS: ports/databases/dbh/Makefile,v 1.3 2006/02/09 11:11:16 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/04/18 00:58:31 jolan Exp $

COMMENT=			library to create Disk Based Hashtables on POSIX systems
DISTNAME=	dbh_1.0-18
PKGNAME=	${DISTNAME:L:S/-/./:S/_/-/}-0
CATEGORIES=	databases
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=dbh/}
EXTRACT_SUFX=	.tar.bz2
HOMEPAGE=	http://dbh.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		devel/pkgconfig
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes

.include <bsd.port.mk>
