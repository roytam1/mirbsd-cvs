# $MirOS: ports/devel/gmp/Makefile,v 1.5 2008/07/30 15:22:32 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/02/22 22:21:01 naddy Exp $

COMMENT=		library for arbitrary precision arithmetic
DISTNAME=		gmp-4.1.4
CATEGORIES=		devel math
HOMEPAGE=		http://www.swox.com/gmp/
MASTER_SITES=		${MASTER_SITE_GNU:=gmp/}

# (L)GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-readline=no \
			--enable-mpbsd \
			--enable-mpfr

.include <mirports.sys.mk>

post-extract:
.if ${OStype} == "Darwin"
	cd ${WRKSRC}/mpn/x86 && rm -f {,*/{,*/}}{dive_1,mode1o}*
.endif
	rm -f ${WRKSRC}/gmp.info*

.include <bsd.port.mk>
