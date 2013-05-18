# $MirOS: ports/graphics/gle/Makefile,v 1.1.7.1 2005/03/18 15:46:51 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/09/22 22:53:37 pvalchev Exp $

COMMENT=		"OpenGL Extrusion library"
VERSION=		3.0.4
DISTNAME=		gle-${VERSION}
CATEGORIES=     	graphics devel
HOMEPAGE=		http://www.linas.org/gle/

LIB_DEPENDS=		glut.3::graphics/glut

# Artistic/custom
PERMIT_PACKAGE_CDROM=	"unclear"
PERMIT_PACKAGE_FTP=	"unclear"
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.linas.org/gle/pub/
USE_CXX=		Yes		# needs libGLU
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ENV=		CPPFLAGS="-I${LOCALBASE}/include" \
			LDFLAGS="-L${LOCALBASE}/lib -L${X11BASE}/lib -lXi"

post-extract:
	@perl -i -p -e 's/3GLE/3/;' ${WRKSRC}/man/*.man

.include <bsd.port.mk>
