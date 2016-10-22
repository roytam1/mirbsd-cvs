# $MirOS: src/share/mk/bsd.cfwrap.mk,v 1.25 2013/08/19 17:35:39 tg Exp $

.if !defined(BSD_CFWRAP_MK)
BSD_CFWRAP_MK=1

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif
.if !defined(BSD_SYS_MK)
.  include <bsd.sys.mk>
.endif

.if !target(.MAIN)
.  if exists(${.CURDIR}/../Makefile.inc)
.    include "${.CURDIR}/../Makefile.inc"
.  endif

.MAIN: all
.endif

INSTALL_PROGRAM=	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} \
			    -o ${BINOWN} -g ${BINGRP} -m ${BINMODE}
INSTALL_SCRIPT=		${INSTALL} ${INSTALL_COPY} \
			    -o ${BINOWN} -g ${BINGRP} -m ${BINMODE}
INSTALL_DATA=		${INSTALL} ${INSTALL_COPY} \
			    -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE}
INSTALL_MAN=		${INSTALL} ${INSTALL_COPY} \
			    -o ${MANOWN} -g ${MANGRP} -m ${MANMODE}
INSTALL_DOC=		${INSTALL} ${INSTALL_COPY} \
			    -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE}

GCCHOST?=	${OStriplet}
GCCTARGET?=	${OStriplet}
ALL_TARGET?=	all
INST_TARGET?=	install
FSFMAKEFILE?=	Makefile
CLEANFILES+=	config.cache config.log
FSFISLIB?=	Yes
FSFMAKE?=	${XVARS} ${MAKE} ${FSFMARGS} ${XARGS}
FSFSRC?=	${.CURDIR}
.if !defined(FSFOBJDIR)
FSFOBJDIR!=	realpath ${.OBJDIR}
.endif

.PATH: ${FSFSRC}

.if ${FSFMAKEFILE} != "Makefile"
FSFMARGS+=	-f ${FSFMAKEFILE}
.endif

HOSTCFLAGS?=	${CFLAGS} ${COPTS}

FSFCFLAGS+=	${CFLAGS} ${COPTS}
FSFCXXFLAGS+=	${CXXFLAGS} ${CXXOPTS} -fno-omit-frame-pointer
FSFHOSTCFLAGS+=	${HOSTCFLAGS}

.if ${FSFCFLAGS:M*Werror*} || ${FSFCXXFLAGS:M*Werror*}
FSFCFLAGS+=	-Werror-maybe-reset
FSFCXXFLAGS+=	-Werror-maybe-reset
FSFHOSTCFLAGS+=	-Werror-maybe-reset
.endif

.if (${DEBUGLIBS:L} == "yes") && (${FSFISLIB:L} == "yes")
FSFCDEBUG=	-g1
FSFCFLAGS+=	${FSFCDEBUG} -fno-omit-frame-pointer
FSFCXXFLAGS+=	${FSFCDEBUG}
FSFHOSTCFLAGS+=	${FSFCDEBUG} -fno-omit-frame-pointer
.endif
.if defined(MKC_DEBG) && (${MKC_DEBG:L} != "no")
FSFCDEBUG=	-g3
.endif

.if !defined(CFWRAP_NO_CCOM)
XVARS+=	CC=${CC:NGCC_HONOUR_COPTS=*:M*:Q} CFLAGS=${FSFCFLAGS:M*:Q} CPP=${CPP:Q}
.  if !defined(CFWRAP_NO_CXXCOM)
XVARS+=	CXX=${CXX:M*:Q} CXXFLAGS=${FSFCXXFLAGS:M*:Q}
.  endif
XVARS+=	HOSTCFLAGS=${FSFHOSTCFLAGS:M*:Q} CC_FOR_BUILD=${HOSTCC:M*:Q}
XVARS+=	CFLAGS_FOR_BUILD=${FSFHOSTCFLAGS:M*:Q}
.endif

XARGS+=	INSTALL_PROGRAM=${INSTALL_PROGRAM:Q} INSTALL_DATA=${INSTALL_DATA:Q} \
	INSTALL_SCRIPT=${INSTALL_SCRIPT:Q} BSDSRCDIR=${BSDSRCDIR:Q} \
	GNUSYSTEM_AUX_DIR=${GNUSYSTEM_AUX_DIR:Q} SHELL=${SHELL:Q} \
	CONFIG_SHELL=${SHELL:Q} PICFLAG=${PICFLAG:Q} DESTDIR=${DESTDIR:Q}

XVARS+=	CPPFLAGS=${CPPFLAGS:C/ *$//:Q} LDFLAGS=${LDFLAGS:Q}\ ${LDSTATIC:Q} \
	INSTALL_STRIP=${INSTALL_STRIP:Q} GCC_HONOUR_COPTS=1

_CFVARS+=${XVARS} ${XARGS} GCC_NO_WERROR=1 GCC_HONOUR_COPTS=0

# reported to be misused by bsiegert@
_CFVARS+=ac_cv_func_malloc_0_nonnull=yes
# caught by systrace, tries to write to ${LOCALBASE}/lib as check
_CFVARS+=ac_cv_sys_long_file_names=yes
# cannot be used on MirBSD
_CFVARS+=ac_cv_type_long_double=no ac_cv_sizeof_long_double=0

_CFVARS+=${CFVARS}

CFARGS+=--build=${OStriplet} --host=${GCCHOST} --srcdir=${FSFSRC}
.if ${GCCTARGET} != ${GCCHOST}
CFARGS+=--target=${GCCTARGET}
.endif
.if ${NOPIC:L} != "no"
CF_PIC=	--disable-shared
.else
CF_PIC=	--enable-shared
.endif

all: _SUBDIRUSE do-build

prereq: config.status

config: config.clean config.status

config.clean:
	rm -f config.cache config.status

config.status: ${FSFMAKEFILE}.in configure
	cd ${FSFOBJDIR} && ${_CFVARS} ${SHELL} ${FSFSRC}/configure ${CFARGS}

build: config.status
	cd ${FSFOBJDIR} && ${FSFMAKE} ${ALL_TARGET}

.if !target(do-build)
do-build: build
.endif

install: _SUBDIRUSE pre-install do-install maninstall linkinstall post-install

.if !target(do-install)
do-install:
	cd ${FSFOBJDIR} && ${FSFMAKE} ${INST_TARGET}
.endif

pre-install:

post-install:

linkinstall:
.if defined(LINKS) && !empty(LINKS)
.  for lnk file in ${LINKS}
	@l=${DESTDIR}${lnk}; \
	 t=${DESTDIR}${file}; \
	 print -r -- $$t -\> $$l; \
	 rm -f $$t; ln $$l $$t || cp $$l $$t
.  endfor
.endif

.if ${NOMAN:L} != "no"
maninstall:
.endif

.for _tgt in depend lint tags
.  if !target(${_tgt})
${_tgt}: _SUBDIRUSE
.  endif
.endfor

clean: _SUBDIRUSE pre-clean do-clean post-clean

pre-clean:

.if !target(do-clean)
do-clean:
	-if test -e ${FSFMAKEFILE}; then \
		cd ${FSFOBJDIR} && ${FSFMAKE} distclean; \
	fi
.endif

post-clean:
	-rm -rf ${CLEANFILES}

cleandir: _SUBDIRUSE clean

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
.if ${NOMAN:L} == "no"
.  include <bsd.man.mk>
.endif

.PHONY:	all prereq config config.clean build do-build install \
	pre-install do-install maninstall post-install depend \
	lint tags clean pre-clean do-clean post-clean cleandir

.endif
