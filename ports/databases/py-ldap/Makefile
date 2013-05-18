# $MirOS: ports/databases/py-ldap/Makefile,v 1.5 2007/03/31 22:01:55 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/02/17 20:47:45 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			LDAP client API for Python
VERSION=	2.0.0pre19
DISTNAME=	python-ldap-${VERSION}
PKGNAME=	py-ldap-${VERSION}-0
CATEGORIES=	databases
HOMEPAGE=	http://python-ldap.sourceforge.net/

# Python
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=python-ldap/}

FLAVOURS=	p2.3
FLAVOUR?=	p2.3

MODULES=	lang/python

#.if ${FLAVOUR} == "p2.1" || ${FLAVOUR} == "p2.2" || ${FLAVOUR} == "p2.3"
.if ${FLAVOUR} == "p2.3"
MODPY_VERSION=	${FLAVOUR:S/p//}
.else
ERRORS+=	"Fatal: Conflicting flavour: ${FLAVOUR}"
.endif

LIB_DEPENDS=	ldap,lber::databases/openldap

EXAMPLESDIR=	${PREFIX}/share/examples/py-ldap

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	cd ${WRKSRC}; tar cf - Demo | tar xf - -C ${EXAMPLESDIR}

do-regress: fake
	@cd ${WRKSRC}/Tests/Lib && ${MAKE_ENV} \
		PYTHONPATH=${WRKINST}${MODPY_SITEPKG} \
		${MODPY_BIN} ./test_ldapurl.py 

.include <bsd.port.mk>
