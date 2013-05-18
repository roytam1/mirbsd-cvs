# $MirOS: ports/lang/jdk/1.3-linux/Makefile,v 1.5 2006/09/14 00:10:22 tg Exp $
# $OpenBSD: Makefile,v 1.23 2004/05/01 14:29:17 sturm Exp $

BROKEN=			1.3.1_13 is no longer available at Sun,\
			1.3.1_19 does not work (segfaults)

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		Java(TM) Development Kit for Java(TM) 2 Standard Edition 1.3
VERSION=		1.3.1_13

DISTNAME=		jdk${VERSION}
PKGNAME=		jdk-linux-${VERSION}-0
CATEGORIES=		devel java lang
HOMEPAGE=		http://java.sun.com/j2se/
BUILD_DEPENDS=		:redhat_base->=6.2:emulators/redhat/base
RUN_DEPENDS=		${BUILD_DEPENDS}
DISTFILES=		j2sdk-${VERSION:S/./_/g}-linux-i586.bin
EXTRACT_CASES+=	*.bin) \
		    tail `sed -n -e '/^tail/p' -e '/^tail/q' ${FULLDISTDIR}/$$archive \
		    | awk '{print $$2}'` ${FULLDISTDIR}/$$archive >${WRKDIR}/$$archive \
		    && chmod u+x ${WRKDIR}/$$archive && ${WRKDIR}/$$archive -q ;; \

# Sun proprietary
PERMIT_PACKAGE_CDROM=	"Redistribution not permitted"
PERMIT_PACKAGE_FTP=	"Redistribution not permitted"
PERMIT_DISTFILES_CDROM=	"Redistribution not permitted"
PERMIT_DISTFILES_FTP=	"Redistribution not permitted"

NO_BUILD=		Yes
NO_REGRESS=		Yes

FETCH_MANUALLY = " You must fetch the distfile for this port manually"
FETCH_MANUALLY+= " after agreeing to the license agreement at"
FETCH_MANUALLY+= ""
FETCH_MANUALLY+= "     http://java.sun.com/j2se/1.3/download.html"
FETCH_MANUALLY+= ""
FETCH_MANUALLY+= " First choose the following option:"
FETCH_MANUALLY+= " * Download SDK, Windows/Linux/Solaris SPARC/Solaris x86"
FETCH_MANUALLY+= " Then, after several redirects, activate this link:"
FETCH_MANUALLY+= " * self-extracting file, English (${DISTFILES}, ..."
FETCH_MANUALLY+= " Then place the 26'653'147 bytes file just retrieved,"
FETCH_MANUALLY+= " ${DISTFILES} into ${FULLDISTDIR}."

JDK_HOME=		${PREFIX}/jdk1.3.1-linux

# Add empty OpenBSD and MirBSD resource bundle for javah
post-patch:
	mkdir -p ${WRKSRC}/lib/com/sun/tools/javah/resources
	touch ${WRKSRC}/lib/com/sun/tools/javah/resources/OpenBSD_i386.properties
	touch ${WRKSRC}/lib/com/sun/tools/javah/resources/MirBSD_i386.properties
	${WRKSRC}/bin/jar -0uvf ${WRKSRC}/lib/tools.jar -C ${WRKSRC}/lib \
	    com/sun/tools/javah/resources/OpenBSD_i386.properties
	${WRKSRC}/bin/jar -0uvf ${WRKSRC}/lib/tools.jar -C ${WRKSRC}/lib \
	    com/sun/tools/javah/resources/MirBSD_i386.properties

do-install:
	${INSTALL_DATA_DIR} ${JDK_HOME}
	cp -Rp ${WRKDIST}/* ${JDK_HOME}
	
.include <bsd.port.mk>
