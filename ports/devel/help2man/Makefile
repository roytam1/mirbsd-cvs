# $MirOS: ports/devel/help2man/Makefile,v 1.3 2005/11/10 21:13:45 tg Exp $
# $OpenBSD: Makefile,v 1.5 2002/11/13 19:04:53 naddy Exp $

COMMENT=	"GNU help2man"
DISTNAME=	help2man-1.29
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=help2man/}
HOMEPAGE=	http://www.gnu.org/software/help2man/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>
.if ${OStype} == "Interix"
BUILD_DEPENDS+=		::essentials/texinfo
.endif

CONFIGURE_STYLE=	gnu
INSTALL_STRIP=

post-extract:
	@rm -f ${WRKSRC}/help2man.info*

.include <bsd.port.mk>
