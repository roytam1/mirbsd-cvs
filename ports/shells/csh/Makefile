# $MirOS: ports/shells/csh/Makefile,v 1.2 2008/05/25 20:56:39 tg Exp $

COMMENT=		BSD ‘C’ Shell
CATEGORIES=		shells devel
MCZ_FETCH=		Yes
CVS_DISTREPO=		:ext:anoncvs@anoncvs.ca.openbsd.org:/cvs
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
