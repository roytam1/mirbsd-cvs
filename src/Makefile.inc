# $MirOS: src/Makefile.inc,v 1.2 2005/03/19 13:41:27 tg Exp $

.ifndef _MODSRC_MAKEFILE_INC
_MODSRC_MAKEFILE_INC=1

_STCMD=		/bin/systrace -e -i -a
_STFILE_OBJ=	${BSDOBJDIR}/.policy.mk
_STFILE_SUB=	${SUBOBJDIR}/.policy.mk
_STFILE_DEST=	${DESTDIR}/.policy.mk
.if defined(CUSTOM_NO_SYSTRACE) && ${CUSTOM_NO_SYSTRACE:L} != "no"
_STCMD_OBJ=
_STCMD_SUB=
_STCMD_DEST=
_STCMD_HTMAN=
.else
_STCMD_OBJ=	${_STCMD} -f ${_STFILE_OBJ}
_STCMD_SUB=	${_STCMD} -f ${_STFILE_SUB}
_STCMD_DEST=	${_STCMD} -f ${_STFILE_DEST}
_STCMD_HTMAN=	${_STCMD} -f ${BSDOBJDIR}/htman/.policy.mk
.endif

.endif
