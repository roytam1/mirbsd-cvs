# $MirOS$
# $OpenBSD: Makefile,v 1.3 2004/05/21 22:55:41 sturm Exp $

COMMENT=		filter to print a wide range of file formats

DISTNAME=		apsfilter-7.2.5
DASH_VER=		1
CATEGORIES=		print

HOMEPAGE=		http://www.apsfilter.org/


# GPL license
PERMIT_PACKAGE_CDROM=	dependency print/a2ps is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.apsfilter.org/download/

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-shell=/bin/sh

RUN_DEPENDS=		:psutils-*:print/psutils \
			:a2ps-*:print/a2ps

WRKDIST=		${WRKDIR}/apsfilter/

.include <bsd.port.mk>
