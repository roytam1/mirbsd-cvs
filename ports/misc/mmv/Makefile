# $OpenBSD: Makefile,v 1.18 2003/09/23 15:29:41 sturm Exp $

COMMENT=			move/copy/append/link multiple files with wildcards

DISTNAME=	mmv
PKGNAME=	mmv-1.01b-0
CATEGORIES=	misc

MASTER_SITES=	ftp://gatekeeper.dec.com/pub/usenet/comp.sources.unix/volume21/mmv/
DISTFILES=	part01.Z part02.Z

MASTER_SITES0=	ftp://gatekeeper.dec.com/pub/usenet/comp.sources.unix/volume22/
PATCHFILES=	mmv.pch.Z:0

PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

DIST_SUBDIR=	${DISTNAME}
WRKDIST=	${WRKDIR}
EXTRACT_CASES=	*.Z) ${GZIP_CMD} -cd ${FULLDISTDIR}/$$archive | \
		sed '1,/^\#! \/bin\/sh/d' | sh ;;
PATCH_DIST_ARGS= -z ${DISTORIG} -d ${WRKSRC} --forward --quiet -E ${PATCH_DIST_STRIP} mmv.c

post-extract:
	@cd ${WRKSRC} && cat mmv.c.? >mmv.c && rm mmv.c.?

NO_REGRESS=	Yes

.include <bsd.port.mk>
