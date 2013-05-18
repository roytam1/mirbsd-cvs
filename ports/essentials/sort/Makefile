# $MirOS: ports/essentials/sort/Makefile,v 1.3 2009/05/07 16:37:38 bsiegert Exp $

COMMENT=		MirOS sort(1)
CATEGORIES=		essentials
DISTNAME=		mirsort-20091122
HOMEPAGE=		http://mirbsd.de/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/sort/}

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRACT_SUFX=		.cpio.gz
WRKDIST=		${WRKDIR}/sort
EXTRA_FAKE_FLAGS=	BINDIR=${PREFIX}/bin MANDIR=${PREFIX}/man/cat

do-configure:
	@cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} obj

.include <bsd.port.mk>
