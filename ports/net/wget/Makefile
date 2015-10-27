# $MirOS: ports/net/wget/Makefile,v 1.10 2009/08/16 17:18:33 tg Exp $
# $OpenBSD: Makefile,v 1.35 2003/05/14 15:03:51 brad Exp $

COMMENT=		retrieve files via HTTP and FTP
VSN=			1.10.2
DASH_VER=		3
DISTNAME=		wget-${VSN}
CATEGORIES=		net
MASTER_SITES=		${MASTER_SITE_GNU:=wget/}
MASTER_SITES0=		${MASTER_SITE_DEBIAN:=w/wget/}
HOMEPAGE=		http://www.gnu.org/software/wget/

PATCHFILES=		wget_${VSN}-2.diff.gz:0
PATCH_DIST_STRIP=	-p1

# GNU GPLv2 or later
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls

.include <mirports.sys.mk>
.if ${MACHINE_OS} == "Interix"
CONFIGURE_ARGS+=	--disable-ipv6
.endif

pre-build:
	print '%g#/usr/local/etc#s##${SYSCONFDIR}#g\n%g#/usr/local#s##${PREFIX}#g\nwq' \
	    | ed -s ${WRKSRC}/doc/wget.texi
	print '%g#/usr/local/etc#s##${SYSCONFDIR}#g\nwq' \
	    | ed -s ${WRKSRC}/doc/sample.wgetrc

.include <bsd.port.mk>
