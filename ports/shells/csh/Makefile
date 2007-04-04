# $MirOS$

COMMENT=		BSD ‘C’ Shell
CATEGORIES=		shells devel
CVS_DISTREPO=		anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2007/04/04
CVS_DISTMODS=		src/bin/csh
CVS_DISTFILE=		csh
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CPPFLAGS+=		-DNOSTRCOLL

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/usd/04.csh

.include <bsd.port.mk>
