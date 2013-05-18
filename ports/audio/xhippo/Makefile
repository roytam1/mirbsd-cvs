# $MirOS: ports/audio/xhippo/Makefile,v 1.3 2006/02/09 11:11:08 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/04/02 19:07:04 sturm Exp $

COMMENT=	"generic playlist manager for UNIX"

DISTNAME=	xhippo-3.3
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio

HOMEPAGE=	http://www.gnu.org/software/xhippo/


PERMIT_PACKAGE_CDROM=  Yes
PERMIT_PACKAGE_FTP=    Yes
PERMIT_DISTFILES_CDROM=Yes
PERMIT_DISTFILES_FTP=  Yes

MASTER_SITES=	${MASTER_SITE_GNU:=xhippo/}

LIB_DEPENDS=	gdk_pixbuf_xlib-2.0.0.0::x11/gtk+ \
		id3tag::audio/libid3tag

USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	--with-gtk2

MODULES=	devel/gettext devel/pkgconfig

DOCS=	ChangeLog gnu-xhippo.html screenshot.jpeg xhippo.html.gz \
	xhippo.info.gz xhippo.ps.gz xhippo.sgml xhippo.txt.gz xhippo_toc.html

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xhippo
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xhippo
	${INSTALL_DATA} ${WRKSRC}/xhippo.config ${PREFIX}/share/examples/xhippo/xhippo.config-sample
	${INSTALL_DATA} ${WRKSRC}/xhippo.gtkrc ${PREFIX}/share/examples/xhippo
	cd ${WRKSRC}/doc; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/xhippo 

.include <bsd.port.mk>
