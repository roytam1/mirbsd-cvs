# $MirOS$

COMMENT=		small and secure emacs-like editor
CATEGORIES=		editors
CVS_DISTREPO=		anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2007/03/09
CVS_DISTMODS=		src/usr.bin/mg
CVS_DISTFILE=		mg
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# PD; 2-clause UCB
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.if defined(CVS_DISTDATE)
OBSDVER=		${CVS_DISTDATE} (CVS)
.else
OBSDVER=		${CVS_DISTTAGS:S/OPENBSD_//:S/_/./}
.endif
SUBST_VARS+=		OBSDVER

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

pre-build:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} depend

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mg
	cd ${WRKSRC}; ${INSTALL_DATA} README tutorial ${PREFIX}/share/doc/mg/

.include <bsd.port.mk>
