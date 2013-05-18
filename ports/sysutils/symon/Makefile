# $OpenBSD: Makefile,v 1.12 2004/03/02 14:32:43 naddy Exp $

COMMENT=			active monitoring tool
VSN=			2.65
DASH_VER=		1
DISTNAME=		symon-${VSN}
PKGNAME=		symon-${VSN}-${DASH_VER}
CATEGORIES=		sysutils net

HOMEPAGE=		http://www.xs4all.nl/~wpd/symon/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/philes/

SUBPACKAGE?=

# client only package
MULTI_PACKAGES+=	-mon
COMMENT-mon=			active host monitor
MON_LIBDEPENDS=
# gatherer only package
MULTI_PACKAGES+=	-mux
COMMENT-mux=			symon data gatherer
MUX_LIBDEPENDS=		rrd:rrdtool-*:net/rrdtool

.for i in ${MULTI_PACKAGES}
FULLPKGNAME${i}=        symon${i}-${VSN}-${DASH_VER}
.endfor

.if defined(PACKAGING) && !empty(SUBPACKAGE)
MODULE_NAME=            ${SUBPACKAGE:S/-//g}
LIB_DEPENDS=            ${${MODULE_NAME:U}_LIBDEPENDS}
MESSAGE=                ${PKGDIR}/MESSAGE${SUBPACKAGE}
.else
LIB_DEPENDS=		rrd:rrdtool-*:net/rrdtool
.endif

WRKDIST=		${WRKDIR}/symon

NO_REGRESS=		Yes

.include <bsd.port.mk>
