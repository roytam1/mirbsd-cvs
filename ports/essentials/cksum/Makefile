# $MirOS: ports/editors/joe/Makefile,v 1.1.7.1 2005/03/18 15:45:43 tg Exp $

# only works with portable MirMake
NOT_FOR_OS=		MirBSD:*:* OpenBSD:*:*

COMMENT=		"MirOS cksum(1)"
CATEGORIES=		essentials
DISTNAME=		mircksum-20050412
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://wiki.mirbsd.de/MirCksum
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
MASTER_SITES=		${_MASTER_SITE_MIRBSD}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/md5
CPPFLAGS+=		-isystem ${.SYSMK}
EXTRA_XAKE_FLAGS=	LDADD="-L${.SYSMK} -lhash"
EXTRA_FAKE_FLAGS=	BINDIR=${PREFIX}/bin MANDIR=${PREFIX}/man/cat

do-configure:
	@cd ${WRKBUILD} && exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} obj

.include <bsd.port.mk>
