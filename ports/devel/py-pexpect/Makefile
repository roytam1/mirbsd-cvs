# $MirOS: ports/devel/py-pexpect/Makefile,v 1.4 2008/08/12 08:32:03 tg Exp $
# $OpenBSD: Makefile,v 1.9 2007/10/08 08:22:40 steven Exp $

COMMENT=		pure Python Expect-like module
MODPY_EGG_VERSION=	2.3
DISTNAME=		pexpect-${MODPY_EGG_VERSION}
PKGNAME=		py-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://pexpect.sourceforge.net/

# Python
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=pexpect/}

MODULES=		lang/python

EXAMPLESDIR=		${PREFIX}/share/examples/py-pexpect
DOCDIR=			${PREFIX}/share/doc/py-pexpect

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/{ANSI,FSM,screen}.py ${EXAMPLESDIR}/
	${INSTALL_DATA} ${WRKSRC}/examples/* ${EXAMPLESDIR}/
	${INSTALL_DATA} ${WRKSRC}/doc/* ${DOCDIR}/

.include <bsd.port.mk>
