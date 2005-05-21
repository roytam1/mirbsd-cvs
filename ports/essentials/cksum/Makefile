# $MirOS: ports/essentials/cksum/Makefile,v 1.2 2005/04/12 21:10:57 tg Exp $

# only works with portable MirMake
NOT_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

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

.include <mirports.sys.mk>

.if ${OBJECT_FMT} == "PE"
MAKE_ENV+=		AFLAGS=-DUNDERSCORES
.endif

post-extract:
	cp ${FILESDIR}/[!C]* ${WRKSRC}/

do-configure:
	@cd ${WRKBUILD} && exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} obj

.include <bsd.port.mk>
