# $MirOS: ports/devel/mico/Makefile,v 1.7 2008/08/12 15:23:51 tg Exp $
# $OpenBSD: Makefile,v 1.4 2002/10/25 22:37:52 naddy Exp $

COMMENT=		free and complete CORBA-compliant implementation
DISTNAME=		mico-2.3.12
DASH_VER=		1
CATEGORIES=		devel
HOMEPAGE=		http://www.mico.org/
MASTER_SITES=		${HOMEPAGE}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf

FAKE_FLAGS=		prefix=${WRKINST:Q}${PREFIX:Q}
WRKDIST=        	${WRKDIR}/mico
NO_REGRESS=		Yes

FLAVOURS=		gtk tcl
FLAVOUR?=

CONFIGURE_ARGS+=	--with-ssl

.if ${FLAVOUR:L:Mgtk}
.  error PFRAG.gtk probably needed
LIB_DEPENDS+=		gtk.1.2::x11/gtk+
CONFIGURE_ARGS+=	--with-gtk
USE_X11=		Yes
.else
CONFIGURE_ARGS+=	--without-x
.endif

.if ${FLAVOUR:L:Mtcl}
LIB_DEPENDS+=		tcl.8::lang/tcl
CONFIGURE_ARGS+=	--with-tcl
USE_X11=		Yes
.endif

post-install:
	cd ${PREFIX}/doc; pax -rwl -pe . ${PREFIX}/share/doc/
	rm -rf ${PREFIX}/doc

.include <bsd.port.mk>
