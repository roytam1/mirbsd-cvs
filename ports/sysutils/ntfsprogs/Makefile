# $MirOS: ports/sysutils/ntfsprogs/Makefile,v 1.1.7.1 2005/03/18 15:52:18 tg Exp $
# $NetBSD: Makefile,v 1.2 2004/10/09 10:29:12 kristerw Exp $

BROKEN=			no <wchar.h>

COMMENT=			Linux-NTFS project utilities for the NT Filesystem (ntfs)
DISTNAME=		ntfsprogs-1.9.4
CATEGORIES=		sysutils
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=linux-ntfs/}
HOMEPAGE=		http://linux-ntfs.sourceforge.net/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-debug

# XXX support for this should be possibly integrated with other
# gnome pkgsrc and this could be a configurable option
CONFIGURE_ARGS+=	--disable-gnome-vfs

.include <bsd.port.mk>
