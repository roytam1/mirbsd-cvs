# $OpenBSD: Makefile,v 1.28 2003/09/22 22:53:36 pvalchev Exp $

COMMENT=			u-law to gsm encoding audio converter and library

DISTNAME=	gsm-1.0.10
CATEGORIES=	audio
MASTER_SITES=	ftp://ftp.cs.tu-berlin.de/pub/local/kbs/tubmik/gsm/

# Missing redistribution terms in license
PERMIT_PACKAGE_CDROM=	"no redistribution"
PERMIT_PACKAGE_FTP=	"no redistribution"
PERMIT_DISTFILES_CDROM=	"no redistribution"
PERMIT_DISTFILES_FTP=	"no redistribution"

EXTRA_XAKE_FLAGS=	DEBUG="${CFLAGS}" LDINC='-L$$(LIB)'
EXTRA_FAKE_FLAGS=	INSTALL_ROOT="${WRKINST}${PREFIX}"

WRKDIST=	${WRKDIR}/gsm-1.0-pl10
NO_REGRESS=	Yes

.include <bsd.port.mk>

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
MAKE_ENV+=	NO_SHARED_LIBS=Yes
.endif
