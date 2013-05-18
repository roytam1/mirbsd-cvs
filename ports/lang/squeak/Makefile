# $MirOS: ports/lang/squeak/Makefile,v 1.4 2006/09/14 00:10:28 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/05/17 15:04:03 espie Exp $

NOT_FOR_PLATFORM=	${LP64_PLATFORMS}

COMMENT=			smalltalk system
CATEGORIES=	lang

# Apple license, similar to GPL, with a clause to protect Apple
# against litigation
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes


MAJOR=3
MINOR=0
SUB=3552
VSN=			${MAJOR}.${MINOR}
SUBST_VARS+=		MAJOR
DIST_SUBDIR=squeak${VSN}

FTPSITE=	ftp://st.cs.uiuc.edu/pub/Smalltalk/Squeak
HOMEPAGE=	http://squeak.org/
MASTER_SITES=${FTPSITE}/${VSN}/platform-independent/
MASTER_SITES0=${FTPSITE}/${VSN}/unix-linux/src/ \
	http://www-sor.inria.fr/~piumarta/squeak/unix/

COMMON_FILES=ReadMe.txt.gz MajorShrinkFor${VSN}.cs.gz SqueakV${MAJOR}.sources.gz

IMAGE=Squeak${VSN}-${SUB}.zip

DISTNAME=squeak-${VSN}
DISTFILES=Squeak-${VSN}-src.tar.gz:0 ${COMMON_FILES} ${IMAGE}

EXTRACT_ONLY=Squeak-${VSN}-src.tar.gz ${IMAGE}

WRKDIST=${WRKDIR}/Squeak-${VSN}
WRKSRC=	${WRKDIST}/src/unix


CONFIGURE_STYLE=gnu
CONFIGURE_ENV=RANLIB=ranlib
#MAKE_FLAGS=CFLAGS=-O2
#ALL_TARGET=squeak plugins map
ALL_TARGET=all squeak.1
USE_GMAKE=yes
USE_X11=yes

MAKE_FLAGS=docdir=${TRUEPREFIX}/share/doc/squeak-${VSN}
.if ${MACHINE_ARCH} != "powerpc"
MAKE_FLAGS+=INTERP=gnu-interp
.endif
FAKE_FLAGS=${MAKE_FLAGS} DESTDIR=${WRKINST}

PLUGINS= Profiler.so SoundCodecPrims.so Squeak3D.so System.so

NO_REGRESS=	Yes

post-extract:
	cp ${FILESDIR}/sqOpenBSDSound.c ${WRKSRC}
	rm ${WRKSRC}/sqUnixSound.c
	gzip ${WRKDIR}/Squeak${VSN}.{changes,image}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/squeak
	for i in ${COMMON_FILES}; \
	do \
		${INSTALL_DATA} ${FULLDISTDIR}/$$i ${PREFIX}/share/squeak; \
	done
	${INSTALL_DATA} ${WRKDIR}/Squeak${VSN}.changes.gz ${PREFIX}/share/squeak
	${INSTALL_DATA} ${WRKDIR}/Squeak${VSN}.image.gz ${PREFIX}/share/squeak
	gunzip ${PREFIX}/share/squeak/SqueakV${MAJOR}.sources.gz
	sed -e 's,@PREFIX@,${TRUEPREFIX},' -e 's,@V@,${VSN},' \
	    <${FILESDIR}/inisqueak >${PREFIX}/lib/squeak/${VSN}/inisqueak
	@chmod a+x ${PREFIX}/bin/inisqueak

.include <bsd.port.mk>
