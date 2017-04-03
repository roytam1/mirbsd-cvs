# $MirOS: src/share/mk/bsd.sys.mk,v 1.24 2009/12/13 00:32:21 tg Exp $
# $OpenBSD: bsd.sys.mk,v 1.8 2000/07/06 23:12:41 millert Exp $
# $NetBSD: bsd.sys.mk,v 1.2 1995/12/13 01:25:07 cgd Exp $

.if !defined(BSD_SYS_MK)
BSD_SYS_MK=1

# just in case...
.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

# The "if" is in case we want the current directory to have
# preference, due to gcc (GNU cpp, actually) brain-deadness
# The :N:S works around make idiocy, :M doesn't expand vars
.if ${CPPFLAGS:N1:S-I${.CURDIR}1:M1} == ""
CPPFLAGS+=	-idirafter ${.CURDIR}
.endif

.if ${OBJECT_FMT} == "ELF"						#mmk-1(
LDFLAGS+=	-Wl,-O2		# optimise hash table
.endif\
									#mmk-1)
# The following is only wanted for source tree builds, not MirPorts
.if !defined(TRUEPREFIX) || empty(TRUEPREFIX)

.  if !defined(EXPERIMENTAL)						#mmk-2(
CFLAGS+=	-Werror
.    if !defined(BSD_CFWRAP_MK) && !make(depend)
_ORIG_CC:=	${CC}
CC:=		env GCC_HONOUR_COPTS=2 ${CC}
.    endif
.  endif								#mmk-2)
_ORIG_CC?=	${CC}

.  if defined(DESTDIR) && !empty(DESTDIR)				#mmk-3(
CPPFLAGS+=	-nostdinc
CPPFLAGS+=	-isystem ${DESTDIR}/usr/include
LDFLAGS+=	-Wl,-rpath-link -Wl,${DESTDIR}/usr/lib
.  endif\
									#mmk-3)
.endif

.if (!target(includes) || defined(BSD_SUBDIR_MK_NOINCLUDES)) && \
    (defined(BSD_PROG_MK) || defined(BSD_LIB_MK)) && \
    (defined(HDRS) || defined(HDRS2))
HDRSRC?=	${.CURDIR}
HDRDST?=	${DESTDIR}${BSD_PREFIX}/include

afterincludes:
includes: _includes afterincludes

.PHONY: _includes afterincludes

_includes:
.  ifdef HDRS
	@cd ${HDRSRC:Q}; for i in ${HDRS}; do \
		j=$${i##*/}; \
		if cmp -s "$$i" ${HDRDST:Q}/"$$j"; then \
			print Header ${HDRDST:Q}/"$$j <=> $$i"; \
		else \
			print Header ${HDRDST:Q}/"$$j <-- $$i"; \
			${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
			    -m ${NONBINMODE} "$$i" ${HDRDST:Q}/; \
		fi; \
	done
.  endif
.  ifdef HDRS2
.    for _i _j in ${HDRS2}
	@if cmp -s ${HDRSRC:Q}/${_i:Q} ${HDRDST:Q}/${_j:Q}; then \
		print Header ${HDRDST:Q}/${_j:Q} '<=>' ${_i:Q}; \
	else \
		print Header ${HDRDST:Q}/${_j:Q} '<--' ${_i:Q}; \
		${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
		    -m ${NONBINMODE} ${HDRSRC:Q}/${_i:Q} ${HDRDST:Q}/${_j:Q}; \
	fi
.    endfor
.  endif
.endif

.endif	# ! BSD_SYS_MK
