# $MirOS$

COMMENT=		"estimate randomness of sample data"
CATEGORIES=		math security
DISTNAME=		ent-19981020
DISTFILES=		random.zip
DIST_SUBDIR=		${DISTNAME}
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
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
