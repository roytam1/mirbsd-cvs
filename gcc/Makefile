# $MirOS: gcc/Makefile,v 1.19 2006/03/01 14:20:25 tg Exp $

.include <bsd.own.mk>
.include "${GNUSYSTEM_AUX_DIR}/locations.mk"
.include "${BSDSRCDIR}/Makefile.inc"
.include "Makefile.inc"

_STFILE_PFX=	${DESTDIR}${GCC_PREFIX}/.policy.mk
_STCMD_PFX=	${_STCMD} -f ${_STFILE_PFX}

.if ${OStype} != "MirBSD"
GCC_NATIVE=	No
.endif
GCC_NATIVE?=	Yes

SUBOBJDIR!=	readlink -nf ${.OBJDIR}
BSDMAKE!=	whence -p ${MAKE}
CC!=		whence -p ${CC}

IGNORE_TGTS=	obj
BUILD_TGTS=	all clean depend lint prereq tags
INSTALL_TGTS=	includes install

.ifdef _CROSSBUILD
EXTRA_ENV=	PATH=/bin:/usr/bin:/sbin:/usr/sbin:${GCC_PREFIX}/${GCC_TARGET}/bin
EXTRA_ENV+=	CROSSCFLAGS=${CROSSCFLAGS:Q}
.else
EXTRA_ENV=	PATH=/bin:/usr/bin:/sbin:/usr/sbin
.endif

.if ${GCC_NATIVE:L} != "yes"
EXTRA_ENV:=	${EXTRA_ENV:S!PATH=!PATH=${BSDMAKE:H}:${CC:H}:!}
_STCMD=
_STFILE_SUB=
_STFILE_DEST=
_STFILE_PFX=
_STCMD_SUB=
_STCMD_DEST=
_STCMD_PFX=
.endif

.MAIN: all

.for _i in ${IGNORE_TGTS}
${_i}:
	cd ${.CURDIR} && ${EXTRA_ENV} exec ${BSDMAKE} -f Makefile.sub $@
.endfor

.for _i in ${BUILD_TGTS}
${_i}: ${_STFILE_SUB}
	ulimit -dS 245760 && cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_SUB} ${BSDMAKE} -f Makefile.sub $@
.endfor

.for _i in ${INSTALL_TGTS}
${_i}:
.  if ${GCC_NATIVE:L} == "yes"
	d="${DESTDIR}${GCC_PREFIX}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${BSDMAKE}
.  endif
	cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_PFX} ${BSDMAKE} -f Makefile.sub $@
.  if ${GCC_NATIVE:L} == "yes"
	sleep 1; ${SUDO} rm -f ${_STFILE_PFX}
.  endif
.endfor

.if ${GCC_NATIVE:L} == "yes"
${_STFILE_SUB}:
	cd ${SUBOBJDIR} && env WRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${BSDMAKE}
.endif

cleandir-recursive: ${_STFILE_SUB}
	cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_SUB} ${BSDMAKE} -f Makefile.sub cleandir

cleandir: cleandir-recursive local-cleandir

local-cleandir: .PHONY
	-rm -rf ${SUBOBJDIR}/bs-{1,2}
.if ${GCC_NATIVE:L} == "yes"
	-sleep 1; rm -f ${_STFILE_SUB}
.endif

b-r: .PHONY
	# Test if the targets are mounted suitable for root (BTSTF)
.for _dir in ${BSDOBJDIR} ${BSDRELDIR}
	mkdir -p ${_dir} || ${SUDO} mkdir -p ${_dir}
	${SUDO} touch ${_dir}/permissions.test
	${SUDO} chown root:wheel ${_dir}/permissions.test
	${SUDO} rm ${_dir}/permissions.test
.endfor
	touch ${BSDOBJDIR}/permissions.test && rm ${BSDOBJDIR}/permissions.test
	cd ${.CURDIR} && exec ${BSDMAKE} obj
	cd ${.CURDIR} && exec ${BSDMAKE}
	cd ${.CURDIR} && exec ${SUDO} ${BSDMAKE} install
	cd ${.CURDIR} && exec ${BSDMAKE} release BSDRELDIR=${BSDRELDIR}

release: .PHONY
	mkdir -p ${BSDRELDIR}/base || ${SUDO} mkdir -p ${BSDRELDIR}/base
	cd ${BSDSRCDIR} && ${EXTRA_ENV} exec \
	    ${BSDMAKE} distrib-dirs mksystrace-dest DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} install DESTDIR=${BSDRELDIR}/base

bootstrapbuild: ${_STFILE_SUB}
	ulimit -dS 245760 && cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_SUB} ${BSDMAKE} -f Makefile.sub all \
	    NO_CXX=Yes NO_OBJC=Yes NO_PASCAL=Yes NO_BOEHMGC=Yes

bootstrap:
	@cd ${.CURDIR} && ${MAKE} obj && exec ${MAKE} do-bootstrap \
	    _LIBERTY_GIVEN=$$(l="${_LIBERTY}"; \
	    [[ -e $${l:-/nonexistant} ]] && print yes)

_LIBERTY_GIVEN?=No
do-bootstrap:
.if ${_LIBERTY_GIVEN} == "no"
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} obj
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} depend
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} all
.endif
	mkdir -p ${SUBOBJDIR}/bs-{1,2}
.if ${_LIBERTY_GIVEN} == "no"
	cd ${.CURDIR} && exec ${MAKE} bootstrapbuild COMPILER_ONLY=Yes \
	    _LIBERTY=${GNU_LIBIBERTY_SRC}/obj/libiberty.a \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-1
	cd ${.CURDIR} && exec ${MAKE} install COMPILER_ONLY=Yes \
	    _LIBERTY=${GNU_LIBIBERTY_SRC}/obj/libiberty.a \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-1
.else
	cd ${.CURDIR} && exec ${MAKE} bootstrapbuild COMPILER_ONLY=Yes \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-1
	cd ${.CURDIR} && exec ${MAKE} install COMPILER_ONLY=Yes \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-1
.endif
.if ${_LIBERTY_GIVEN} == "no"
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} cleandir
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} depend \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc CPP="${SUBOBJDIR}/bs-1/bin/mgcc -E"
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} all \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc CPP="${SUBOBJDIR}/bs-1/bin/mgcc -E"
.endif
	cd ${.CURDIR} && exec ${MAKE} cleandir-recursive COMPILER_ONLY=Yes
.if ${_LIBERTY_GIVEN} == "no"
	cd ${.CURDIR} && exec ${MAKE} all COMPILER_ONLY=Yes \
	    _LIBERTY=${GNU_LIBIBERTY_SRC}/obj/libiberty.a \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-2
	cd ${.CURDIR} && exec ${MAKE} install COMPILER_ONLY=Yes \
	    _LIBERTY=${GNU_LIBIBERTY_SRC}/obj/libiberty.a \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-2
.else
	cd ${.CURDIR} && exec ${MAKE} all COMPILER_ONLY=Yes \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-2
	cd ${.CURDIR} && exec ${MAKE} install COMPILER_ONLY=Yes \
	    CC=${SUBOBJDIR}/bs-1/bin/mgcc \
	    GCC_NATIVE=no GCC_PREFIX=${SUBOBJDIR}/bs-2
.endif
.if ${_LIBERTY_GIVEN} == "no"
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} cleandir
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} depend \
	    CC=${SUBOBJDIR}/bs-2/bin/mgcc CPP="${SUBOBJDIR}/bs-2/bin/mgcc -E"
	cd ${GNU_LIBIBERTY_SRC} && exec ${MAKE} all \
	    CC=${SUBOBJDIR}/bs-2/bin/mgcc CPP="${SUBOBJDIR}/bs-2/bin/mgcc -E"
.endif
	cd ${.CURDIR} && exec ${MAKE} cleandir-recursive COMPILER_ONLY=Yes
.if ${_LIBERTY_GIVEN} == "no"
	cd ${.CURDIR} && exec ${MAKE} all \
	    _LIBERTY=${GNU_LIBIBERTY_SRC}/obj/libiberty.a \
	    CC=${SUBOBJDIR}/bs-2/bin/mgcc \
	    CXX=${SUBOBJDIR}/bs-2/bin/g++
.else
	cd ${.CURDIR} && exec ${MAKE} all \
	    CC=${SUBOBJDIR}/bs-2/bin/mgcc \
	    CXX=${SUBOBJDIR}/bs-2/bin/g++
.endif
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} install

.PHONY: bootstrapbuild bootstrap do-bootstrap

.include <bsd.obj.mk>
