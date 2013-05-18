# $MirOS: ports/www/jakarta-tomcat/v3/Makefile,v 1.5 2006/09/14 00:14:38 tg Exp $
# $OpenBSD: Makefile,v 1.8 2003/11/27 20:11:06 sturm Exp $

# Requires a JVM
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Java servlet 2.2 and Java server pages 1.1 server
VSN=		3.2.4
DISTNAME=	jakarta-tomcat-${VSN}
CATEGORIES=	www
MASTER_SITES=	http://archive.apache.org/dist/jakarta/tomcat-3/archive/v${VSN}/bin/
EXTRACT_SUFX=	.zip
HOMEPAGE=	http://jakarta.apache.org/

JDK_VERSION=	1.3.1-linux
JAVA_HOME=	${LOCALBASE}/jdk${JDK_VERSION}
RUN_DEPENDS=	:jdk-linux->1.3:lang/jdk/1.3-linux

# Apache Software License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_BUILD=	Yes
NO_REGRESS=	Yes

WRKSRC=		${WRKDIR}/${DISTNAME}

DIRS=		bin conf doc lib logs src webapps
CONFDIR=	${SYSCONFDIR}/tomcat
TOMCATDIR=	/var/tomcat
SUBST_VARS=	TOMCATDIR CONFDIR

post-patch:
	@perl -pi -e 's|JAVA_HOME|${JAVA_HOME}|g' ${WRKSRC}/conf/workers.properties
	@perl -pi -e 's|TOMCATDIR|${TOMCATDIR}|g' ${WRKSRC}/bin/tomcat.sh
	@perl -pi -e 's|PREFIX|${PREFIX}|g' ${WRKSRC}/bin/tomcat.sh
	@perl -pi -e 's|SYSCONFDIR|${SYSCONFDIR}|g' ${WRKSRC}/bin/tomcat.sh
	@cd ${WRKDIST}/conf && perl -pi -e 's,^M,,g' *

do-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/tomcat
	@${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/tomcat
	@cd ${WRKDIST}/bin && chmod +x *.sh	# for .zip file
	@cd ${WRKDIST} && tar cf - ${DIRS} | (cd ${PREFIX}/tomcat && tar -xf -)
	@${INSTALL_DATA} ${FILESDIR}/README.OpenBSD ${PREFIX}/tomcat/conf

.include "bsd.port.mk"
