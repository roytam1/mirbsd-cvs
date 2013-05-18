# $MirOS: ports/devel/fribidi/Makefile,v 1.2 2006/06/24 23:57:23 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/01/11 16:45:51 couderc Exp $

COMMENT=			Library implementing the Unicode Bidirectional Algorithm
DISTNAME=		fribidi-0.10.4
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel
HOMEPAGE=		http://fribidi.org/
MASTER_SITES=		${HOMEPAGE}download/

# GNU LGPLv2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
