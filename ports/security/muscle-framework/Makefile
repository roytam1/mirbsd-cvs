# $MirOS: ports/security/muscle-framework/Makefile,v 1.3 2005/07/07 21:25:52 bsiegert Exp $

COMMENT=			Smartcard access framework
DISTNAME=		muscleframework-1.1.5
PKGNAME=		${DISTNAME}-1
CATEGORIES=		security
MASTER_SITES=		http://alioth.debian.org/download.php/463/
HOMEPAGE=		http://www.linuxnet.com/musclecard/index.html

# 3-clause and 4-clause UCB licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
LIB_DEPENDS+=		musclecard.0::security/pcsc-lite

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}/CFlexPlugin ${WRKSRC}/MCardPlugin \
			${WRKSRC}/libmusclepkcs11
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		yes

.include <bsd.own.mk>
CFLAGS+=		-pthread
LDFLAGS+=		-pthread

post-extract:
	cp ${FILESDIR}/configure ${FILESDIR}/Makefile ${WRKSRC}/

.include <bsd.port.mk>
