# $MirOS: ports/mailnews/sylpheed/Makefile,v 1.5 2007/04/12 20:24:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.48 2004/04/10 19:13:50 couderc Exp $

COMMENT=		mail/news client in gtk+

VERSION=		2.2.4
DISTNAME=		sylpheed-${VERSION}
CATEGORIES=    		mailnews x11
HOMEPAGE=		http://sylpheed.good-day.net


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/sylpheed/v2.2/
EXTRACT_SUFX=		.tar.bz2
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODULES+=		devel/pkgconfig converters/libiconv

FLAVOURS=	compface gpgme ldap
FLAVOUR?=

.if ${FLAVOUR:L:Mcompface}
PERMIT_PACKAGE_CDROM=	"No Fee"
PERMIT_DISTFILES_CDROM=	"No Fee"
LIB_DEPENDS+=		compface.1::mail/faces
.else
CONFIGURE_ARGS+=	--disable-compface
.endif

.if ${FLAVOUR:L:Mgpgme}
PERMIT_PACKAGE_CDROM=	dependency security/gnupg is not allowed for CDROM
LIB_DEPENDS+=		gpgme.4::security/gpgme
CONFIGURE_ARGS+=	--enable-gpgme
.else
CONFIGURE_ARGS+=	--disable-gpgme
.endif

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=		ldap.2,lber.2::databases/openldap
CONFIGURE_ARGS+=	--enable-ldap
.else
CONFIGURE_ARGS+=	--disable-ldap
.endif

.include <bsd.port.mk>
