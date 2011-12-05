# $MirOS: gcc/boehm-gc/tests/Makefile,v 1.2 2005/05/23 13:02:41 tg Exp $

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

CPPFLAGS+=	-lpthread
LDFLAGS+=	-lpthread

.  include <bsd.prog.mk>

.else

.  for _i in all clean cleandir depend obj
${_i}:
	cd ${.CURDIR} && make ${_i} TEST=1
	cd ${.CURDIR} && make ${_i} TEST=2
.  endfor

.endif
