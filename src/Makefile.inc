# $MirOS$

.ifndef _MODSRC_MAKEFILE_INC
_MODSRC_MAKEFILE_INC=1

_STCMD=		/bin/systrace -e -i -a
_STFILE_OBJ=	${BSDOBJDIR}/.policy.mk
_STFILE_FSF=	${FSFOBJDIR}/.policy.mk
_STFILE_DEST=	${DESTDIR}/.policy.mk
_STCMD_OBJ=	${_STCMD} -f ${_STFILE_OBJ}
_STCMD_FSF=	${_STCMD} -f ${_STFILE_FSF}
_STCMD_DEST=	${_STCMD} -f ${_STFILE_DEST}

.endif
