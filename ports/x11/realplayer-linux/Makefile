# $MirOS: ports/x11/realplayer-linux/Makefile,v 1.2 2005/04/10 21:51:59 tg Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

DISTNAME=		rp8_linux20_libc6_i386_cs2
PKGNAME=		realplayer-linux-8.0.1p1
CATEGORIES=		audio graphics x11

PERMIT_PACKAGE_CDROM=	"commercial, redistribution not permitted"
PERMIT_PACKAGE_FTP=	"commercial, redistribution not permitted"
PERMIT_DISTFILES_CDROM=	"commercial, redistribution not permitted"
PERMIT_DISTFILES_FTP=	"commercial, redistribution not permitted"

COMMENT=		Real Networks streaming audio/video client
HOMEPAGE=		http://www.real.com/products/player/
EXTRACT_SUFX=		_rpm


RUN_DEPENDS=		:redhat_base->=6.2:emulators/redhat/base62
BUILD_DEPENDS=		::misc/rpm

NO_BUILD=		Yes
NO_FAKE=		Yes
NO_REGRESS=		Yes
INSTALL_STRIP=

RPDIR=			${PREFIX}/lib/RealPlayer
WRKSRC=			${WRKDIR}/usr/lib/RealPlayer8

do-fetch:
	@if [ ! -f ${DISTDIR}/${DISTFILES} ]; then \
		echo "" ; \
		echo " You must fetch the distfile for this port manually" ; \
		echo " after agreeing to the license at:" ; \
		echo "" ; \
		echo "   http://forms.real.com/real/player/unix/unix.html" ; \
		echo "" ; \
		echo " Choose the 'Linux 2.x (libc6 i386) RPM' version and" ; \
		echo " place the downloaded file into ${DISTDIR}" ; \
		echo "" ; \
		exit 1 ; \
	fi

# the find hackery here is so 'make clean' works as it should
do-extract:
	@cd ${WRKDIR}; \
		${LOCALBASE}/bin/rpm2cpio ${DISTDIR}/${DISTFILES} | tar -xf -
	@find ${WRKSRC} -type d -exec ${CHMOD} 755 {} ';'
	@find ${WRKSRC} -type f -exec ${CHMOD} 644 {} ';'

do-install:
	@mkdir -p ${RPDIR}
.for f in mimeinstall.sh pluginstall.sh postinstall.sh
	@${INSTALL_SCRIPT} ${WRKSRC}/${f} ${RPDIR}
.endfor
.for f in realplay rpnp.so
	@${INSTALL_PROGRAM} ${WRKSRC}/${f} ${RPDIR}
.endfor
.for f in LICENSE Mailcap Mime.types README app.kdelnk audiosig.rm \
	firstrun.rm mime.kdelnk raclass.zip \
	realplay.desktop rp7.xpm rp7doc.png rp7doc.xpm rp7mini.xpm
	@${INSTALL_DATA} ${WRKSRC}/${f} ${RPDIR}
.endfor
.for d in Codecs Common Plugins
	@mkdir -p ${RPDIR}/${d}
	@${INSTALL_PROGRAM} ${WRKSRC}/${d}/*.so* ${RPDIR}/${d}
.endfor

	@mkdir -p ${RPDIR}/Plugins/ExtResources
	@${INSTALL_PROGRAM} ${WRKSRC}/Plugins/ExtResources/* \
		${RPDIR}/Plugins/ExtResources/

	@mkdir -p ${PREFIX}/bin; cd ${PREFIX}/bin; ln -sf \
		../lib/RealPlayer/realplay realplay

.if exists(${LOCALBASE}/netscape/plugins)
	@ln -sf ${RPDIR}/raclass.zip ${LOCALBASE}/netscape/plugins
	@ln -sf ${RPDIR}/rpnp.so ${LOCALBASE}/netscape/plugins
.endif

	@mkdir -p ${PREFIX}/share/doc/RealPlayer8
	@${INSTALL_DATA} ${WRKSRC}/Help/readme ${WRKSRC}/Help/realplay.htm \
		${PREFIX}/share/doc/RealPlayer8/
	@mkdir -p ${PREFIX}/share/doc/RealPlayer8/realplay
	@${INSTALL_DATA} ${WRKSRC}/Help/realplay/*.htm \
		${PREFIX}/share/doc/RealPlayer8/realplay
	@mkdir -p ${PREFIX}/share/doc/RealPlayer8/realplay/pics
	@${INSTALL_DATA} ${WRKSRC}/Help/realplay/pics/* \
		${PREFIX}/share/doc/RealPlayer8/realplay/pics

.include <bsd.port.mk>
