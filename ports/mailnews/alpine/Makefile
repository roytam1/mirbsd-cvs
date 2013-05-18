# $MirOS: ports/mailnews/alpine/Makefile,v 1.1 2008/02/17 15:29:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.56 2003/10/05 21:42:29 jakob Exp $

ONLY_FOR_PLATFORM=	Darwin:*:*

COMMENT=		alpine messaging system
CATEGORIES=		mailnews
VERSION=		1.00
DISTNAME=		alpine-${VERSION}
MASTER_SITES=		ftp://ftp.cac.washington.edu/alpine/ \
			ftp://ftp.cac.washington.edu/alpine/old
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.washington.edu/alpine/

# Apache Licence v2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes

FLAVOURS=		tcl
FLAVOUR?=

.if ${FLAVOUR:L:Mtcl}
LIB_DEPENDS+=		tcl::lang/tcl/8.4
.else
CONFIGURE_ARGS+=	--without-tcl
.endif

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
