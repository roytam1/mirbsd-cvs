# $MirOS: src/Makefile.inc,v 1.1.7.1 2005/03/06 16:33:37 tg Exp $

.ifndef _MODSRC_MAKEFILE_INC
_MODSRC_MAKEFILE_INC=1

_STCMD=		/bin/systrace -e -i -a
_STFILE_OBJ=	${BSDOBJDIR}/.policy.mk
_STFILE_SUB=	${SUBOBJDIR}/.policy.mk
_STFILE_DEST=	${DESTDIR}/.policy.mk
_STCMD_OBJ=	${_STCMD} -f ${_STFILE_OBJ}
_STCMD_SUB=	${_STCMD} -f ${_STFILE_SUB}
_STCMD_DEST=	${_STCMD} -f ${_STFILE_DEST}

.endif
