# $MirOS: ports/lang/jdk/1.4/Makefile,v 1.12 2005/07/07 21:22:29 bsiegert Exp $
# $OpenBSD$
# $FreeBSD: /repoman/r/pcvs/ports/java/jdk14/Makefile,v 1.79 2004/08/18 07:06:03 glewis Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

CATEGORIES=		devel/jdk java lang
COMMENT=			Java2(TM) Standard Edition Dev Kit v${V}
COMMENT-jre=			Java2(TM) Standard Edition Runtime Environment v${V}
V=			1.4.2
DISTNAME=		j2sdk-1_4_2
PKGNAME=		jdk-${V}-0
PKGNAME-jre=		jre-${V}-0
# explanations at http://www.intricatesoftware.com/OpenBSD/java/jdk14.html
# wwws is not a typo in the following:
HOMEPAGE=		http://wwws.sun.com/software/communitysource/j2se/java2/

MULTI_PACKAGES= 	-jre
DISTFILES=		${DISTNAME}-src-scsl.zip \
			${DISTNAME}-bin-scsl.zip \
			bsd-jdk14-patches-6.tar.gz

# Sun Community Source License
# http://www.sun.com/981208/scsl/principles.html
PERMIT_PACKAGE_CDROM=	"SCSL"
PERMIT_PACKAGE_FTP=	"SCSL"
PERMIT_DISTFILES_CDROM= "SCSL"
PERMIT_DISTFILES_FTP=	"SCSL"

# TCK (Technology Compatibility Kit) covered by yet another license...
NO_REGRESS=		yes

VMEM_WARNING=		Yes
BUILD_DEPENDS=		:gtar-*:archivers/gtar \
			:zip-*:archivers/zip
RUN_DEPENDS=		:zip-*:archivers/zip \
			:gs-fonts-std-*:print/ghostscript/fonts-std
USE_MOTIF=		openmotif
USE_GMAKE=		Yes
USE_CXX=		Yes
TAR=			${LOCALBASE}/bin/gtar
MAKE_ENV+=		ALT_MOTIF_DIR="${LOCALBASE}" \
			OPENWINHOME="${X11BASE}" \
			HAVE_DPS="yes" \
			DEV_ONLY="YES" \
			LANG="C"
MAKE_ENV+=		PLATFORM=bsd TRUE_PLATFORM=OpenBSD # XXX?
MAKE_FLAGS+=		CC="${CC}"

# Error message for distfile.
FETCH_MANUALLY=		"You must manually fetch the distibution files, place"
FETCH_MANUALLY+=	"them in ${FULLDISTDIR} and then run make again."
FETCH_MANUALLY+=	"Get the SCSL source \& binary files:"
FETCH_MANUALLY+=	"    ${DISTNAME}-src-scsl.zip"
FETCH_MANUALLY+=	"    ${DISTNAME}-bin-scsl.zip"
FETCH_MANUALLY+=	"from http://wwws.sun.com/software/communitysource/j2se/java2/download.html"
FETCH_MANUALLY+=	"Get the BSD patchset file:"
FETCH_MANUALLY+=	"    bsd-jdk14-patches-6.tar.gz"
FETCH_MANUALLY+=	"from http://www.eyesbeyond.com/freebsddom/java/jdk14.html"

FLAVORS=		no_plugin no_webstart with_ipv6
PSEUDO_FLAVORS=		native_bootstrap openbsd_bootstrap
FLAVOR?=

.if !${FLAVOR:L:Mwith_ipv6}
PATCH_LIST=		patch-* disable-ipv6
.endif

.if ${FLAVOR:L:Mopenbsd_bootstrap}
.  if !${FLAVOR:L:Mnative_bootstrap}
FLAVOR+=		native_bootstrap
.  endif
MAKE_ENV+=		ALT_BOOTDIR=/emul/openbsd/usr/local/jdk-1.4.2
.elif ${FLAVOR:L:Mnative_bootstrap}
BUILD_DEPENDS+=		:jdk-1.4*:lang/jdk/1.4
MAKE_ENV+=		ALT_BOOTDIR="${LOCALBASE}/${JDKHOME}"
.else
DISTFILES+=		j2sdk-1_4_2-linux-i586.bin
FETCH_MANUALLY+=	"Get the linux binary sdk file:"
FETCH_MANUALLY+=	"    j2sdk-1_4_2-linux-i586.bin"
FETCH_MANUALLY+=	"from http://java.sun.com/products/archive/j2se/1.4.2/"
DISTFILES+=		bootstrap-src-jdk14.tgz
FETCH_MANUALLY+=	"Get the bootstrap source dist file:"
FETCH_MANUALLY+=	"    bootstrap-src-jdk14.tgz"
FETCH_MANUALLY+=	"from http://www.intricatesoftware.com/OpenBSD/java/jdk14.html"
BUILD_DEPENDS+=		:jdk-linux->=1.3.1_10:lang/jdk/1.3-linux
ALT_BOOTDIR2=		${LOCALBASE}/jdk1.3.1-linux
MAKE_ENV+=		ALT_BOOTDIR="${WRKDIST}"
MAKE_ENV+=		ALT_BOOTDIR2="${ALT_BOOTDIR2}"
MAKE_ENV+=		MANUAL_BOOTSTRAP="yes"
CLASSESDIR=		${WRKDIR}/control/build/bsd-i586/classes
LINUXFILES=		j2sdk1.4.2/lib/unpack \
			j2sdk1.4.2/lib/tools.pack \
			j2sdk1.4.2/jre/lib/rt.pack
EXTRACT_CASES+=		*.bin) \
			perl -p0777 -e "s/.*?PK\03\04/PK\03\04/s" ${FULLDISTDIR}/$$archive \
				>${WRKDIR}/$$archive.zip && \
			unzip -j ${WRKDIR}/$$archive ${LINUXFILES} ;;
.endif

.if !${FLAVOR:L:Mnative_bootstrap}
NO_SYSTRACE=		mix of different binaries
.endif

.if !${FLAVOR:L:Mno_plugin}
BUILD_DEPENDS+=		:nspr-*:devel/nspr

LIB_DEPENDS+=		glib.1::devel/glib1 \
			gtk.1.2::x11/gtk+1

MODULES+=		devel/gettext

MAKE_ENV+=		LIBG_HDRS="${LOCALBASE}/include/glib-1.2" \
			GTK_HDRS="${LOCALBASE}/include/gtk-1.2" \
			LIBIDL_HDRS= \
			INTL_DIR="${LOCALBASE}"

.else
#no plugin - no messages
MESSAGE=		/dev/null
MAKE_ENV+=		NO_PLUGIN="YES"
.endif

.if ${FLAVOR:L:Mno_webstart}
MAKE_ENV+=		NO_JAVAWS="YES"
.endif

JDKHOME=		jdk-${V}
JREHOME=		jre-${V}

SUBST_VARS=		JDKHOME JREHOME

# Deal with Sun's internal build structure
WRKDIST=		${WRKDIR}
WRKSRC=         	${WRKDIR}/control/make
OUTPUTDIR=		${WRKDIR}/control/build/bsd-i586
JDKIMAGEDIR=		${OUTPUTDIR}/j2sdk-image
JDKIMAGEDIR_G=		${OUTPUTDIR}/j2sdk-debug-image
JREIMAGEDIR=		${OUTPUTDIR}/j2re-image
CACERTSDIR=		${WRKDIR}/j2se/src/share/lib/security

.if !${FLAVOR:L:Mnative_bootstrap}
# The removal of /tmp/unpack.log is to workaround a security issue
# described here:
#   http://www.securityfocus.com/archive/1/343038
post-extract:
	@rm -f /tmp/unpack.log
	@cd ${WRKDIR} && \
		./unpack tools.pack tools.jar && \
		./unpack rt.pack rt.jar
	@rm -f /tmp/unpack.log
	@mkdir -p ${CLASSESDIR}
	@cd ${CLASSESDIR} && \
		xargs ${ALT_BOOTDIR2}/bin/jar xf ${WRKDIR}/tools.jar <${FILESDIR}/tools_jar_class_list && \
		xargs ${ALT_BOOTDIR2}/bin/jar xf ${WRKDIR}/rt.jar <${FILESDIR}/rt_jar_class_list
.endif

pre-patch:
	@cp -f ${FILESDIR}/cacerts ${CACERTSDIR}
	@cd ${WRKDIR} &&  \
		${CHMOD} -R u+w * && \
		${PATCH} -p0 -z .orig.bsd <${WRKDIR}/jdk14.patches

.if !${FLAVOR:L:Mnative_bootstrap}
post-patch:
	@cd ${WRKDIR}/bin && \
		${CHMOD} +x linux_bootscript
.  for prog in java javac javah jar
	@cd ${WRKDIR}/bin && \
		ln -s linux_bootscript ${prog}
.  endfor
.endif

post-build:
	@rm -rf ${JDKIMAGEDIR}/demo/jfc/SwingSet2/resources \
		${JDKIMAGEDIR}/demo/plugin/jfc/SwingSet2/resources

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${JDKHOME}
	cd ${JDKIMAGEDIR} && tar -cf - * | tar -C ${PREFIX}/${JDKHOME} -xf -
	cd ${JDKIMAGEDIR_G} && tar -cf - * | tar -C ${PREFIX}/${JDKHOME} -xf -
	${INSTALL_DATA_DIR} ${PREFIX}/${JREHOME}
	cd ${JREIMAGEDIR} && tar -cf - * | tar -C ${PREFIX}/${JREHOME} -xf -

.include <bsd.port.mk>
