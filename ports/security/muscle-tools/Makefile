# $MirOS: ports/security/muscle-tools/Makefile,v 1.2 2005/04/10 21:50:55 tg Exp $

COMMENT=			Smartcard access tools
DISTNAME=		muscleTools-0.9.2
CATEGORIES=		security
MASTER_SITES=		http://alioth.debian.org/download.php/395/
HOMEPAGE=		http://www.linuxnet.com/musclecard/index.html

# 3-clause UCB licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
BUILD_DEPENDS+=		:muscleframework->=1.1:security/muscle-framework
RUN_DEPENDS+=		:muscleframework->=1.1:security/muscle-framework
LIB_DEPENDS+=		musclecard.0::security/pcsc-lite

.include <bsd.own.mk>
CFLAGS+=		-pthread

.include <bsd.port.mk>
