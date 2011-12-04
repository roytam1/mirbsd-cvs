# $MirOS$

.ifdef TEST

.  if ${TEST} == "1"
PROG=		gctest
.  else
PROG=		threads
.  endif
NOMAN=		yes
REALOBJDIR!=	readlink -f ${.OBJDIR}
LDADD=		${REALOBJDIR}/../.libs/libgcjgc.a
CPPFLAGS+=	-I${.CURDIR}/../include

CPPFLAGS+=	-pthread
LDFLAGS+=	-pthread

.  include <bsd.prog.mk>

.else

.  for _i in all clean cleandir depend obj
${_i}:
	cd ${.CURDIR} && make ${_i} TEST=1
	cd ${.CURDIR} && make ${_i} TEST=2
.  endfor

.endif
