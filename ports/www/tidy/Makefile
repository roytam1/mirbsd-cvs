# $MirOS: ports/www/tidy/Makefile,v 1.2 2005/07/07 21:28:23 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2003/10/18 19:44:59 sturm Exp $

COMMENT=			validate, correct, and pretty-print HTML files
COMMENT-lib=			library for accessing HTML validation functions
TIDYDATE=	040202
DISTNAME=	tidy_src_${TIDYDATE}
PKGNAME=	tidy-${TIDYDATE}-0
CATEGORIES=     www
MASTER_SITES=	http://tidy.sourceforge.net/src/old/
HOMEPAGE=	http://www.w3.org/People/Raggett/tidy/
EXTRACT_SUFX=	.tgz

# BSD-like, badly worded
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}/tidy
CONFIGURE_STYLE=	autogen
CONFIGURE_ARGS+=	--enable-access --enable-utf16 \
			--enable-asian --disable-shared

MULTI_PACKAGES=		-lib
SUBPACKAGE?=
DESCR?=			${.CURDIR}/pkg/DESCR

pre-patch:
	cd ${WRKSRC}/build/gnuauto && cp -R * ${WRKSRC}/
	touch ${WRKSRC}/{NEWS,README,AUTHORS,ChangeLog}	# shut up

.include <bsd.port.mk>
