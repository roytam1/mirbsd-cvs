# $MirOS: ports/multimedia/realplayer-linux/Makefile,v 1.2 2006/03/24 13:57:07 tg Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			Real Networks streaming audio/video client
DISTNAME=		rp8_linux20_libc6_i386_cs2
PKGNAME=		realplayer-linux-8.0.1-4
CATEGORIES=		audio graphics x11 multimedia
DISTFILES=		rp8_linux20_libc6_i386_cs2_rpm \
			rv9_libc6_i386_cs2.tgz
HOMEPAGE=		http://www.real.com/products/player/

PERMIT_PACKAGE_CDROM=	"commercial, redistribution not permitted"
PERMIT_PACKAGE_FTP=	"commercial, redistribution not permitted"
PERMIT_DISTFILES_CDROM=	"commercial, redistribution not permitted"
PERMIT_DISTFILES_FTP=	"commercial, redistribution not permitted"

RUN_DEPENDS=		:redhat_base->=6.2:emulators/redhat/base
BUILD_DEPENDS=		::converters/rpm2cpio

NO_REGRESS=		Yes

RPDIR=			${PREFIX}/lib/RealPlayer
WRKSRC=			${WRKDIR}/usr/lib/RealPlayer8

do-fetch:
	@cd ${DISTDIR}; x=1; for f in ${DISTFILES}; do \
		test -f $$f || x=0; \
	done; if [ $$x = 0 ]; then \
		echo "" ; \
		echo " You must fetch the distfile for this port manually" ; \
		echo " after agreeing to the license at:" ; \
		echo "" ; \
		echo "   http://forms.real.com/real/player/blackjack.html" ; \
		echo "" ; \
		echo " Choose 'RealPlayer 8 for Linux 2.x (i386) RPM' and" ; \
		echo " place the downloaded file into ${DISTDIR}" ; \
		echo " Note you must change \"cs1\" to \"cs2\" in the URL!" ; \
		echo " You also need RV9 Codec packs for Unix RealPlayer 8" ; \
		echo "" ; \
		exit 1 ; \
	fi

# the chmod hackery here is so 'make clean' works as it should
do-extract:
	@cd ${WRKDIR}; for f in ${DISTFILES}; do \
		if [[ $$f = *rpm ]]; then \
			${LOCALBASE}/bin/rpm2cpio ${DISTDIR}/$$f; \
		else \
			gzip -dc ${DISTDIR}/$$f; \
		fi | ${TAR} xf -; \
	done
	@chmod -R u=rwX,go=rX ${WRKSRC}

do-build:
	sed 's!@RPDIR@!${RPDIR}!g' \
	    <${FILESDIR}/realplay.sh >${WRKBUILD}/realplay.sh

do-install:
	${INSTALL_DATA_DIR} ${RPDIR}
.for _f in mimeinstall.sh realplay rpnp.so
	${INSTALL_SCRIPT} ${WRKSRC}/${_f} ${RPDIR}/
.endfor
.for _f in LICENSE Mailcap Mime.types app.kdelnk audiosig.rm firstrun.rm \
    raclass.zip realplay.desktop rp7.xpm rp7doc.png rp7doc.xpm rp7mini.xpm
	${INSTALL_DATA} ${WRKSRC}/${_f} ${RPDIR}/
.endfor
.for _f in Codecs Common Plugins
	${INSTALL_DATA_DIR} ${RPDIR}/${_f}
	${INSTALL_SCRIPT} ${WRKSRC}/${_f}/*.so* ${RPDIR}/${_f}/
.endfor
	${INSTALL_SCRIPT} ${WRKDIR}/rv9/codecs/{drv4,rv40}.so.6.0 \
	    ${RPDIR}/Codecs/
	${INSTALL_DATA_DIR} ${RPDIR}/Plugins/ExtResources
	${INSTALL_SCRIPT} ${WRKSRC}/Plugins/ExtResources/* \
		${RPDIR}/Plugins/ExtResources/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/RealPlayer8/realplay/pics
	${INSTALL_DATA} ${WRKSRC}/Help/readme ${WRKSRC}/Help/realplay.htm \
	    ${PREFIX}/share/doc/RealPlayer8/
	${INSTALL_DATA} ${WRKSRC}/Help/realplay/*.htm \
	    ${PREFIX}/share/doc/RealPlayer8/realplay/
	${INSTALL_DATA} ${WRKSRC}/Help/realplay/pics/* \
	    ${PREFIX}/share/doc/RealPlayer8/realplay/pics/
	${INSTALL_SCRIPT} ${WRKBUILD}/realplay.sh ${PREFIX}/bin/realplay

.include <bsd.port.mk>
