# $MirOS: ports/sysutils/ntfsprogs/Makefile,v 1.2 2006/09/14 00:13:39 tg Exp $
# $NetBSD: Makefile,v 1.2 2004/10/09 10:29:12 kristerw Exp $

COMMENT=		Linux-NTFS project utilities for the NT Filesystem (ntfs)
DISTNAME=		ntfsprogs-1.13.1
CATEGORIES=		sysutils
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=linux-ntfs/}
HOMEPAGE=		http://www.linux-ntfs.org/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		debug
FLAVOR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-fuse-module

# XXX support for this should be possibly integrated with other
# gnome pkgsrc and this could be a configurable option
CONFIGURE_ARGS+=	--disable-gnome-vfs

.if ${FLAVOR:Mdebug}
CONFIGURE_ARGS+=	--enable-debug
.else
CONFIGURE_ARGS+=	--disable-debug
.endif

.include <bsd.port.mk>
