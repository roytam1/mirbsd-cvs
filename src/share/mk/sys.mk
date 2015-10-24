# $MirOS: src/share/mk/sys.mk,v 1.172 2015/07/19 01:04:20 tg Exp $
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
OSrpl=		183		# MirOS patchlevel
OScompat=	3.5		# OpenBSD compatibility revision
.if !defined(OSNAME) || empty(OSNAME)
OSNAME!=	uname -s
.endif
OSname=		${OSNAME:L}
OStriplet?=	${MACHINE_ARCH}-ecce-${OSname}${OSrev}
OSgccver?=	3.4.6
_MIRMAKE_EXE=	/usr/bin/make
_MIRMAKE_VER=	20100106

.SUFFIXES:	.out .a .ln .o .lo .s .S .c .m .cc .C .cxx .cpp .F .f .y .l .i .h .sh .m4
.LIBS:		.a

AR?=		ar
ARFLAGS?=	rl
RANLIB?=	ranlib
LORDER?=	lorder

AS?=		as
CC?=		mgcc
CPP?=		${CC} -E
HOSTCC?=	mgcc

CPPFLAGS?=
PIPE?=		-pipe

AFLAGS?=	${DEBUG}
COMPILE.s?=	${CC} -D_ASM_SOURCE ${AFLAGS} -c
LINK.s?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${LDFLAGS}
COMPILE.S?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} -c
LINK.S?=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} ${LDFLAGS}

CFLAGS?=	-O2 ${PIPE} -Wno-long-long ${DEBUG}
COMPILE.c?=	${CC} ${CFLAGS:M*} ${CPPFLAGS} -c
LINK.c?=	${CC} ${CFLAGS:M*} ${CPPFLAGS} ${LDFLAGS}

CXX?=		false
CXXFLAGS?=	${CFLAGS:N-std=c99:N-std=gnu99:N-Wno-long-long}
COMPILE.cc?=	${CXX} ${CXXFLAGS:M*} ${CPPFLAGS} -c
LINK.cc?=	${CXX} ${CXXFLAGS:M*} ${CPPFLAGS} ${LDFLAGS}

FC?=		false
FFLAGS?=	-O2
COMPILE.f?=	${FC} ${FFLAGS:M*} -c
LINK.f?=	${FC} ${FFLAGS:M*} ${LDFLAGS}
COMPILE.F?=	${FC} ${FFLAGS:M*} -D_ASM_SOURCE ${CPPFLAGS} -c
LINK.F?=	${FC} ${FFLAGS:M*} -D_ASM_SOURCE ${CPPFLAGS} ${LDFLAGS}

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

CTAGS?=		ctags

# C
.c:
	${LINK.c} -o $@ ${.IMPSRC} ${LDLIBS}
.c.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} ${.IMPSRC}
.c.i:
	${COMPILE.c} ${CFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.c.s:
	${COMPILE.c} ${CFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.c.a:
	${COMPILE.c} ${CFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.c.ln:
	env CC=${_ORIG_CC:Q} ${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} \
	    ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

# Objective-C
.m:
	${LINK.c} -o $@ ${.IMPSRC} ${LDLIBS}
.m.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} ${.IMPSRC}
.m.i:
	${COMPILE.c} ${CFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.m.s:
	${COMPILE.c} ${CFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.m.a:
	${COMPILE.c} ${CFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.m.ln:
	env CC=${_ORIG_CC:Q} ${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} \
	    ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

# C++
.cc:
	${LINK.cc} -o $@ ${.IMPSRC} ${LDLIBS}
.cc.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.cc.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.cc.s:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.cc.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.C:
	${LINK.cc} -o $@ ${.IMPSRC} ${LDLIBS}
.C.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.C.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.C.s:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.C.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.cxx:
	${LINK.cc} -o $@ ${.IMPSRC} ${LDLIBS}
.cxx.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.cxx.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.cxx.s:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.cxx.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.cpp:
	${LINK.cc} -o $@ ${.IMPSRC} ${LDLIBS}
.cpp.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} ${.IMPSRC}
.cpp.i:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.cpp.s:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.s=.o}:M*} -o $@ -S ${.IMPSRC}
.cpp.a:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Fortran
.f:
	${LINK.f} -o $@ ${.IMPSRC} ${LDLIBS}
.f.o:
	${COMPILE.f} ${FFLAGS_${.TARGET}:M*} ${.IMPSRC}
.f.a:
	${COMPILE.f} ${FFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.F:
	${LINK.F} -o $@ ${.IMPSRC} ${LDLIBS}
.F.o:
	${COMPILE.F} ${FFLAGS_${.TARGET}:M*} ${.IMPSRC}
.F.i:
	${COMPILE.F} ${FFLAGS_${.TARGET:.i=.o}:M*} -o $@ -E ${.IMPSRC}
.F.a:
	${COMPILE.F} ${FFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Assembly
.s:
	${LINK.s} -o $@ ${.IMPSRC} ${LDLIBS}
.s.o:
	${COMPILE.s} ${AFLAGS_${.TARGET}:M*} ${.IMPSRC}
.s.a:
	${COMPILE.s} ${AFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.S:
	${LINK.S} -o $@ ${.IMPSRC} ${LDLIBS}
.S.o:
	${COMPILE.S} ${AFLAGS_${.TARGET}:M*} ${.IMPSRC}
.S.s:
	${COMPILE.S} ${AFLAGS_${.TARGET:.s=.o}:M*} -o $@ -E ${.IMPSRC}
.S.a:
	${COMPILE.S} ${AFLAGS_${.TARGET:.a=.o}:M*} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Lex
.l:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${LINK.c} -o $@ ${.TARGET:R}.yy.c ${LDLIBS} -ll
	rm -f ${.TARGET:R}.yy.c
.l.c:
	${LEX.l} -o$@ ${.IMPSRC}
.l.o:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o $@ ${.TARGET:R}.yy.c
	rm -f ${.TARGET:R}.yy.c

# Yacc
.y:
	${YACC.y} -o ${.TARGET:R}.tab.c ${.IMPSRC}
	${LINK.c} -o $@ ${.TARGET:R}.tab.c ${LDLIBS}
	rm -f ${.TARGET:R}.tab.c
.y.c:
	${YACC.y} -o $@ ${.IMPSRC}
.y.o:
	${YACC.y} -o ${.TARGET:R}.tab.c ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o $@ ${.TARGET:R}.tab.c
	rm -f ${.TARGET:R}.tab.c

# Shell
.sh:
	rm -f $@
	cp ${.IMPSRC} $@
	chmod +x $@

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
.elif defined(___DUMP_MAKEVARS)
${.TARGETS}: .MADE
	@:
.  if empty(.TARGETS)
.MAIN: ___dump_makevars
___dump_makevars::
.  else
.BEGIN:
.  endif
.  for _i in ${___DUMP_MAKEVARS}
	@print -r -- ${_i:Q:Q}=${${_i}:Q:Q}
.  endfor
.endif

.endif
