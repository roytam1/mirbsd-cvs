# $MirOS: src/share/mk/sys.mk,v 1.10 2005/04/16 21:22:33 tg Exp $
# $OpenBSD: sys.mk,v 1.37 2004/04/05 19:17:25 miod Exp $
# $NetBSD: sys.mk,v 1.27 1996/04/10 05:47:19 mycroft Exp $
# @(#)sys.mk	5.11 (Berkeley) 3/13/91

.if !defined(_SYS_MK)
_SYS_MK=1

MACHINE_OS?=	unknown
.if ${MACHINE_OS} == "BSD"
OStype=		MirBSD
.elif ${MACHINE_OS} == "Linux"
OStype=		MirLinux
.else
ERRORS+=	Something fishy: $$MACHINE_OS unknown!
___DISPLAY_MAKEVARS+=ERRORS
OStype=		unknown
.endif

.if defined(EXTRA_SYS_MK_INCLUDES)
.  for _i in ${EXTRA_SYS_MK_INCLUDES}
.    include ${_i}
.  endfor
.endif

# Sync these with <sys/param.h>
unix=		We run ${OStype}.
OSrev=		8		# MirOS version (major)
OSrpl=		39		# MirOS patchlevel
OScompat=	3.5		# OpenBSD compatibility revision
.if !defined(OSNAME) || empty(OSNAME)
OSNAME!=	uname -s
.endif
OSname=		${OSNAME:L}
OStriplet?=	${MACHINE_ARCH}-ecce-${OSname}${OSrev}

.SUFFIXES:	.out .a .ln .o .s .S .c .m .cc .cxx .y .l .i .h .sh .m4
.LIBS:		.a

AR?=		ar
ARFLAGS?=	rl
RANLIB?=	ranlib
LORDER?=	lorder

AS?=		as
AFLAGS?=	${DEBUG}
COMPILE.s?=	${CC} ${AFLAGS} -c
LINK.s?=	${CC} ${AFLAGS} ${LDFLAGS}
COMPILE.S?=	${CC} ${AFLAGS} ${CPPFLAGS} -c
LINK.S?=	${CC} ${AFLAGS} ${CPPFLAGS} ${LDFLAGS}

CC?=		mgcc

CFLAGS?=	-O2 ${PIPE} ${DEBUG}
COMPILE.c?=	${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK.c?=	${CC} ${CFLAGS} ${CPPFLAGS} ${LDFLAGS}

HOSTCC?=	mgcc

CXX?=		c++
CXXFLAGS?=	${CFLAGS}
COMPILE.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c
LINK.cc?=	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LDFLAGS}

CPP?=		cpp
CPPFLAGS?=

# CPPOPTS are for the user to override/add, e.g. in mk.conf
CPPOPTS=	-isystem ${.CURDIR}
CPPFLAGS+=	${CPPOPTS}

LEX?=		lex
LFLAGS?=
LEX.l?=		${LEX} ${LFLAGS}

LD?=		ld
LDFLAGS+=	${DEBUG}

LINT?=		lint
LINTFLAGS?=	-chapbx

# MirOS can use mirbsdksh extensions per definitionem
SHELL=		/bin/ksh
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
	${COMPILE.c} ${CFLAGS_${.TARGET}} ${.IMPSRC}
.c.i:
	${COMPILE.c} -o ${.TARGET} -E ${.IMPSRC}
.c.a:
	${COMPILE.c} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.c.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} \
	    -i ${.IMPSRC}

# Objective-C
.m:
	${LINK.c} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.m.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}} ${.IMPSRC}
.m.i:
	${COMPILE.c} -o ${.TARGET} -E ${.IMPSRC}
.m.a:
	${COMPILE.c} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o
.m.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} \
	    -i ${.IMPSRC}

# C++
.cc:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cc.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}} ${.IMPSRC}
.cc.i:
	${COMPILE.cc} -o ${.TARGET} -E ${.IMPSRC}
.cc.a:
	${COMPILE.cc} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.cxx:
	${LINK.cc} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.cxx.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}} ${.IMPSRC}
.cxx.i:
	${COMPILE.cc} -o ${.TARGET} -E ${.IMPSRC}
.cxx.a:
	${COMPILE.cc} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Assembly
.s:
	${LINK.s} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.s.o:
	${COMPILE.s} ${ASFLAGS_${.TARGET}} ${.IMPSRC}
.s.a:
	${COMPILE.s} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

.S:
	${LINK.S} -o ${.TARGET} ${.IMPSRC} ${LDLIBS}
.S.o:
	${COMPILE.S} ${ASFLAGS_${.TARGET}} ${.IMPSRC}
.S.i:
	${COMPILE.S} -o ${.TARGET} -E ${.IMPSRC}
.S.a:
	${COMPILE.S} ${.IMPSRC}
	${AR} ${ARFLAGS} $@ $*.o
	rm -f $*.o

# Lex
.l:
	${LEX.l} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} lex.yy.c ${LDLIBS} -ll
	rm -f lex.yy.c
.l.c:
	${LEX.l} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}
.l.o:
	${LEX.l} ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}} -o ${.TARGET} lex.yy.c
	rm -f lex.yy.c

# Yacc
.y:
	${YACC.y} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} y.tab.c ${LDLIBS}
	rm -f y.tab.c
.y.c:
	${YACC.y} ${.IMPSRC}
	mv y.tab.c ${.TARGET}
.y.o:
	${YACC.y} ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}} -o ${.TARGET} y.tab.c
	rm -f y.tab.c

# Shell
.sh:
	rm -f ${.TARGET}
	cp ${.IMPSRC} ${.TARGET}

# Debugging output
.if defined(___DISPLAY_MAKEVARS)
.MAIN: ___display_makevars
.endif
___display_makevars: .PHONY .NOTMAIN
.for _i in ${___DISPLAY_MAKEVARS}
	@printf '%s\n' '${${_i}}'
.endfor

.endif
