# $MirOS$

.ifndef _MODSRC_SHARE_MAN_AUTOMAN_MK
_MODSRC_SHARE_MAN_AUTOMAN_MK=1

.if defined(MANSECT)
_MANR!=		cd ${.CURDIR} && echo *.$(MANSECT)
_MANT!=		cd ${.CURDIR} && echo *.$(MANSECT)tbl
_MANE!=		cd ${.CURDIR} && echo *.$(MANSECT)eqn
.  if ${_MANR} != "*.$(MANSECT)"
MAN+=		${_MANR}
.  endif
.  if ${_MANT} != "*.$(MANSECT)tbl"
MAN+=		${_MANT}
.  endif
.  if ${_MANE} != "*.$(MANSECT)eqn"
MAN+=		${_MANE}
.  endif
.endif

.endif
