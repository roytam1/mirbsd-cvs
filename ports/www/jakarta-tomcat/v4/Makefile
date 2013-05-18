# $MirOS: ports/www/jakarta-tomcat/v4/Makefile,v 1.5 2006/09/14 00:14:38 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/01/03 13:36:03 sturm Exp $

# Requires a JVM
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Java servlet 2.3 and Java server pages 1.2 server
VSN=		4.1.29
DISTNAME=	jakarta-tomcat-${VSN}
CATEGORIES=	www
MASTER_SITES=	${MASTER_SITE_APACHE:=jakarta/tomcat-4/v${VSN}/bin/} \
		http://archive.apache.org/dist/jakarta/tomcat-4/archive/v${VSN}/bin/
HOMEPAGE=	http://jakarta.apache.org/

JDK_VERSION=	1.3.1-linux
JAVA_HOME=	${LOCALBASE}/jdk${JDK_VERSION}
BUILD_DEPENDS=	::archivers/gtar
RUN_DEPENDS=	:jdk-linux->1.3:lang/jdk/1.3-linux

# Apache Software License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

TAR=		${LOCALBASE}/bin/gtar

NO_BUILD=	Yes
NO_REGRESS=	Yes

CONFDIR=	${SYSCONFDIR}/tomcat
DIRS=		bin common conf server shared temp webapps work
DOCS=		LICENSE README.txt RELEASE-NOTES-4.1.txt RELEASE-PLAN-4.1.txt \
		RUNNING.txt
TOMCATDIR=	/var/tomcat
SUBST_VARS=	TOMCATDIR CONFDIR DISTNAME

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${DISTNAME}
	cd ${WRKDIST} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/${DISTNAME}
	cd ${WRKDIST} && \
		tar cf - ${DIRS} | (cd ${PREFIX}/${DISTNAME} && tar -xf -)
	@sed -e 's,y0y0y0,${TRUEPREFIX}/${DISTNAME},' \
		-e 's,y0y0y1,${SYSCONFDIR},' \
		< ${FILESDIR}/README.OpenBSD \
		> ${PREFIX}/${DISTNAME}/conf/README.OpenBSD
	@sed -e 's,y0y0y0,${TRUEPREFIX}/${DISTNAME},' \
		-e 's,y0y0y1,${JAVA_HOME},' \
		< ${FILESDIR}/tomcat.rc > ${PREFIX}/${DISTNAME}/conf/tomcat.rc
	@perl -pi -e 's,y0y0y0,${SYSCONFDIR},' \
		${PREFIX}/${DISTNAME}/bin/setclasspath.sh

.include "bsd.port.mk"
