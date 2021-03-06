# $MirOS: ports/x11/aterm/Makefile,v 1.4 2007/05/07 19:39:06 bsiegert Exp $
# $OpenBSD: Makefile,v 1.33 2004/04/09 04:24:44 jolan Exp $

COMMENT=	color vt102 terminal emulator with transparency support
DISTNAME=	aterm-0.4.2
CATEGORIES=	x11

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

HOMEPAGE=	http://aterm.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=aterm/}

USE_X11=	Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--enable-xgetdefault --enable-ttygid --enable-utmp

FLAVOURS=	big5 lite
FLAVOUR?=

.if ${FLAVOUR:L:Mbig5}
PERMIT_PACKAGE_CDROM=	dependency chinese/taipeifonts is not allowed for CDROM
PERMIT_PACKAGE_FTP=	dependency chinese/taipeifonts is not allowed for FTP
RUN_DEPENDS=	${LOCALBASE}/lib/X11/fonts/chinese/taipei16.pcf.gz::chinese/taipeifonts
PATCH_LIST=	patch-src_Makefile_in \
		patch-src_command_c

CONFIGURE_ARGS+= --enable-big5

post-patch:
	@cd ${FILESDIR}; cp -f {cli_xcin.c,protocol.h,state.h} \
		${WRKSRC}/src
.else
PATCH_LIST=
.endif

.if ${FLAVOUR:L:Mlite}
CONFIGURE_ARGS+= --without-xpm --disable-transparency \
		--disable-background-image --disable-fading \
		--without-jpeg --without-png
.else
LIB_DEPENDS=	jpeg.62::graphics/jpeg \
		png.2::graphics/png

CONFIGURE_ARGS+= --with-xpm --enable-transparency \
		--enable-background-image --enable-fading \
		--with-jpeg --with-png
.endif

NO_REGRESS=	Yes

.include <bsd.port.mk>
