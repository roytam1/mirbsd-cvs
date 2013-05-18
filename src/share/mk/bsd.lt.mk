# $MirOS$

.if !defined(BSD_LT_MK)
BSD_LT_MK=1

LIBTOOL?=	libtool

.c.lo:
	${LIBTOOL} --tag=CC --mode=compile \
	    ${COMPILE.c} ${CFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.m.lo:
	${LIBTOOL} --tag=CC --mode=compile \
	    ${COMPILE.c} ${CFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.s.lo:
	${LIBTOOL} --tag=CC --mode=compile \
	    ${COMPILE.s} ${AFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.S.lo:
	${LIBTOOL} --tag=CC --mode=compile \
	    ${COMPILE.S} ${AFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}

.cc.lo:
	${LIBTOOL} --tag=CXX --mode=compile \
	    ${COMPILE.cc} ${CXXFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.C.lo:
	${LIBTOOL} --tag=CXX --mode=compile \
	    ${COMPILE.cc} ${CXXFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.cxx.lo:
	${LIBTOOL} --tag=CXX --mode=compile \
	    ${COMPILE.cc} ${CXXFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}
.cpp.lo:
	${LIBTOOL} --tag=CXX --mode=compile \
	    ${COMPILE.cc} ${CXXFLAGS_${.TARGET:.lo=.o}:M*} ${.IMPSRC}

.endif
