# $MirOS: ports/lang/m4/Makefile,v 1.2 2005/05/21 02:52:36 tg Exp $
# $OpenBSD: Makefile,v 1.18 2002/12/29 20:19:11 fgsch Exp $
# $FreeBSD: Makefile,v 1.7 1997/06/16 08:22:35 max Exp $
#-
# On Interix, this port cannot depend on autoconf.

COMMENT=		"GNU m4"
DISTNAME=		m4-1.4.2
CATEGORIES=		devel lang
MASTER_SITES=		${MASTER_SITE_GNU:=m4/}
HOMEPAGE=		http://www.gnu.org/software/m4/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>
.if ${OStype} == "Interix"
BUILD_DEPENDS+=		::essentials/texinfo
CONFIGURE_STYLE=	gnu dest
.else
CONFIGURE_STYLE=	autoconf dest
AUTOCONF_NEW=		Yes
.endif
CONFIGURE_ARGS=		--program-prefix="g"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gm4
	${INSTALL_DATA} ${WRKSRC}/examples/*.m4 ${PREFIX}/share/examples/gm4/

.include <bsd.port.mk>
