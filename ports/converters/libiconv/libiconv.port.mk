# $MirOS: ports/converters/libiconv/libiconv.port.mk,v 1.10 2006/08/26 23:33:46 tg Exp $
# $OpenBSD: iconv.port.mk,v 1.4 2001/11/27 17:44:04 brad Exp $

# This is equivalent to USE_MOTIF.
# Can be one of 'any', 'base', 'gnu', 'port' + 'oldm4'
USE_ICONV?=	any

.if ${USE_ICONV:L:Many}
.  if ${OStype} == "MirBSD"
.    if ${NOPIC:L} != "no"
USE_ICONV+=	port
.    elif ${OSver:R} < 8
USE_ICONV+=	port
.    elif ${OSver:R} == 8
.      if ${OSver:E} < 163
USE_ICONV+=	port
.      else
USE_ICONV+=	base
.      endif
.    else
USE_ICONV+=	base
.    endif
.  elif ${MACHINE_OS} == "Darwin"
USE_ICONV+=	base
.  else
USE_ICONV+=	port
.  endif
.endif

.if ${USE_ICONV:L:Mgnu}
.  if ${MACHINE_OS} == "Darwin"
USE_ICONV+=	base
.  else
USE_ICONV+=	port
.  endif
.endif

.if ${USE_ICONV:L:Mport}
# The RUN_DEPENDS entry is to ensure libiconv is installed. This is
# necessary so that we have charset.alias installed on static archs.
# Typically installed in PREFIX/lib.
LIB_DEPENDS+=	giconv::converters/libiconv
RUN_DEPENDS+=	:libiconv->=1.9.1-4:converters/libiconv
ICONV_PREFIX=	${LOCALBASE}/giconv
CONFIGURE_ENV+=	ICONV_PREFIX=${ICONV_PREFIX:Q}
LDFLAGS+=	-Wl,-rpath,${ICONV_PREFIX}
.elif ${USE_ICONV:L:Mbase}
ICONV_PREFIX=	/usr
.else
.  error USE_ICONV=${USE_ICONV:L} invalid
.endif

.if ${USE_ICONV:L:Moldm4}
_ICONV_M4FILE=	${PORTSDIR}/converters/libiconv/iconvold.m4
.else
_ICONV_M4FILE=	${PORTSDIR}/converters/libiconv/iconv.m4
.endif

_MODGNU_loop_hooks+=	m4f=; if [[ -f $$d/iconv.m4 ]]; then \
				m4f=$$d/iconv.m4; \
			elif [[ -f $$d/m4/iconv.m4 ]]; then \
				m4f=$$d/m4/iconv.m4; \
			elif [[ -f $$d/$$ACAUX/iconv.m4 ]]; then \
				m4f=$$d/$$ACAUX/iconv.m4; \
			elif [[ -f $$d/$$ACAUX/m4/iconv.m4 ]]; then \
				m4f=$$d/$$ACAUX/m4/iconv.m4; \
			fi; \
			[[ -z $$m4f ]] || cp ${_ICONV_M4FILE} $$m4f;
