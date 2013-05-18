# $MirOS: src/lib/csu/Makefile.inc,v 1.2 2005/10/21 11:02:39 tg Exp $

.ifndef _MODSRC_LIB_CSU_MAKEFILE_INC
_MODSRC_LIB_CSU_MAKEFILE_INC=1

.include <bsd.own.mk>
COPTS+=		-Wall

HAVE_VERSION_SPECIFIC_GCC_LIBS= #defined

.endif
