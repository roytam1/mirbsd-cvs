# $MirOS: ports/x11/evilwm/Makefile,v 1.10 2008/12/07 18:58:09 tg Exp $

COMMENT=		minimalist window manager for keyboard or mouse
CATEGORIES=		x11
VSN=			0.99.18
PKGNAME=		evilwm-${VSN}-${DASH_VER}
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
DASH_VER=		0
SUPDISTFILES+=		evilwm-${VSN}.tar.gz
.else
DISTNAME=		evilwm-${VSN}
DASH_VER=		0
MASTER_SITES=		http://www.6809.org.uk/evilwm/

MAKE_FLAGS+=		EVILVERSION=${VSN} X11LIBDIR=${X11BASE}/lib
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
