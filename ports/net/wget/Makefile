# $MirOS: ports/net/wget/Makefile,v 1.5 2005/11/10 23:45:16 tg Exp $
# $OpenBSD: Makefile,v 1.35 2003/05/14 15:03:51 brad Exp $

COMMENT=		"retrieve files via HTTP and FTP"
V=			1.10.2
P=			1
DISTNAME=		wget-${V}
PKGNAME=		wget-${V}-${P}
CATEGORIES=		net
MASTER_SITES=		${MASTER_SITE_GNU:=wget/}
MASTER_SITES0=		http://ftp.fr.debian.org/debian/pool/main/w/wget/ \
			ftp://ftp.us.debian.org/debian/pool/main/w/wget/
HOMEPAGE=		http://www.gnu.org/software/wget/

PATCHFILES=		wget_${V}-${P}.diff.gz:0
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
