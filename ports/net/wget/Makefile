# $MirOS: ports/net/wget/Makefile,v 1.1.7.1 2005/03/18 15:49:22 tg Exp $
# $OpenBSD: Makefile,v 1.35 2003/05/14 15:03:51 brad Exp $

COMMENT=		"retrieve files via HTTP and FTP"
V=			1.10
P=			2
DISTNAME=		wget-${V}
PKGNAME=		wget-${V}-${P}-0
CATEGORIES=		net
MASTER_SITES=		${MASTER_SITE_GNU:=wget/}
MASTER_SITES0=		ftp://ftp.us.debian.org/debian/pool/main/w/wget/
HOMEPAGE=		http://www.gnu.org/software/wget/

PATCHFILES=		wget_${V}-${P}.diff.gz:0
PATCH_DIST_STRIP=	-p1

# GNU GPLv2 or later
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls

.include <mirports.sys.mk>
.if ${OStype} == "Interix"
CONFIGURE_ARGS+=	--disable-ipv6
.endif

pre-build:
	print '1,$$g#/usr/local/etc#s##${SYSCONFDIR}#g\n1,$$g#/usr/local#s##${PREFIX}#g\nwq' \
	    | ed -s ${WRKSRC}/doc/wget.texi
	print '1,$$g#/usr/local/etc#s##${SYSCONFDIR}#g\nwq' \
	    | ed -s ${WRKSRC}/doc/sample.wgetrc

.include <bsd.port.mk>
