# $MirOS: ports/devel/ORBit0/Makefile,v 1.4 2006/09/14 00:08:00 tg Exp $
# $OpenBSD: Makefile,v 1.33 2002/11/21 02:33:59 margarida Exp $

COMMENT=			high-performance CORBA ORB with support for the C language

DISTNAME=	ORBit-0.5.13
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/ORBit/0.5/}

HOMEPAGE=	http://www.labs.redhat.com/orbit/

# workaround for a ld.so problem on alpha w/ orbit-idl
.if (${MACHINE_ARCH} == "alpha")
PATCH_LIST=		patch-* sup-alpha-*
.endif

MODULES=	devel/gettext
LIB_DEPENDS=	glib.1.2,gmodule.1.2::devel/glib1 \
		popt::devel/popt


# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes
CONFIGURE_STYLE= autoconf no-autoheader
MODGNU_RECURSE_DIRS=	${WRKSRC}/popt ${WRKSRC}/libIDL ${WRKSRC}
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static --disable-indent

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/orbit
	${INSTALL_DATA} ${FILESDIR}/orbitrc-sample \
	    ${PREFIX}/share/examples/orbit

.include <bsd.port.mk>
