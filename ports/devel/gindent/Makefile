# $OpenBSD: Makefile,v 1.22 2002/08/26 02:58:36 pvalchev Exp $

COMMENT=			GNU utility to indent C source files

DISTNAME=	indent-2.2.8
PKGNAME=	g${DISTNAME}-0
CATEGORIES=	devel

HOMEPAGE=	http://www.gnu.org/software/indent/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=indent/}

MODULES=	devel/gettext

NO_REGRESS=	Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--program-prefix="g" --without-included-gettext
MAKE_ARGS=	BERKELEY_DEFAULTS=1

.include <bsd.port.mk>
