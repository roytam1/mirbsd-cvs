# $MirOS$

.ifndef PORT_AMX_MAKEFILE_INC
PORT_AMX_MAKEFILE_INC=1

.include "../Makefile.inc"

CPPFLAGS+=	-DFLOATPOINT -DFIXEDPOINT

.if defined(NEED_AMXCONS) && ${NEED_AMXCONS:L} != "no"
SRCS+=		amxcons.c
USE_CURSES=	No

.  if ${USE_CURSES:L} == "yes"
CPPFLAGS+=	-DHAVE_CURSES_H -DUSE_CURSES
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses
.  else
SRCS+=		getch.c
.  endif
.endif

.if defined(SHLIB_VERSION)
_LIBS_STATIC=	No
LIBDIR=		${BSD_PREFIX}/libexec/pawn
.endif

.endif
