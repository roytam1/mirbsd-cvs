# $MirOS: ports/shells/tcsh/Makefile,v 1.1.7.1 2005/03/18 15:51:57 tg Exp $

COMMENT=			C shell with file name completion and command line editing
DISTNAME=	tcsh-6.13.00
CATEGORIES=	shells
HOMEPAGE=	http://www.tcsh.org
RESPONSIBLE=	Stephen Paskaluk <sap@66h.42h.de>

# BSD licensed
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.astron.com/pub/tcsh/

FLAVORS=	static
FLAVOR?=

CONFIGURE_STYLE=gnu

.if ${FLAVOR:L} == "static"
LDSTATIC=	-static
.endif

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/tcsh ${PREFIX}/bin/tcsh
	${INSTALL_MAN} ${WRKSRC}/tcsh.man ${PREFIX}/man/man1/tcsh.1

.include <bsd.port.mk>
