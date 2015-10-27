# $MirOS: ports/lang/expect/Makefile,v 1.7 2009/08/16 17:25:51 tg Exp $
# $OpenBSD: Makefile,v 1.42 2004/04/18 19:55:47 jolan Exp $

COMMENT=		sophisticated scripter based on Tcl/Tk
VSN=			5.43
_V=			${VSN:S/.//}
DISTNAME=		expect-${VSN}.0
CATEGORIES=		lang
#MASTER_SITES=		http://expect.nist.gov/old/ # now sourcefrog (5.45)
HOMEPAGE=		http://expect.nist.gov/

# PD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		tcl84::lang/tcl/8.4

FLAVOURS=		no_tk
FLAVOUR?=

SUBST_VARS+=		_V
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-tclconfig="${LOCALBASE}/lib/tcl8.4"\
			--with-tclinclude="${LOCALBASE}/include/tcl8.4"

.if !${FLAVOUR:L:Mno_tk}
USE_X11=		Yes
LIB_DEPENDS+=		tk84::x11/tk/8.4
CONFIGURE_ARGS+=	--with-tkconfig="${LOCALBASE}/lib/tk8.4" \
			--with-tkinclude="${LOCALBASE}/include/tk8.4"
.endif

REGRESS_TARGET=		test
DESTDIRNAME=		INSTALL_ROOT
WRKDIST=		${WRKDIR}/expect-${VSN}

.include <bsd.port.mk>
