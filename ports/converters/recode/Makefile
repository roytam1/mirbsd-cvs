# $MirOS: ports/converters/recode/Makefile,v 1.2 2005/07/07 21:18:19 bsiegert Exp $
# $OpenBSD: Makefile,v 1.22 2003/04/27 21:00:21 avsm Exp $

COMMENT=	"convert files between character sets and usages"
DISTNAME=	recode-3.6
PKGNAME=	${DISTNAME}-1
CATEGORIES=	converters textproc
HOMEPAGE=	http://www.gnu.org/software/recode/
MODULES=	devel/gettext

# License: GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=recode/}

CONFIGURE_STYLE=autoconf
CONFIGURE_ARGS=	--without-included-gettext

REGRESS_DEPENDS=	:python-*:lang/python

post-extract:
	@cd ${WRKSRC}/lib && cp -p error.c ../src

post-regress:
	@cd ${WRKBUILD}/tests && ${MAKE} \
		PYTHON=${LOCALBASE}/bin/python bigtest

.include <bsd.port.mk>
