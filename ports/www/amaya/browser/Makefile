# $MirOS: ports/www/amaya/browser/Makefile,v 1.8 2008/04/07 19:20:06 tg Exp $
# $OpenBSD: Makefile,v 1.11 2003/12/20 01:17:43 espie Exp $
#
# Many variables moved to ../Makefile.inc

COMMENT=		test-bed browser/authoring tool of the W3C

AMAYA_VERSION=		5.1
DISTNAME=		amaya-src-${AMAYA_VERSION}
PKGNAME=		amaya-${AMAYA_VERSION}-1

HOMEPAGE=		http://www.w3.org/Amaya/

FLAVOURS=		motif gtk
FLAVOUR?=		motif

MODULES+=		textproc/expat

.if ${FLAVOUR:Mopenmotif} || ${FLAVOUR:Mlesstif}
FLAVOUR+=		motif
.endif

.if ${FLAVOUR:L} == "gtk"

CONFIGURE_ARGS+=	--with-gtk=${LOCALBASE}
# I'm too lazy to write a proper imlib autoconf test.
LIB_DEPENDS+=		gdk_imlib.19::graphics/imlib

.elif ${FLAVOUR:Mmotif}

USE_MOTIF=		any
LIB_DEPENDS+=		jpeg.62::graphics/jpeg
MODULES+=		graphics/png
CONFIGURE_ARGS+=	--without-gtk \
			--with-motif-includes=${LOCALBASE}/include \
			--with-motif-libraries=${LOCALBASE}/lib

.else
ERRORS+=		"Fatal: Conflicting or missing flavour: '${FLAVOUR}'"
.endif

WRKSRC=			${WRKDIR}/Amaya
WRKBUILD=		${WRKDIR}/Amaya/obj
WRKDIST=		${WRKDIR}

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf dest
MODGNU_RECURSE_DIRS=	${WRKSRC}/../libwww/config ${WRKSRC}
CONFIGURE_SCRIPT=	../configure
CONFIGURE_ARGS+=	--without-graphic-libs

# We need to regenerate configure in two places, Amaya/ and libwww/
AUTOCONF_DIR=		${WRKSRC}
post-patch:
	@cd ${WRKDIST}/libwww && exec ${SETENV} \
		${AUTOCONF_ENV} ${AUTOCONF}

post-configure:
	@cd ${WRKBUILD} && cp Options.orig Options

NO_REGRESS=		Yes

pre-install:
	${STRIP} ${WRKBUILD}/bin/amaya
	${STRIP} ${WRKBUILD}/bin/print

post-install:
	cd ${PREFIX}/bin; rm amaya; \
		ln -s ${TRUEPREFIX}/Amaya/applis/bin/amaya

.include <bsd.port.mk>
