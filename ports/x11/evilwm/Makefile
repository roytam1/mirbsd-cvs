# $MirOS: ports/x11/evilwm/Makefile,v 1.9 2008/11/08 23:04:11 tg Exp $

COMMENT=		minimalist window manager for keyboard or mouse
CATEGORIES=		x11
V=			0.99.18
PKGNAME=		evilwm-${V}-${PL}
HOMEPAGE=		http://www.6809.org.uk/evilwm/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# BSD-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVOURS=		miros oldmove
FLAVOUR?=		miros

.if ${FLAVOUR:Mmiros}
FLAVOUR=		miros
MCZ_FETCH=		Yes
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

.if ${FLAVOUR:Moldmove}
CPPFLAGS+=		-DOLD_MOVE_BEHAVIOUR
.endif

.if !${FLAVOUR:Mmiros}
post-extract:
	@cp ${FILESDIR}/Makefile ${WRKSRC}/
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/evilwm
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/evilwm/

.include <bsd.port.mk>
