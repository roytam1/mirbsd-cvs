# $MirOS: ports/devel/gmake/Makefile,v 1.13 2007/02/22 22:57:47 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/04/06 03:12:19 brad Exp $
#-
# Must not have any dependencies, unless they are listed in CVSROOT/modules.

COMMENT=		GNU implementation of the make utility (enhanced)
DISTNAME=		make-3.81
PKGNAME=		g${DISTNAME}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://www.gnu.org/software/make/
MASTER_SITES=		${MASTER_SITE_GNU:=make/}

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	gnu
MODGNU_TYPESCAN=	setvbuf
CONFIGURE_ARGS+=	--program-prefix="g"
CONFIGURE_ARGS+=	--disable-nls
.if ${MACHINE_OS} == "Darwin"
CPPFLAGS+=		-Dstrcmpi=strcasecmp
.endif

post-extract:
	rm -f ${WRKSRC}/doc/make.info*

.include <bsd.port.mk>
