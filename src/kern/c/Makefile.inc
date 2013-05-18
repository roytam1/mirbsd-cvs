# $MirOS: src/kern/c/Makefile.inc,v 1.16 2008/12/28 05:10:30 tg Exp $

.ifndef _KERNBASE_C_MAKEFILE_INC
_KERNBASE_C_MAKEFILE_INC=	#defined

# imports:
# ifdef(KERNSTAND)	-> bootloader, no kernel/libc only stuff
# ifdef(KERNNOGCC)	-> -fhosted -lgcc, no gcc replacement stuff
# ifdef(SMALL)		-> -DSMALL, prefer size over speed optimisation

.include "${KERNBASE}/Makefile.inc"

# md stuff must define sources for the following functions:
# htonl() htons() ntohl() ntohs()
# strlen() wcslen()
# bzero() ffs() memchr() memcmp()=bcmp() memcpy()=bcopy()=memmove() memset()
# strcmp()=strcoll()

.include "${KERNBASE}/c/${MACHINE_ARCH}/Makefile.inc"

.PATH: ${KERNBASE}/c/${MACHINE_ARCH}
.PATH: ${KERNBASE}/c

# XSRCS, UNIFDEF_SRCS:	kernel, userland, bootloader
# KUSRCS, UIF_KUSRCS:	kernel, userland
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
UIF_KUSRCS+=	wcslcpy.c strlfun.c -DL_strlcpy,-DWIDEC
UIF_KUSRCS+=	wcslcat.c strlfun.c -DL_strlcat,-DWIDEC
UIF_KUSRCS+=	wcsxfrm.c strlfun.c -DL_strxfrm,-DWIDEC

UIF_KUSRCS+=	wcscmp.c strcmp.c -DWIDEC

# quad support
XSRCS+=		adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c \
		iordi3.c lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c \
		notdi2.c qdivrem.c subdi3.c ucmpdi2.c udivdi3.c umoddi3.c \
		xordi3.c
KUSRCS+=	fixdfdi.c fixsfdi.c fixunsdfdi.c fixunssfdi.c \
		floatdidf.c floatdisf.c floatunsdidf.c

.ifndef KERNNOGCC
XSRCS+=		__main.c
.endif

XSRCS+=		hdump.c
KUSRCS+=	optu16to8.c optu8to16.c

# …

.ifndef KERNSTAND
XSRCS+=		${KUSRCS}
UNIFDEF_SRCS+=	${UIF_KUSRCS}
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
