# $OpenBSD: Makefile,v 1.2 2003/12/23 23:21:12 naddy Exp $

COMMENT=	GNU versions of grep pattern matching utilities

DISTNAME=	grep-2.5.1
PKGNAME=	g${DISTNAME}-1
CATEGORIES=	sysutils
HOMEPAGE=	http://www.gnu.org/software/grep/grep.html


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=grep/}

MODULES=	devel/gettext
LIB_DEPENDS=	pcre.0::devel/pcre

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	--program-prefix=g

post-build:
	@perl -i -pe 's/\bgrep\b/ggrep/g' ${WRKBUILD}/src/[ef]grep

.include <bsd.port.mk>
