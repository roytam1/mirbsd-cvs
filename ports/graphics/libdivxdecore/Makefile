# $MirOS: ports/graphics/libdivxdecore/Makefile,v 1.2 2006/02/09 09:35:56 tg Exp $
# $OpenBSD: Makefile,v 1.5 2002/10/24 23:23:36 fgsch Exp $

COMMENT=			opendivx decoding API
DISTNAME=	libdivxdecore-0.4.7
CATEGORIES=	graphics devel
MASTER_SITES=	http://download2.projectmayo.com/dnload/divx4linux/xmps/
HOMEPAGE=	http://www.projectmayo.com/projects/detail.php?projectId=4

# Mayo licence, h263 decoding
PERMIT_PACKAGE_CDROM=	"No commercial use plus patent issue"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"No commercial use plus patent issue"
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

.include <bsd.port.mk>
