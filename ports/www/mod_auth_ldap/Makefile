# $OpenBSD: Makefile,v 1.3 2003/05/22 14:16:22 naddy Exp $

# This port currently only works with archs supporting dynamic loading
# and has Apache that supports DSO's.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Apache LDAP authentication module

VERSION=	1.6.0
DISTNAME=	auth_ldap-${VERSION}
PKGNAME=	mod_auth_ldap-${VERSION}-0
CATEGORIES=	www

HOMEPAGE=	http://www.rudedog.org/auth_ldap/

MASTER_SITES=	${HOMEPAGE}


# Apache License, one unused function GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	ldap,lber::databases/openldap

NO_REGRESS=	Yes

CONFIGURE_STYLE=gnu

post-build:
	sed 's,!!PREFIX!!,${PREFIX},' \
		< ${FILESDIR}/mod_auth_ldap-enable \
		> ${WRKBUILD}/mod_auth_ldap-enable

do-install:
	${INSTALL_DATA} ${WRKBUILD}/auth_ldap.so ${PREFIX}/lib
	${INSTALL_SCRIPT} ${WRKBUILD}/mod_auth_ldap-enable ${PREFIX}/sbin

.include <bsd.port.mk>
