# $MirOS: src/share/mk/sys.mk,v 1.114 2007/06/26 18:33:05 tg Exp $
# $OpenBSD: sys.mk,v 1.45 2005/03/07 00:06:00 deraadt Exp $
# $NetBSD: sys.mk,v 1.27 1996/04/10 05:47:19 mycroft Exp $
# @(#)sys.mk	5.11 (Berkeley) 3/13/91

.if !defined(_SYS_MK)
_SYS_MK=1

.if ${MACHINE_OS} == "BSD"
OStype=		MirBSD
.else
.  error MACHINE_OS (${MACHINE_OS}) unknown!
.endif

.if defined(EXTRA_SYS_MK_INCLUDES)
.  for _i in ${EXTRA_SYS_MK_INCLUDES}
.    include ${_i}
.  endfor
.endif

# Sync these with <sys/param.h>
unix=		We run ${OStype}.
OSrev=		10		# MirOS version (major)
OSrpl=		26		# MirOS patchlevel
OScompat=	3.5		# OpenBSD compatibility revision
.if !defined(OSNAME) || empty(OSNAME)
OSNAME!=	uname -s
.endif
OSname=		${OSNAME:L}
OStriplet?=	${MACHINE_ARCH}-ecce-${OSname}${OSrev}
_MIRMAKE_EXE=	/usr/bin/make
_MIRMAKE_VER=	20070628

.SUFFIXES:	.out .a .ln .o .s .S .c .m .cc .cxx .y .l .i .h .sh .m4
.LIBS:		.a

AR?=		ar
ARFLAGS?=	rl
RANLIB?=	ranlib
LORDER?=	lorder

AS?=		as
CC?=		mgcc
CPP?=		cpp
HOSTCC?=	mgcc

CPPFLAGS?=
PIPE?=		-pipe

AFLAGS?=	${DEBUG}
COMPILE.s?=	${CC} -D_ASM_SOURCE ${AFLAGS} -c
LINK.s?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${LDFLAGS}
COMPILE.S?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} -c
LINK.S?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} ${LDFLAGS}

CFLAGS?=	-O2 ${PIPE} ${DEBUG}
COMPILE.c?=	${CC} ${CFLAGS:M*} ${CPPFLAGS} -c
LINK.c?=	${CC} ${CFLAGS:M*} ${CPPFLAGS} ${LDFLAGS}

CXX?=		c++
CXXFLAGS?=	${CFLAGS}
COMPILE.cc?=	${CXX} ${CXXFLAGS:M*} ${CPPFLAGS} -c
LINK.cc?=	${CXX} ${CXXFLAGS:M*} ${CPPFLAGS} ${LDFLAGS}

LEX?=		lex
LFLAGS?=
LEX.l?=		${LEX} ${LFLAGS}

LD?=		ld
LDFLAGS+=	${DEBUG}

LINT?=		lint
LINTFLAGS?=	-chapbx

# MirOS make can use MirBSD ksh extensions per definitionem
SHELL=		/bin/mksh
MAKE?=		make

YACC?=		yacc
YFLAGS?=	-d
YACC.y?=	${YACC} ${YFLAGS}

INSTALL?=	install

CTAGS?=		/usr/bin/ctags

# C
.c:
	${LINK.c} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.c.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} ${.IMPSRC}
.c.i:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} -E ${.IMPSRC}
.c.a:
	${COMPILE.c} ${CFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.c.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} \
	    -i ${.IMPSRC}

# Objective-C
.m:
	${LINK.c} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.m.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} ${.IMPSRC}
.m.i:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} -E ${.IMPSRC}
.m.a:
	${COMPILE.c} ${CFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.m.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} \
	    -i ${.IMPSRC}

# C++
.cc:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cc.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.cc.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} -o ${.TARGET} -E ${.IMPSRC}
.cc.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.cxx:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cxx.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.cxx.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} -o ${.TARGET} -E ${.IMPSRC}
.cxx.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Assembly
.s:
	${LINK.s} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.s.o:
	${COMPILE.s} ${AFLAGS_${.TARGET}:M*} ${.IMPSRC}
.s.a:
	${COMPILE.s} ${AFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.S:
	${LINK.S} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.S.o:
	${COMPILE.S} ${AFLAGS_${.TARGET}:M*} ${.IMPSRC}
.S.i:
	${COMPILE.S} ${AFLAGS_${.TARGET}:M*} -o ${.TARGET} -E ${.IMPSRC}
.S.a:
	${COMPILE.S} ${AFLAGS_${.TARGET:S/.a$/.o/}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Lex
.l:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${LINK.c} -o ${.TARGET} ${.TARGET:R}.yy.c ${LDLIBS} -ll
	rm -f ${.TARGET:R}.yy.c
.l.c:
	${LEX.l} -o${.TARGET} ${.IMPSRC}
.l.o:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} ${.TARGET:R}.yy.c
	rm -f ${.TARGET:R}.yy.c

# Yacc
.y:
	${YACC.y} -o ${.TARGET:R}.tab.c ${.IMPSRC}
	${LINK.c} -o ${.TARGET} ${.TARGET:R}.tab.c ${LDLIBS}
	rm -f ${.TARGET:R}.tab.c
.y.c:
	${YACC.y} -o ${.TARGET} ${.IMPSRC}
.y.o:
	${YACC.y} -o ${.TARGET:R}.tab.c ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} ${.TARGET:R}.tab.c
	rm -f ${.TARGET:R}.tab.c

# Shell
.sh:
	rm -f ${.TARGET}
	cp ${.IMPSRC} ${.TARGET}

# Debugging output
.if defined(___DISPLAY_MAKEVARS)
${.TARGETS}: .MADE
	@:
.  if empty(.TARGETS)
.MAIN: ___display_makevars
___display_makevars::
.  else
.BEGIN:
.  endif
.  for _i in ${___DISPLAY_MAKEVARS}
	@print -r -- ${${_i}:Q}
.  endfor
.endif

.endif
