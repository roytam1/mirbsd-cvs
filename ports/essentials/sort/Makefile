# $MirOS: ports/essentials/cksum/Makefile,v 1.2 2005/04/12 21:10:57 tg Exp $

COMMENT=		"MirOS sort(1)"
CATEGORIES=		essentials
DISTNAME=		mirsort-20050418
HOMEPAGE=		http://mirbsd.de/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD}

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/sort
EXTRA_FAKE_FLAGS=	BINDIR=${PREFIX}/bin MANDIR=${PREFIX}/man/cat

do-configure:
	@cd ${WRKBUILD} && exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} obj

.include <bsd.port.mk>
