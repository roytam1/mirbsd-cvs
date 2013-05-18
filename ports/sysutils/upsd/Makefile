# $MirOS$
# $OpenBSD: Makefile,v 1.13 2002/08/05 02:25:28 kevlo Exp $

COMMENT=	APC Smart UPS Monitoring Daemon
DISTNAME=	upsd-2.0.1.6
CATEGORIES=	sysutils
MASTER_SITES=	${MASTER_SITE_LOCAL}


PERMIT_PACKAGE_CDROM=	"missing license"
PERMIT_PACKAGE_FTP=	"missing license"
PERMIT_DISTFILES_CDROM=	"missing license"
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/upsd-2.0

pre-build:
	@perl -pi -e 's:%%SYSCONFDIR%%:${SYSCONFDIR}:' \
		${WRKSRC}/config.h
	@mv ${WRKSRC}/config.h ${WRKSRC}/conf.h.orig
	@sed -e "s!@prefix@!${PREFIX}!g" ${WRKSRC}/conf.h.orig > ${WRKSRC}/conf.h

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/upsd ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/upsd
	${INSTALL_DATA} ${WRKSRC}/sample/upsd.conf ${PREFIX}/share/examples/upsd/upsd.conf-sample

.include <bsd.port.mk>
