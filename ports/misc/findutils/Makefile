# $OpenBSD: Makefile,v 1.8 2002/12/29 19:49:40 fgsch Exp $

COMMENT=		"finds and then operates on files"

DISTNAME=		findutils-4.1
CATEGORIES=		misc

HOMEPAGE=		http://www.gnu.org/software/findutils/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=findutils/}

MODULES=		devel/gettext

CONFIGURE_STYLE=	gnu dest old
CONFIGURE_ARGS=		--program-prefix="g"
MAKE_FLAGS=		localstatedir=/var/db
FAKE_FLAGS=		DESTDIR=${WRKINST}

# regenerate in one piece
post-extract:
	@rm -f ${WRKSRC}/doc/find.info*

.include <bsd.port.mk>
