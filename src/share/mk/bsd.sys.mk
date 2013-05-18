# $MirOS: src/share/mk/bsd.sys.mk,v 1.15 2007/04/18 21:01:21 tg Exp $
# $OpenBSD: bsd.sys.mk,v 1.8 2000/07/06 23:12:41 millert Exp $
# $NetBSD: bsd.sys.mk,v 1.2 1995/12/13 01:25:07 cgd Exp $

.if !defined(BSD_SYS_MK)
BSD_SYS_MK=1

# The "if" is in case we want the current directory to have
# preference, due to gcc (GNU cpp, actually) brain-deadness
# The :N:S works around make idiocy, :M doesn't expand vars
.if ${CPPFLAGS:N0:S/-I${.CURDIR}/0/:M0} == ""
CPPFLAGS+=	-idirafter ${.CURDIR}
.endif

# The following is only wanted for source tree builds, not MirPorts
.if !defined(TRUEPREFIX) || empty(TRUEPREFIX)

.  if !defined(EXPERIMENTAL)
CFLAGS+=	-Werror
.    if !defined(BSD_CFWRAP_MK) && !make(depend)
CC:=		env GCC_HONOUR_COPTS=2 ${CC}
.    endif
.  endif

.  if defined(DESTDIR) && !empty(DESTDIR)
CPPFLAGS+=	-nostdinc -isystem ${DESTDIR}/usr/include
CXXFLAGS+=	-isystem ${DESTDIR}/usr/include/gxx \
		-isystem ${DESTDIR}/usr/include/gxx/${OStriplet} \
		-isystem ${DESTDIR}/usr/include/gxx/backward
.  endif

.endif

.endif
