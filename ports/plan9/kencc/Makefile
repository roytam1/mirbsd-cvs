# $MirOS: ports/plan9/kencc/Makefile,v 1.7 2009/08/16 16:28:02 tg Exp $

# sort of hard to add more...
ONLY_FOR_PLATFORM=	Darwin:*:powerpc MirBSD:*:i386 OpenBSD:*:i386

COMMENT=		Plan 9 compiler suite
CATEGORIES=		devel lang plan9
VSN=			20060303
DASH_VER=		1
DISTNAME=		kencc-${VSN}
DIST_SUBDIR=		inferno-${VSN}
DISTFILES=		FreeBSD.tgz MacOSX.tgz inferno.tgz utils.tgz
HOMEPAGE=		http://www.advogato.org/proj/Kencc/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		http://www.vitanuova.com/dist/4e/${VSN}/

# GPL, LGPL, Lucent 1.02, "Vita Nuova" (MIT-style)
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
# Vita Nuova (${PREFIX}/share/doc/kencc/NOTICE)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS+=		::plan9/9e
WRKDIST=		${WRKDIR}/install/utils

.if ${MACHINE_OS} == "Darwin"
FBSDORMAC=		MacOSX
PROCESSOR=		power
BROKEN=			need a CPP_DEFINES line for ${MACHINE_OS}
.else
FBSDORMAC=		FreeBSD
PROCESSOR=		386
CPP_DEFINES=		__unix__ __KENCC__ __OpenBSD__ i386 __i386__
.  if ${OStype} == "MirBSD"
CPP_DEFINES+=		__MirBSD__
.  endif
.endif

PORTPATH=		${WRKSRC}/${FBSDORMAC}/${PROCESSOR}/bin:${WRKDIR}/bin:${_PORTPATH}
MK_VARS=		WRKSRC=${WRKSRC:Q} \
			MP_CC=${_PASS_CC:T:Q} MP_CFLAGS=${CFLAGS:Q} \
			FBSDORMAC=${FBSDORMAC:Q} \
			objtype=${PROCESSOR:Q}

ALL_TARGETS=	utils/libregexp libbio lib9 utils
.ifdef NUKE
NUKE_TARGETS=	libbio lib9 utils
.else
NUKE_TARGETS=	utils/libregexp libbio lib9 utils/mk
.endif

BINS=		0a 0c 0l 1a 1c 1l 2a 2c 2l 5a 5c 5coff 5cv 5l 8a 8c 8l \
		data2c data2s iar ka kc kl mk mkext qa qc ql tc va vc vl
MANSRC=		${WRKDIR}/install/inferno/man
MANS10=		2a 2c 2l 5coff 5cv iar mk
MLINKS=		2a 0a 2a 1a 2a 5a 2a 8a 2a ka 2a qa 2a va \
		2c 0c 2c 1c 2c 5c 2c 8c 2c kc 2c qc 2c vc \
		2l 0l 2l 1l 2l 5l 2l 8l 2l kl 2l ql 2l vl

do-extract:
.for _f in ${DISTFILES}
	# NB: this is supposed to fail
	-cd ${WRKDIR} && ${GZCAT} ${FULLDISTDIR}/${_f} | tar xf -
	cd ${WRKDIR}/install/${_f:R} && ${GZCAT} 1141383122.gz | 9e
.endfor
	cd ${WRKDIR}/install/utils && \
	    cp -r ../FreeBSD/FreeBSD . && cp -r ../MacOSX/MacOSX .
	cd ${WRKDIR}/install/utils/include && \
	    lndir ${WRKDIR}/install/inferno/include
	cp ${WRKDIR}/install/inferno/mkconfig ${WRKDIR}/install/utils/
	cd ${WRKDIR}/install/utils && cp -r ../inferno/mkfiles .

do-configure:
	cd ${WRKSRC} && ${SETENV} HOSTCC=${_PASS_CC:T:Q}\ ${CFLAGS:Q} \
	    FBSDORMAC=${FBSDORMAC:Q} PROCESSOR=${PROCESSOR:Q} \
	    WRKSRC=${WRKSRC:Q} ${SCRIPTS_ENV} ${SH} ./makemk.sh
	print '%g/@PREFIX@/s!!${PREFIX}!g\nwq' | \
	    ed -s ${WRKSRC}/utils/cc/mkfile

do-build:
.for _i in ${NUKE_TARGETS}
	cd ${WRKSRC}/${_i} && ${SETENV} ${MAKE_ENV} ${MK_VARS} mk nuke
.endfor
.for _i in ${ALL_TARGETS}
	cd ${WRKSRC}/${_i} && ${SETENV} ${MAKE_ENV} ${MK_VARS} mk
.endfor
	mkdir -p ${WRKSRC}/cat1
	${NROFF} -man ${MANSRC}/8/mkfs >${WRKSRC}/cat1/mkext.0
.for _i in ${MANS10}
	${NROFF} -man ${MANSRC}/10/${_i} >${WRKSRC}/cat1/${_i}.0
.endfor
	print '#!${MKSH}' >${WRKSRC}/9cpp
	print 'exec /usr/libexec/cpp \\' >>${WRKSRC}/9cpp
.for _i in ${CPP_DEFINES}
	print '\t-D${_i} \\' >>${WRKSRC}/9cpp
.endfor
	print '\t"$$@"' >>${WRKSRC}/9cpp

do-install:
	cd ${WRKSRC}/utils && ${SETENV} ${MAKE_ENV} ${MK_VARS} mk install
.for _i in ${BINS}
	${INSTALL_PROGRAM} ${WRKSRC}/${FBSDORMAC}/${PROCESSOR}/bin/${_i} \
	    ${PREFIX}/bin/
.endfor
.for _i in mkext ${MANS10}
	${INSTALL_MAN} ${WRKSRC}/cat1/${_i}.0 ${PREFIX}/man/cat1/
.endfor
.for _i _j in ${MLINKS}
	cd ${PREFIX}/man/cat1 && ln -s ${_i}.0 ${_j}.0
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/kencc
	${INSTALL_DATA} ${WRKSRC}/utils/NOTICE ${PREFIX}/share/doc/kencc/
	${INSTALL_SCRIPT} ${WRKSRC}/9cpp ${PREFIX}/bin/

.include <bsd.port.mk>
