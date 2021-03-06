# $MirOS: ports/www/mod_jk/Makefile,v 1.5 2006/09/14 00:14:44 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/01/02 08:19:54 sturm Exp $

IGNORE=		"might be broken, used to use Libtool"

# This port currently only works with archs supporting dynamic loading
# and has Apache that supports DSO's.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Apache-Tomcat AJP Connector
VSN=			1.2.5
DISTNAME=		jakarta-tomcat-connectors-jk-${VSN}-src
PKGNAME=		mod_jk-${VSN}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://jakarta.apache.org/tomcat/tomcat-4.1-doc/jk2/

# Apache Software License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_APACHE:=jakarta/tomcat-connectors/jk/source/}

NO_REGRESS=		Yes
USE_GMAKE=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--with-apxs=/usr/sbin/apxs
CONFIGURE_ENV+=		CFLAGS='${CFLAGS} -DCHROOTED_APACHE'

WRKSRC=			${WRKDIR}/${DISTNAME}/jk/native

EXAMPLES=		mod_jk.conf workers.properties
DOCDIR=			${PREFIX}/share/doc/mod_jk
SUBST_VARS=		DOCDIR

post-build:
	strip ${WRKBUILD}/apache-1.3/mod_jk.so.0.0

do-install:
	sed 's,/usr/local,${TRUEPREFIX},' \
		< ${FILESDIR}/mod_jk-enable >${WRKSRC}/mod_jk-enable
	${INSTALL_SCRIPT} ${WRKSRC}/mod_jk-enable ${PREFIX}/sbin/mod_jk-enable
	${INSTALL_DATA} ${WRKBUILD}/apache-1.3/mod_jk.so.0.0 ${PREFIX}/lib/mod_jk.so
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mod_jk
.for file in ${EXAMPLES}
	${INSTALL_DATA} ${FILESDIR}/${file} ${PREFIX}/share/examples/mod_jk
.endfor
	${INSTALL_DATA_DIR} ${DOCDIR}
	sed 's,/usr/local,${TRUEPREFIX},' \
		< ${FILESDIR}/README.OpenBSD >${WRKSRC}/README.OpenBSD
	${INSTALL_DATA} ${WRKSRC}/README.OpenBSD ${DOCDIR}
	${INSTALL_DATA} ${WRKDIR}/${DISTNAME}/LICENSE ${DOCDIR}
	cd ${WRKDIR}/${DISTNAME}/jk/docs && \
	    find . -type d -exec ${INSTALL_DATA_DIR} ${DOCDIR}/{} \; && \
	    find . -type f -exec ${INSTALL_DATA} {} ${DOCDIR}/{} \;

.include <bsd.port.mk>
