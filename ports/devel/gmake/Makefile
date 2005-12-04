# $MirOS: ports/devel/gmake/Makefile,v 1.4 2005/07/07 21:19:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.29 2004/04/06 03:12:19 brad Exp $
#-
# This port must not have dependencies, or list them in CVSROOT/modules.

COMMENT=	"GNU make"
DISTNAME=	make-3.80
PKGNAME=	g${DISTNAME}-1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=make/}
HOMEPAGE=	http://www.gnu.org/software/make/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SEPARATE_BUILD=	simple
CONFIGURE_STYLE=gnu
CONFIGURE_ARGS= --program-prefix="g" --disable-nls
CONFIGURE_ENV+=	MAKEINFO="makeinfo --no-split"

post-extract:
	@rm -f ${WRKSRC}/doc/make.info*

post-install:
	@chmod ${BINMODE} ${PREFIX}/bin/gmake
	@chown ${BINOWN}:${BINGRP} ${PREFIX}/bin/gmake

# XXX This is the ONE case where we shouldn't be able to cheat on 
# where HOME is coming from, but we can. Looks like gnu-make is bogus...

REGRESS_FLAGS=HOME=/

.include <bsd.port.mk>
