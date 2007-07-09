# $MirOS$

COMMENT=		network traffic analyser
CATEGORIES=		security sysutils
CVS_DISTREPO=		anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2005/07/21 18:00
CVS_DISTMODS=		src/usr.sbin/tcpdump src/sbin/pfctl src/sys/net
CVS_DISTFILE=		tcpdump
WRKDIST=		${WRKDIR}/src/usr.sbin/tcpdump

# BSD
PERMIT_DISTFILES_CDROM=	"Not in Germany according to Article 202c, penal code"
PERMIT_DISTFILES_FTP=	"Not in Germany according to Article 202c, penal code"
PERMIT_PACKAGE_CDROM=	"Not in Germany according to Article 202c, penal code"
PERMIT_PACKAGE_FTP=	"Not in Germany according to Article 202c, penal code"

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

pre-build:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} depend

.include <bsd.port.mk>
