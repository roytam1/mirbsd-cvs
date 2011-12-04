# $MirOS: gcc/boehm-gc/tests/Makefile,v 1.1 2005/05/14 17:43:46 tg Exp $

.ifdef TEST

.  if ${TEST} == "1"
PROG=		gctest
.  else
PROG=		threads
.  endif
NOMAN=		yes
REALOBJDIR!=	readlink -f ${.OBJDIR}
LDADD=		${REALOBJDIR}/../.libs/libgcjgc.a
DPADD=		${REALOBJDIR}/../.libs/libgcjgc.la
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
