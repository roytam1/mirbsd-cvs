# $OpenBSD: Makefile,v 1.4 2002/10/25 22:37:52 naddy Exp $

COMMENT=		free and complete CORBA-compliant implementation
DISTNAME=		mico-2.3.6
CATEGORIES=		devel
HOMEPAGE=		http://www.mico.org/
MASTER_SITES=		${HOMEPAGE}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu

MODGNU_RECURSE_DIRS=	${WRKSRC}/admin ${WRKSRC}

FAKE_FLAGS=		prefix="${WRKINST}${PREFIX}"
WRKDIST=        	${WRKDIR}/mico
NO_REGRESS=		Yes

FLAVOURS=		ssl gtk tcl
FLAVOUR?=

.if ${FLAVOUR:L:Mssl}
CONFIGURE_ARGS+=	--with-ssl
.endif

.if ${FLAVOUR:L:Mgtk}
LIB_DEPENDS+=		gtk.1.2::x11/gtk+
CONFIGURE_ARGS+=	--with-gtk
USE_X11=		Yes
.endif

.if ${FLAVOUR:L:Mtcl}
LIB_DEPENDS+=		tcl.8::lang/tcl
CONFIGURE_ARGS+=	--with-tcl
USE_X11=		Yes
.endif

.include <bsd.port.mk>
