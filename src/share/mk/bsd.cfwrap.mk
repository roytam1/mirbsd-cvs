# $MirOS: src/share/mk/bsd.cfwrap.mk,v 1.1 2005/02/14 18:57:46 tg Exp $

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
FSFMAKE?=	${XVARS} ${MAKE} ${FSFMARGS} ${XARGS}
FSFSRC?=	${.CURDIR}
.if !defined(FSFOBJDIR)
FSFOBJDIR!=	readlink ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )
.endif

.PATH: ${FSFSRC}

.if ${FSFMAKEFILE} != "Makefile"
FSFMARGS+=	-f ${FSFMAKEFILE}
.endif

FSFCFLAGS=	${CFLAGS} ${COPTS}
FSFCXXFLAGS=	${CXXFLAGS} ${CXXOPTS}

.if ${FSFCFLAGS:M*Werror*} || ${FSFCXXFLAGS:M*Werror*}
FSFCFLAGS+=	-Werror-maybe-reset
FSFCXXFLAGS+=	-Werror-maybe-reset
.endif

.if !defined(CFWRAP_NO_CCOM)
XVARS+=	CC="${CC:C/ *$//}" CFLAGS="${FSFCFLAGS:C/ *$//}" CPP="${CPP}" \
	CXX="${CXX:C/ *$//}" CXXFLAGS="${FSFCXXFLAGS:C/ *$//}"
.endif

XARGS+=	INSTALL_PROGRAM="${INSTALL_PROGRAM}" INSTALL_DATA="${INSTALL_DATA}" \
	INSTALL_SCRIPT="${INSTALL_SCRIPT}" BSDSRCDIR="${BSDSRCDIR}" \
	GNUSYSTEM_AUX_DIR="${GNUSYSTEM_AUX_DIR}" SHELL="${SHELL}" \
	CONFIG_SHELL="${SHELL}" PICFLAG="${PICFLAG}" DESTDIR="${DESTDIR}"

XVARS+=	CPPFLAGS="${CPPFLAGS}" LDFLAGS="${LDFLAGS} ${LDSTATIC}" \
	INSTALL_STRIP="${INSTALL_STRIP}"

_CFVARS=PATH="/bin:/usr/bin:/sbin:/usr/sbin" ${XVARS} ${XARGS} \
	GCC_NO_WERROR=1 ${CFVARS}

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
	 echo $$t -\> $$l; \
	 rm -f $$t; ln $$l $$t || cp $$l $$t
.  endfor
.endif

.if ${NOMAN:L} != "no"
maninstall:
.endif

.for _tgt in depend lint tags
.  if !target(${_tgt})
${_tgt}: _SUBDIRUSE
	# Nothing here so far...

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
