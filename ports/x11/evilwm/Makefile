# $MirOS$

COMMENT=		minimalist window manager for keyboard or mouse
CATEGORIES=		x11
V=			0.99.18
PKGNAME=		evilwm-${V}-${PL}
HOMEPAGE=		http://www.6809.org.uk/evilwm/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# BSD-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		miros oldmove
FLAVOR?=		miros

.if ${FLAVOR:Mmiros}
FLAVOR=			miros
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2006/10/27
CVS_DISTMODS=		X11/extras/evilwm
CVS_DISTFILE=		mirvilwm
PL=			0
SUPDISTFILES+=		evilwm-${V}.tar.gz
.else
DISTNAME=		evilwm-${V}
PL=			0
MASTER_SITES=		http://www.6809.org.uk/evilwm/

MAKE_FLAGS+=		EVILVERSION=${V} X11LIBDIR=${X11BASE}/lib
SUPDISTFILES+=		mirvilwm-20061027.mcz
.endif

USE_X11=		Yes

.if ${FLAVOR:Moldmove}
CPPFLAGS+=		-DOLD_MOVE_BEHAVIOUR
.endif

.if !${FLAVOR:Mmiros}
post-extract:
	@cp ${FILESDIR}/Makefile ${WRKSRC}/
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/evilwm
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/evilwm/

.include <bsd.port.mk>
