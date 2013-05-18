# $MirOS: ports/print/gimp-print/Makefile,v 1.2 2005/07/07 21:25:32 bsiegert Exp $

BROKEN=		incomplete port

COMMENT=			GIMP Printing System
V=		5.0.0-alpha3
DISTNAME=	gimp-print-${V}
EXTRACT_SUFX=	.tar.bz2
PKGNAME=	gimp-print-${V:S/-//g}-0
CATEGORIES=	print graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gimp-print/}
HOMEPAGE=	http://gimp-print.sourceforge.net/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-dependency-tracking --with-gnu-ld \
			--without-foomatic --without-foomatic3

FLAVORS=		cups gs gimp1 gimp2
FLAVOR?=		gs

.if empty(FLAVOR)
ERRORS+=		"Fatal: must choose an operating mode flavour."
.endif

.if ${FLAVOR:L:Mcups}
CONFIGURE_ARGS+=	--with-cups
GP_DEPENDS+=		:cups-*:print/cups
ERRORS+=		"Fatal: CUPS not tested."
.else
CONFIGURE_ARGS+=	--without-cups
.endif

.if ${FLAVOR:L:Mgs}
CONFIGURE_ARGS+=	--with-ghostscript
GP_DEPENDS+=		:ghostscript-*:print/ghostscript/gnu,a4
BROKEN=			Ghostscript does not build IJS tools
.else
CONFIGURE_ARGS+=	--without-ghostscript
.endif

.if ${FLAVOR:L:Mgimp1}
CONFIGURE_ARGS+=	--with-gimp
GP_DEPENDS+=		:gimp-1.*:graphics/gimp/stable
ERRORS+=		"Fatal: GIMP not tested."
.else
CONFIGURE_ARGS+=	--without-gimp --without-libgimpprintui
.endif

.if ${FLAVOR:L:Mgimp2}
CONFIGURE_ARGS+=	--with-gimp2
ERRORS+=		"Fatal: No GIMP2 port!"
ERRORS+=		"Fatal: GIMP not tested."
.else
CONFIGURE_ARGS+=	--without-gimp2
.endif

BUILD_DEPENDS+=		${GP_DEPENDS}
RUN_DEPENDS+=		${GP_DEPENDS}

.include <bsd.port.mk>
