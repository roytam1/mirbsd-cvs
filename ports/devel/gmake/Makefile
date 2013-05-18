# $MirOS: ports/devel/gmake/Makefile,v 1.7 2006/06/16 15:33:41 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/04/06 03:12:19 brad Exp $
#-
# This port must not have dependencies, or list them in CVSROOT/modules.

COMMENT=		GNU make
DISTNAME=		make-3.81
PKGNAME=		g${DISTNAME}-0
CATEGORIES=		devel
HOMEPAGE=		http://www.gnu.org/software/make/
MASTER_SITES=		${MASTER_SITE_GNU:=make/}

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-prefix="g"
CONFIGURE_ARGS+=	--disable-nls
.if ${OStype} == "Darwin"
CONFIGURE_ARGS+=	--enable-case-insensitive-file-system
CPPFLAGS+=		-Dstrcmpi=strcasecmp
.endif
CONFIGURE_ENV+=		MAKEINFO="makeinfo --no-split"

post-extract:
	rm -f ${WRKSRC}/doc/make.info*

.include <bsd.port.mk>
