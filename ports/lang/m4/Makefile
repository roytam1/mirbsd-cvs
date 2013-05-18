# $MirOS: ports/lang/m4/Makefile,v 1.11 2009/11/18 20:50:05 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2002/12/29 20:19:11 fgsch Exp $
# $FreeBSD: Makefile,v 1.7 1997/06/16 08:22:35 max Exp $
#-
# On Interix and MidnightBSD, this port cannot depend on autoconf.
# On MirBSD and OpenBSD, this port cannot depend on autoconf 2.62 or up.

COMMENT=		GNU m4
DISTNAME=		m4-1.4.9
CATEGORIES=		devel lang
MASTER_SITES=		${MASTER_SITE_GNU:=m4/}
HOMEPAGE=		http://www.gnu.org/software/m4/

# GNU GPLv3+
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

.if ${OStype} == "Interix"
BUILD_DEPENDS+=		::essentials/texinfo
.endif
CONFIGURE_STYLE=	gnu
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--program-prefix="g"

post-extract:
	-cd ${WRKSRC}/doc && rm -f m4.info*

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gm4
	${INSTALL_DATA} ${WRKSRC}/examples/*.m4 ${PREFIX}/share/examples/gm4/

.include <bsd.port.mk>

_CIPHERS+=		cksum
