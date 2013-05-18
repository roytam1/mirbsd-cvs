# $MirOS: ports/essentials/texinfo/Makefile,v 1.3 2005/11/10 22:20:45 tg Exp $
#-
# This port must not depend on autoconf, and be built without GNU m4.

COMMENT=			GNU's man page successor
DISTNAME=		texinfo-4.8
CATEGORIES=		textproc
MASTER_SITES=		${MASTER_SITE_GNU:=texinfo/}
HOMEPAGE=		http://www.gnu.org/software/texinfo/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-nls
NO_REGRESS=		Yes

.include <bsd.port.mk>
