# $MirOS: ports/graphics/netpbm/Makefile,v 1.6 2007/04/13 19:30:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.30 2004/02/23 08:20:11 pvalchev Exp $
# $NetBSD: Makefile,v 1.25 1999/03/04 14:18:54 tron Exp $

COMMENT=		toolkit for converting images between different formats
COMMENT-hpcd=		convert photo CD images into ppm format
VERSION=		9.24
DISTNAME=		netpbm-${VERSION}
DASH_VER=		3
PKGNAME-hpcd=		hpcdtoppm-${VERSION}-${DASH_VER}
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=netpbm/}
EXTRACT_SUFX=		.tgz
HOMEPAGE=		http://netpbm.sourceforge.net/
LIB_DEPENDS=		tiff::graphics/tiff \
			jpeg::graphics/jpeg
MODULES+=		graphics/png

MULTI_PACKAGES=		-hpcd
SUBPACKAGE?=

# GPL, BSD/MIT, etc.
# hpcd is under a commercial licence
# There are patent issues (LZW, JBIG)
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee"
.if ${SUBPACKAGE} == "-hpcd"
PERMIT_PACKAGE_CDROM=	"no fee"
.else
PERMIT_PACKAGE_CDROM=	Yes
.endif

FAKE_FLAGS=		PREFIX="${WRKINST}${TRUEPREFIX}"
USE_GMAKE=		Yes
MAKE_FILE=		GNUmakefile

pre-build:
	@mv -f ${WRKSRC}/pm_config.h ${WRKSRC}/pm_config.h.new
	@mv -f ${WRKSRC}/pbm/pm.h ${WRKSRC}/pbm/pm.h.new
	@sed -e s#!!X11R6!!#${X11BASE}#g \
		${WRKSRC}/pm_config.h.new > ${WRKSRC}/pm_config.h
	@sed -e 's#<shhopt.h>#<pm_shhopt.h>#g' \
		${WRKSRC}/pbm/pm.h.new > ${WRKSRC}/pbm/pm.h
	@cp -f ${FILESDIR}/Makefile.config.OpenBSD \
		${WRKSRC}/Makefile.config
	@cd ${WRKSRC}/shhopt; ln -sf shhopt.h pm_shhopt.h

NO_REGRESS=		Yes

.if defined(PACKAGING) && ${SUBPACKAGE} == "-hpcd"
LIB_DEPENDS=		pbm.1,pgm.1,ppm.1::graphics/netpbm
.endif

.include <bsd.port.mk>

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
EXTRA_XAKE_FLAGS+=	NETPBMLIBTYPE=unixstatic
.else
EXTRA_XAKE_FLAGS+=	NETPBMLIBTYPE=unixshared
.endif
