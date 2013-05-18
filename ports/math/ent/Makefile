# $MirOS: ports/math/ent/Makefile,v 1.7 2010/09/21 21:23:54 tg Exp $

COMMENT=		estimate randomness of sample data
CATEGORIES=		math security
DISTNAME=		ent-19981020
DASH_VER=		4
DISTFILES=		random.zip
DIST_SUBDIR=		${DISTNAME}
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://fourmilab.ch/random/
MASTER_SITES=		${HOMEPAGE}

# public domain
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

do-extract:
	@mkdir -p ${WRKDIST}
	@PATH=${PORTPATH}; set -e; cd ${WRKDIST}; \
	for archive in ${EXTRACT_ONLY}; do \
		${UNZIP} -q ${FULLDISTDIR}/$$archive -d ${WRKDIST}; \
	done
	cp ${FILESDIR}/Makefile ${WRKDIST}/

.include <bsd.port.mk>
