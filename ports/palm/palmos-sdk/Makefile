# $MirOS: ports/palm/palmos-sdk/Makefile,v 1.4 2007/03/31 22:02:07 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/10/28 02:13:21 naddy Exp $

BROKEN=			unfetchable distfiles

COMMENT=		PalmOS include files

VERSION=	4.0
DISTNAME=	sdk40
PKGNAME=	palmos-sdk-${VERSION}-0
CATEGORIES=	palm devel

HOMEPAGE=	http://www.palmos.com/dev/tools/

IS_INTERACTIVE=	Yes


PERMIT_PACKAGE_CDROM=   "no redistribution"
PERMIT_PACKAGE_FTP=     "no redistribution"
PERMIT_DISTFILES_CDROM= "no redistribution"
PERMIT_DISTFILES_FTP=   "no redistribution"

MASTER_SITES=	http://www.palmos.com/cgi-bin/sdk40.cgi/
FETCH_CMD=	${LOCALBASE}/bin/curl -O -b sdk40_license=I-agree
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} \
		sdk40upd1${EXTRACT_SUFX}

FETCH_DEPENDS=	:curl-*:net/curl
BUILD_DEPENDS=	:rpm2cpio-*|rpm-*:converters/rpm2cpio

PALMDEV=	${PREFIX}/palm
NO_BUILD=	Yes
NO_REGRESS=	Yes
SUBST_VARS=	VERSION

.include <mirports.sys.mk>

ACCEPT_PALMOS_SDK_LICENSE?=No
.if ${ACCEPT_PALMOS_SDK_LICENSE:L} == "no"
do-fetch:
	@echo "You must read http://www.palmos.com/dev/tech/tools/sdk35.cgi first."
	@echo "To accept the license, restart the build with"
	@echo "ACCEPT_PALMOS_SDK_LICENSE=Yes"
	@exit 1
.endif

post-extract:
	@cd ${WRKDIR} && \
	${LOCALBASE}/bin/rpm2cpio ./palmos-sdk-${VERSION}-1.noarch.rpm | cpio -i -d && \
	ln -s ./opt/palmdev/sdk-4/ ./sdk-${VERSION}

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/palmos-sdk
	${INSTALL_DATA} ${FILESDIR}/palmos-sdk-license ${PREFIX}/share/doc/palmos-sdk
	${INSTALL_DATA_DIR} ${PALMDEV}/sdk-${VERSION}
	${INSTALL_DATA_DIR} ${PALMDEV}/sdk-${VERSION}/include
	${INSTALL_DATA_DIR} ${PALMDEV}/sdk-${VERSION}/lib
	@cd ${WRKDIR}/sdk-${VERSION} && pax -rw include ${PALMDEV}/sdk-${VERSION}
	@cd ${WRKDIR}/sdk-${VERSION} && pax -rw . ${PALMDEV}/sdk-${VERSION}/lib
	@cd ${PALMDEV} && ln -sf sdk-${VERSION} sdk

.include <bsd.port.mk>
