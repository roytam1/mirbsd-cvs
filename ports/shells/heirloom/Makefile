# $MirOS: ports/shells/heirloom/Makefile,v 1.1 2007/04/04 22:13:23 tg Exp $

COMMENT=		portable variant of the traditional Unix (Bourne) shell
CATEGORIES=		shells
DISTNAME=		heirloom-sh-050706
DASH_VER=		1
HOMEPAGE=		http://heirloom.sourceforge.net/sh.html
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=heirloom/}
EXTRACT_SUFX=		.tar.bz2	# Gunnar, this sucks.

# Caldera, CDDL
PERMIT_DISTFILES_CDROM=	"CDDL"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"CDDL"
PERMIT_PACKAGE_FTP=	Yes

MAKE_FILE=		${FILESDIR}/BSDmakefile

.include <bsd.port.mk>
