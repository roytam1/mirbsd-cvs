# $MirOS: ports/x11/evilwm/Makefile,v 1.4 2005/12/18 03:37:16 tg Exp $

NOT_FOR_PLATFORM=	MirBSD:8:*

COMMENT=			minimalist window manager for keyboard or mouse
CATEGORIES=		x11
V=			0.99.17
DISTNAME=		evilwm_${V}.orig
PKGNAME=		evilwm-${V}-1
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=evilwm/}
HOMEPAGE=		http://evilwm.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# BSD-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		unpatched miros
FLAVOR?=		miros

.if ${FLAVOR:L:Munpatched}
PATCH_LIST=
.endif

.if ${FLAVOR:L:Mmiros}
.  if ${FLAVOR:L} != "miros"
ERRORS+=		"Fatal: miros flavour is not combining"
.  endif
CPPFLAGS+=		-DOLD_MOVE_BEHAVIOUR
.endif

WRKDIST=		${WRKDIR}/evilwm-${V}.orig
MAKE_FLAGS+=		EVILVERSION=${V} X11LIBDIR=${X11BASE}/lib
USE_X11=		Yes
CPPFLAGS+=		-I${X11BASE}/include

post-extract:
	@cp ${FILESDIR}/Makefile ${WRKSRC}/

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/evilwm
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/evilwm/

.include <bsd.port.mk>
