# $MirOS$
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/20 19:54:58 espie Exp $
# $FreeBSD: ports/sysutils/e2fsprogs/Makefile,v 1.8 2003/02/20 19:00:47 knu Exp $

COMMENT=		"utilities to manipulate ext2 and ext3 filesystems"
DISTNAME=		e2fsprogs-1.36
CATEGORIES=		sysutils
HOMEPAGE=		http://e2fsprogs.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=e2fsprogs/}

# GNU GPLv2
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

.include <mirports.sys.mk>

SEPARATE_BUILD= 	concurrent
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-compression \
			--enable-htree \
			--disable-fsck \
			--disable-e2initrd-helper \
			--disable-nls
.if ${NO_SHARED_LIBS:L} == "yes"
CONFIGURE_ARGS+=	--disable-elf-shlibs
.else
CONFIGURE_ARGS+=	--enable-elf-shlibs \
			--enable-dynamic-e2fsck
.endif
USE_GMAKE=		Yes
CPPFLAGS+=		-DI_KNOW_THAT_COMPRESSION_IS_EXPERIMENTAL	# d'oh

.include <bsd.port.mk>
