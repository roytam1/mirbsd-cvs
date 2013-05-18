# $MirOS: ports/net/pavuk/Makefile,v 1.2 2005/07/07 21:24:47 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2003/01/30 22:39:07 espie Exp $

COMMENT=	"tool to mirror contents of HTTP and FTP servers"

DISTNAME=	pavuk-0.9pl28
PKGNAME=	${DISTNAME}a-0
CATEGORIES=	net
EXTRACT_SUFX=	.tgz

MASTER_SITES=	http://www.pavuk.org/sw/ \
		http://www.idata.sk/~ondrej/sw/ \
		http://www.doc.cs.univ-paris8.fr/mirrors/pavuk/sw/

HOMEPAGE=	http://www.pavuk.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=	no_x11
FLAVOR?=

MODULES=	devel/gettext

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= --disable-debug --disable-tree  \
		 --disable-gnome --with-regex=posix \
		 --disable-socks

.if !${FLAVOR:L:Mno_x11}
LIB_DEPENDS+=	gtk.1.2,gdk.1.2::x11/gtk+
USE_X11=	Yes
.else
CONFIGURE_ARGS+= --disable-gtk
.endif

DOCS=		COPYING FAQ README jsbind.txt wget-pavuk.HOWTO
SAMPLES=	pavukrc.sample

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pavuk
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/pavuk
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/pavuk
	cd ${WRKSRC} && ${INSTALL_DATA} ${SAMPLES} \
	  ${PREFIX}/share/examples/pavuk

.include <bsd.port.mk>
