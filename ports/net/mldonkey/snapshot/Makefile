# $MirOS: ports/net/mldonkey/snapshot/Makefile,v 1.4 2008/05/07 22:48:37 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/04/19 08:42:25 espie Exp $

BROKEN=			unfetchable distfile

COMMENT=		Filesharing client/server for multiple networks
CATEGORIES=		net
DISTNAME=		mldonkey-2.5.18
HOMEPAGE=		http://savannah.nongnu.org/projects/mldonkey/
MASTER_SITES=		http://savannah.nongnu.org/download/mldonkey/

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/config
CONFIGURE_ARGS+=	--enable-ocamlver=3.07

USE_GMAKE=		Yes
MODULES=		lang/ocaml
BUILD_DEPENDS+=		::x11/lablgtk
LIB_DEPENDS+=		gdk.1,gtk.1::x11/gtk+1
FAKE_FLAGS+=		prefix=${DESTDIR}${PREFIX} \
			MODOCAML_NATIVE=${MODOCAML_NATIVE}
NO_REGRESS=		Yes

post-install:
	mkdir -p ${PREFIX}/share/mldonkey
	cp -R ${WRKDIST}/{distrib,docs} ${PREFIX}/share/mldonkey

.include <bsd.port.mk>
