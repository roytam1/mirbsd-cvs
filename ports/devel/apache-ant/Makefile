# $MirOS: ports/devel/apache-ant/Makefile,v 1.4 2005/04/11 15:54:54 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/01/03 13:40:03 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			java equivalent to make

DISTNAME=	apache-ant-1.6.0
CATEGORIES=	devel

HOMEPAGE=	http://ant.apache.org/


# Apache Software License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_APACHE:=ant/binaries/} \
		http://archive.apache.org/dist/ant/binaries/

EXTRACT_SUFX=	-bin.tar.gz

BUILD_DEPENDS=	::archivers/gtar
RUN_DEPENDS=	:jdk*->=1.2:lang/jdk/1.3-linux

NO_BUILD=	Yes
NO_REGRESS=	Yes

TAR=		${LOCALBASE}/bin/gtar

ANTDOCS=	${PREFIX}/share/doc/java/ant
TXT=		README WHATSNEW LICENSE

do-install:
	@cd ${WRKDIST}/bin; \
	    perl -pi -e 's|_anthome_|${TRUEPREFIX}/bin|;' \
		-e 's|_antlibs_|${TRUEPREFIX}/lib/java/ant|;' ant runant.pl; \
	    ${INSTALL_SCRIPT} ant antRun runant.pl ${PREFIX}/bin
	@${INSTALL_DATA_DIR} ${ANTDOCS}
	@cp -Rp ${WRKDIST}/docs/* ${ANTDOCS}
	@cd ${WRKDIST} && ${INSTALL_DATA} ${TXT} ${ANTDOCS}
	@${INSTALL_DATA_DIR} ${PREFIX}/lib/java/ant
	@cd ${WRKDIST}/lib && ${INSTALL_DATA} *.jar ${PREFIX}/lib/java/ant

.include <bsd.port.mk>
