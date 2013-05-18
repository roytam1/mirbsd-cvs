# $MirOS: src/share/man/automan.mk,v 1.1 2005/03/28 22:34:15 tg Exp $

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

.if exists(man$(MANSECT).${MACHINE})
SUBDIR+=	man$(MANSECT).${MACHINE}
.elif exists(man$(MANSECT).${MACHINE_ARCH})
SUBDIR+=	man$(MANSECT).${MACHINE_ARCH}
.endif

.endif
