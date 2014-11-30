# $MirOS: src/kern/c/Makefile.inc,v 1.30 2014/03/29 10:25:52 tg Exp $

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

# XSRCS, UIF_XSRCS:	kernel, userland, bootloader
# KXSRCS, UIF_KXSRCS:	kernel, libmbfun, bootloader
# KUSRCS, UIF_KUSRCS:	kernel, userland
# NUSRCS, UIF_NUSRCS:	userland
# LSRCS, UIF_LSRCS:	lint libraries (userland)

UIF_KUSRCS+=	timet2posix.c mirtime.c -DL_timet2posix
UIF_KUSRCS+=	posix2timet.c mirtime.c -DL_posix2timet
UIF_KUSRCS+=	timet2mjd.c mirtime.c -DL_timet2mjd
UIF_KUSRCS+=	mjd2timet.c mirtime.c -DL_mjd2timet
UIF_KUSRCS+=	mjd_explode.c mirtime.c -DL_mjd_explode
UIF_KUSRCS+=	mjd_implode.c mirtime.c -DL_mjd_implode
UIF_KUSRCS+=	mirtime_isleap.c mirtime.c -DL_mirtime_isleap
UIF_KUSRCS+=	mirtime_macrobodies.c mirtime.c -DL_mirtime_macrobodies

UIF_KUSRCS+=	mbsd_digits_dec.c miscdata.c -DL_mbsd_digits_dec
UIF_KUSRCS+=	mbsd_digits_hex.c miscdata.c -DL_mbsd_digits_hex
UIF_KUSRCS+=	mbsd_digits_HEX.c miscdata.c -DL_mbsd_digits_HEX
UIF_KUSRCS+=	mbsd_digits_base64.c miscdata.c -DL_mbsd_digits_base64
UIF_KUSRCS+=	RFC1321_padding.c miscdata.c -DL_RFC1321_padding
UIF_KUSRCS+=	mbsd_digits_md5crypt.c miscdata.c -DL_mbsd_digits_md5crypt
UIF_KUSRCS+=	mbsd_digits_bcrypt.c miscdata.c -DL_mbsd_digits_bcrypt

UIF_XSRCS+=	strlcpy.c strlfun.c -DL_strlcpy
UIF_XSRCS+=	strlcat.c strlfun.c -DL_strlcat
UIF_XSRCS+=	strxfrm.c strlfun.c -DL_strxfrm
UIF_NUSRCS+=	wcslcpy.c strlfun.c -DL_strlcpy,-DWIDEC
UIF_NUSRCS+=	wcslcat.c strlfun.c -DL_strlcat,-DWIDEC
UIF_NUSRCS+=	wcsxfrm.c strlfun.c -DL_strxfrm,-DWIDEC

UIF_NUSRCS+=	wcscmp.c strcmp.c -DWIDEC

UIF_XSRCS+=	strcasecmp.c strcasecmpfun.c -DSTRCASECMP
UIF_XSRCS+=	strncasecmp.c strcasecmpfun.c -DSTRNCASECMP
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
KUSRCS+=	optu16to8.c optu8to16.c

KUSRCS+=	arc4random_roundhash.c
KUSRCS+=	arc4random_uniform.c
KUSRCS+=	arcfour_base.c
KUSRCS+=	arcfour_ksa.c

KUSRCS+=	explicit_bzero.c
KUSRCS+=	timingsafe_bcmp.c

# …

.ifndef KERNSTAND
XSRCS+=		${KUSRCS}
UIF_XSRCS+=	${UIF_KUSRCS}
.endif

.ifdef KERNISUSR
XSRCS+=		${NUSRCS}
UIF_XSRCS+=	${UIF_NUSRCS}
.else
XSRCS+=		${KXSRCS}
UIF_XSRCS+=	${UIF_KXSRCS}
.endif

.for _z _q _s in ${UIF_XSRCS}
XSRCS+=		${_z}
.endfor
.for _z _q _s in ${UIF_LSRCS}
LSRCS+=		${_z}
.endfor
.for _z _q _s in ${UIF_XSRCS} ${UIF_LSRCS}
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
