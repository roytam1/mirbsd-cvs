# $MirOS: gcc/Makefile,v 1.5 2005/04/26 21:15:29 tg Exp $

.include <bsd.own.mk>
.include "${BSDSRCDIR}/Makefile.inc"

SUBOBJDIR!=	readlink ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )

IGNORE_TGTS=	obj
BUILD_TGTS=	all clean depend lint prereq tags
INSTALL_TGTS=	includes install

EXTRA_ENV=	PATH=/bin:/usr/bin:/sbin:/usr/sbin

.MAIN: all

.for _i in ${IGNORE_TGTS}
${_i}:
	cd ${.CURDIR} && ${EXTRA_ENV} exec ${MAKE} -f Makefile.sub $@
.endfor

.for _i in ${BUILD_TGTS}
${_i}: ${_STFILE_SUB}
	ulimit -dS 245760 && cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_SUB} ${MAKE} -f Makefile.sub $@
.endfor

.for _i in ${INSTALL_TGTS}
${_i}:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}
	cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_DEST} ${MAKE} -f Makefile.sub $@
	sleep 1; ${SUDO} rm -f ${_STFILE_DEST}
.endfor

${_STFILE_SUB}:
	cd ${SUBOBJDIR} && env WRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

cleandir-recursive: ${_STFILE_SUB}
	cd ${.CURDIR} && ${EXTRA_ENV} exec \
	    ${_STCMD_SUB} ${MAKE} -f Makefile.sub cleandir

cleandir: cleandir-recursive local-cleandir

local-cleandir: .PHONY
	-sleep 1; rm -f ${_STFILE_SUB}

b-r: .PHONY
	# Test if the targets are mounted suitable for root (BTSTF)
.for _dir in ${BSDOBJDIR} ${BSDRELDIR}
	mkdir -p ${_dir} || ${SUDO} mkdir -p ${_dir}
	${SUDO} touch ${_dir}/permissions.test
	${SUDO} chown root:wheel ${_dir}/permissions.test
	${SUDO} rm ${_dir}/permissions.test
.endfor
	touch ${BSDOBJDIR}/permissions.test && rm ${BSDOBJDIR}/permissions.test
	cd ${.CURDIR} && exec ${MAKE} obj
	cd ${.CURDIR} && exec ${MAKE}
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} install
	cd ${.CURDIR} && exec ${MAKE} release BSDRELDIR=${BSDRELDIR}

release: .PHONY
	mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel \
	    || ${SUDO} mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel
	cd ${BSDSRCDIR} && ${EXTRA_ENV} exec \
	    ${MAKE} distrib-dirs mksystrace-dest DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} install DESTDIR=${BSDRELDIR}/base

.include <bsd.obj.mk>
