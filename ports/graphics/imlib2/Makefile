# $MirOS: ports/graphics/imlib2/Makefile,v 1.8 2008/03/09 17:22:51 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/04/18 02:01:25 jolan Exp $

COMMENT=		image manipulation library
DISTNAME=		imlib2-1.4.0
CATEGORIES=		graphics
HOMEPAGE=		http://www.enlightenment.org/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=enlightenment/}

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_cxx
FLAVOUR?=

USE_X11=		Yes
MODULES+=		devel/pkgconfig graphics/png
LIB_DEPENDS+=		tiff::graphics/tiff
LIB_DEPENDS+=		bz2::archivers/bzip2
LIB_DEPENDS+=		id3tag::audio/libid3tag

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <mirports.sys.mk>

.if ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--enable-mmx
.endif

.if ${FLAVOUR:L:Mno_cxx}
CONFIGURE_ARGS+=	--without-gif
.else
LIB_DEPENDS+=		ungif::graphics/libungif
USE_CXX=		Yes
CONFIGURE_ARGS+=	--with-gif=libungif
.  if ${NO_SHARED_LIBS:L} != "no"
ERRORS+=		"Fatal: Must use no_cxx flavour if no shared libs."
.  endif
.endif

post-extract:
	cp ${FILESDIR}/round.c ${WRKSRC}/src/lib/

.include <bsd.port.mk>
