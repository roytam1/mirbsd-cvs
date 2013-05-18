# $MirOS: ports/misc/findutils/Makefile,v 1.4 2008/12/15 21:06:44 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 19:49:40 fgsch Exp $

COMMENT=		finds and then operates on files
DISTNAME=		findutils-4.1
DASH_VER=		1
CATEGORIES=		misc
HOMEPAGE=		http://www.gnu.org/software/findutils/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=findutils/}

CONFIGURE_STYLE=	autoconf dest
CONFIGURE_ARGS+=	--program-prefix=g
EXTRA_XAKE_FLAGS+=	localstatedir=/var/db

# regenerate in one piece
post-extract:
	@rm -f ${WRKSRC}/doc/find.info*

post-install:
	-rm -rf ${PREFIX}/man/man*
	cd ${PREFIX}/man; for f in $$(find cat* -type f); do \
		mv $$f $${f%[0-9]}0; \
	done

.include <bsd.port.mk>
