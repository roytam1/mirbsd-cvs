# $MirOS: ports/security/ccrypt/Makefile,v 1.2 2005/03/25 23:14:03 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/03/31 06:08:36 kevlo Exp $

COMMENT=			encrypt and decrypt AES files and streams

DISTNAME=	ccrypt-1.7
CATEGORIES=	security

HOMEPAGE=	http://quasar.mathstat.uottawa.ca/~selinger/ccrypt/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}/download/ \
		${MASTER_SITE_SOURCEFORGE:=ccrypt/}

CONFIGURE_STYLE= gnu

FLAVORS=	emacs
FLAVOR?=

.if ${FLAVOR:L:Memacs21}
BUILD_DEPENDS=	:emacs-21.*:editors/emacs
.endif

.include <bsd.port.mk>
