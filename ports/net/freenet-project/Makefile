# $MirOS: ports/net/freenet-project/Makefile,v 1.4 2006/01/01 05:25:29 tg Exp $

COMMENT=			fully anonymous distributed storage system
VERSION=	0.5.2-rc2
# If you want an update, make sunjdk-1.4.1 work first ;-)
PKGNAME=	freenet-${VERSION:S/-/./}-0
EXTRACT_SUFX=	.jar
CATEGORIES=	net
HOMEPAGE=	http://www.freenetproject.org/
MASTER_SITES=	${HOMEPAGE}snapshots/
RESPONSIBLE=	Thorsten Glaser <tg@66h.42h.de>

DISTFILES=	freenet-${VERSION}.jar freenet-ext.jar
SCRIPTS=	configure run j update.sh
FILES=		freenet.conf.in seednodes.ref

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

#RUN_DEPENDS+=	::devel/jdk/1.3-linux
#RUN_DEPENDS+=	::sysutils/daemontools

NO_BUILD=	Yes
NO_REGRESS=	Yes

do-extract:

TDIR=${PREFIX}/freenet-project/

do-install:
	${INSTALL_DATA_DIR} ${TDIR} ${TDIR}env ${TDIR}node \
	    ${TDIR}route ${TDIR}stats ${TDIR}store
.for i in ${SCRIPTS}
	${INSTALL_SCRIPT} ${FILESDIR}/$i ${TDIR}
.endfor
.for i in ${FILES}
	${INSTALL_DATA} ${FILESDIR}/$i ${TDIR}node/
.endfor
.for i in ${DISTFILES}
	${INSTALL_DATA} ${FULLDISTDIR}/$i ${TDIR}node/
.endfor
	mv ${TDIR}node/freenet-${VERSION}.jar ${TDIR}node/freenet.jar
	chmod 444 ${TDIR}node/*.in ${TDIR}node/*.jar
	chmod 744 ${TDIR}configure
	touch ${TDIR}down

.include <bsd.port.mk>
