# $MirOS: src/kern/c/Makefile.inc,v 1.21 2010/09/12 17:10:49 tg Exp $

.ifndef _KERNBASE_C_MAKEFILE_INC
_KERNBASE_C_MAKEFILE_INC=	#defined

# imports:
# ifdef(KERNSTAND)	-> bootloader, no kernel/libc only stuff
# ifdef(KERNISUSR)	-> user space
# ifdef(KERNNOGCC)	-> -fhosted -lgcc, no gcc replacement stuff
# ifdef(SMALL)		-> -DSMALL, prefer size over speed optimisation

.include "${KERNBASE}/Makefile.inc"

# md stuff must define sources for the following functions:
# htonl() htons() ntohl() ntohs()
# strlen() wcslen()
# bzero() ffs() memchr() memcmp()=bcmp() memcpy()=bcopy()=memmove() memset()
# strcmp()=strcoll()
# strchr()=index() strrchr()=rindex()
# strncmp() strncpy()

.include "${KERNBASE}/c/${MACHINE_ARCH}/Makefile.inc"

.PATH: ${KERNBASE}/c/${MACHINE_ARCH}
.PATH: ${KERNBASE}/c

# XSRCS, UNIFDEF_SRCS:	kernel, userland, bootloader
# KUSRCS, UIF_KUSRCS:	kernel, userland
# NUSRCS, UIF_NUSRCS:	userland
# LSRCS, UIF_LSRCS:	lint libraries (userland)

UIF_KUSRCS+=	tai_isleap.c taitime.c -DL_tai_isleap
UIF_KUSRCS+=	tai_timet2tai.c taitime.c -DL_timet2tai
UIF_KUSRCS+=	tai_tai2timet.c taitime.c -DL_tai2timet
UIF_KUSRCS+=	tai_utc2tai.c taitime.c -DL_utc2tai
UIF_KUSRCS+=	tai_tai2utc.c taitime.c -DL_tai2utc
UIF_KUSRCS+=	tai_mjd2tai.c taitime.c -DL_mjd2tai
UIF_KUSRCS+=	tai_tai2mjd.c taitime.c -DL_tai2mjd
UIF_KUSRCS+=	tai_mjd2tm.c taitime.c -DL_mjd2tm
UIF_KUSRCS+=	tai_tm2mjd.c taitime.c -DL_tm2mjd

UNIFDEF_SRCS+=	strlcpy.c strlfun.c -DL_strlcpy
UNIFDEF_SRCS+=	strlcat.c strlfun.c -DL_strlcat
UNIFDEF_SRCS+=	strxfrm.c strlfun.c -DL_strxfrm
UIF_NUSRCS+=	wcslcpy.c strlfun.c -DL_strlcpy,-DWIDEC
UIF_NUSRCS+=	wcslcat.c strlfun.c -DL_strlcat,-DWIDEC
UIF_NUSRCS+=	wcsxfrm.c strlfun.c -DL_strxfrm,-DWIDEC

UIF_NUSRCS+=	wcscmp.c strcmp.c -DWIDEC

UNIFDEF_SRCS+=	strcasecmp.c strcasecmpfun.c -DSTRCASECMP
UNIFDEF_SRCS+=	strncasecmp.c strcasecmpfun.c -DSTRNCASECMP
UIF_NUSRCS+=	wcscasecmp.c strcasecmpfun.c -DWCSCASECMP
UIF_NUSRCS+=	wcsncasecmp.c strcasecmpfun.c -DWCSNCASECMP

# quad support
XSRCS+=		adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c \
		iordi3.c lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c \
		notdi2.c qdivrem.c subdi3.c ucmpdi2.c udivdi3.c umoddi3.c \
		xordi3.c
KUSRCS+=	fixdfdi.c fixsfdi.c fixunsdfdi.c fixunssfdi.c \
		floatdidf.c floatdisf.c floatunsdidf.c

NUSRCS+=	__main.c

XSRCS+=		hdump.c
KUSRCS+=	oaat.c
KUSRCS+=	optu16to8.c optu8to16.c

KUSRCS+=	arc4random_roundhash.c
KUSRCS+=	arc4random_uniform.c
KUSRCS+=	arcfour_base.c
KUSRCS+=	arcfour_ksa.c
KUSRCS+=	arcfour_ksa256.c

# …

.ifndef KERNSTAND
XSRCS+=		${KUSRCS}
UNIFDEF_SRCS+=	${UIF_KUSRCS}
.endif

.ifdef KERNISUSR
XSRCS+=		${NUSRCS}
UNIFDEF_SRCS+=	${UIF_NUSRCS}
.endif

.for _z _q _s in ${UNIFDEF_SRCS}
XSRCS+=		${_z}
.endfor
.for _z _q _s in ${UIF_LSRCS}
LSRCS+=		${_z}
.endfor
.for _z _q _s in ${UNIFDEF_SRCS} ${UIF_LSRCS}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor

KERNPICKSRCS?=	No
.if ${KERNPICKSRCS:L} == "no"
SRCS+=		${XSRCS}
.endif

.endif
