# $OpenBSD: Makefile,v 1.12 2004/02/16 18:18:43 jcs Exp $

DISTNAME=	sybperl-2.16
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	databases perl5

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Sybase database access in Perl
HOMEPAGE=	http://www.mbay.net/~mpeppler/
MASTER_SITES=	http://www.peppler.org/downloads/


MODULES=	devel/gettext
LIB_DEPENDS=	tds.3,sybdb.4,ct.2::databases/freetds

CONFIGURE_STYLE= perl
CONFIGURE_ENV=	SYBASE="${LOCALBASE}"
NO_REGRESS=	Yes

.include <bsd.port.mk>
