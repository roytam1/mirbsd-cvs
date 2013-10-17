# $MirOS$

COMMENT=		decode morse from a PCM WAV file
CATEGORIES=		audio
DISTNAME=		morse2ascii-0.2
DISTFILES=		morse2ascii.zip
DIST_SUBDIR=		${DISTNAME}
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://aluigi.altervista.org/mytoolz.htm

# GPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://aluigi.altervista.org/mytoolz/
CONFIGURE_STYLE=	bmake

do-extract:
	@mkdir -p ${WRKDIST}
	@PATH=${PORTPATH}; set -e; cd ${WRKDIST}; \
	for archive in ${EXTRACT_ONLY}; do \
		${UNZIP} -q ${FULLDISTDIR}/$$archive -d ${WRKDIST}; \
	done
	cp ${FILESDIR}/Makefile ${WRKDIST}/

.include <bsd.port.mk>
