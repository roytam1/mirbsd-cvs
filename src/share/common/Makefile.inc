# $MirOS$

.ifndef _MODSRC_SHARE_COMMON_MAKEFILE_INC
_MODSRC_SHARE_COMMON_MAKEFILE_INC=1

.PATH: ${BSDSRCDIR}/share/common
CPPFLAGS+=	-I${BSDSRCDIR}/share/common

.if ${MSMODS:Mambstowcs}
SRCS+=		ambstowcs.c
.endif

.endif
