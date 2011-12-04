# $MirOS: src/share/mk/bsd.lib.mk,v 1.13 2005/04/16 21:22:32 tg Exp $
# $OpenBSD: bsd.lib.mk,v 1.38 2004/06/22 19:50:01 pvalchev Exp $
# $NetBSD: bsd.lib.mk,v 1.67 1996/01/17 20:39:26 mycroft Exp $
# @(#)bsd.lib.mk	5.26 (Berkeley) 5/2/91

.if !defined(BSD_LIB_MK)
BSD_LIB_MK=1

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.if defined(SHLIB_MAJOR) && !empty(SHLIB_MAJOR) \
    && defined(SHLIB_MINOR) && !empty(SHLIB_MINOR)
SHLIB_VERSION=	${SHLIB_MAJOR}.${SHLIB_MINOR}
.elif exists(${.CURDIR}/shlib_version)
.  include "${.CURDIR}/shlib_version"
SHLIB_VERSION?=	${major}.${minor}
.endif

.ifdef SHLIB_VERSION
.  if empty(SHLIB_VERSION) || (${SHLIB_VERSION} == ".")
.    undef SHLIB_VERSION
.  endif
.endif

.if defined(SHLIB_VERSION) && ${NOPIC:L} == "no"
.  if ${OBJECT_FMT} == "Mach-O"
SHLIB_SONAME?=	lib${LIB}.${SHLIB_VERSION}.dylib
SHLIB_LINKS?=	lib${LIB}.${SHLIB_VERSION:R}.dylib lib${LIB}.dylib
.  else
SHLIB_SONAME?=	lib${LIB}.so.${SHLIB_VERSION}
.  endif
.endif
SHLIB_LINKS?=

.if defined(SHLIB_SONAME) && empty(SHLIB_SONAME)
.  undef SHLIB_SONAME
.  undef SHLIB_LINKS
.elif ${OBJECT_FMT} == "Mach-O"
LINK.shlib?=	${CC} ${CFLAGS} ${PICFLAG} -dynamiclib \
		-compatibility_version ${SHLIB_VERSION} \
		-current_version ${SHLIB_VERSION} \
		$$(${LORDER} ${SOBJS}|tsort -q) ${LDADD}
.else
LINK.shlib?=	${CC} ${CFLAGS} ${PICFLAG} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) ${LDADD}
.endif

.MAIN: all

# prefer .S to a .c, remove stuff not used in the BSD libraries.
# .so used for PIC object files.  .ln used for lint output files.
# .m for objective c files.
.SUFFIXES:
.SUFFIXES:	.out .o .go .so .S .s .c .m .cc .cxx .y .l .i .ln .m4

.c.o .m.o:
	@echo "${COMPILE.c} ${CFLAGS_${.TARGET:C/(g|s)o$/.o/}} " \
	    "${.IMPSRC} -o $@"
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${.IMPSRC} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.c.go .m.go:
	@echo "${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} " \
	    "-g ${.IMPSRC} -o $@"
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    -g ${.IMPSRC} -o $@.o
	@${LD} -X -r $@.o -o $@
	@rm -f $@.o

.c.so .m.so:
	@echo "${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} " \
	    "${PICFLAG} -DPIC ${.IMPSRC} -o $@"
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${PICFLAG} -DPIC ${.IMPSRC} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.c.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

.cc.o .cxx.o:
	@echo "${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} " \
	    "${.IMPSRC} -o $@"
	@${COMPILE.cc}  ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${.IMPSRC} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.cc.go .cxx.go:
	@echo "${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} " \
	    "-g ${.IMPSRC} -o $@"
	@${COMPILE.cc}  ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    -g ${.IMPSRC} -o $@.o
	@${LD} -X -r $@.o -o $@
	@rm -f $@.o

.cc.so .cxx.so:
	@echo "${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} " \
	    "${PICFLAG} -DPIC ${.IMPSRC} -o $@"
	@${COMPILE.cc}  ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${PICFLAG} -DPIC ${.IMPSRC} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.S.o .s.o:
	@echo "${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
		${AS} -o $@"
	@${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.S.go .s.go:
	@echo "${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} |\
	    ${AS} -o $@"
	@${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o $@.o
	@${LD} -X -r $@.o -o $@
	@rm -f $@.o

.S.so .s.so:
	@echo "${CPP} -DPIC ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} ${ASPICFLAG} -o $@"
	@${CPP} -DPIC ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} ${ASPICFLAG} -o $@.o
	@${LD} -x -r $@.o -o $@
	@rm -f $@.o

.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
CXXFLAGS+=	${CXXDIAGFLAGS}
.endif
CFLAGS+=	${COPTS}
CXXFLAGS+=	${CXXOPTS}

_LIBS=		lib${LIB}.a
.if ${DEBUGLIBS:L} == "yes"
_LIBS+=		lib${LIB}_g.a
.endif

.if ${NOPIC:L} == "no"
_LIBS+=		lib${LIB}_pic.a
.endif

.ifdef SHLIB_SONAME
_LIBS+=		${SHLIB_SONAME}
.endif

.if ${NOLINT:L} == "no"
_LIBS+=		llib-l${LIB}.ln
.endif

all: ${_LIBS} _SUBDIRUSE

OBJS+=		${SRCS:N*.h:R:S/$/.o/g}

lib${LIB}.a:: ${OBJS}
	@echo building standard ${LIB} library
	@rm -f lib${LIB}.a
	@${AR} cq lib${LIB}.a $$(${LORDER} ${OBJS} | tsort -q)
	${RANLIB} lib${LIB}.a

GOBJS+=		${OBJS:.o=.go}
lib${LIB}_g.a:: ${GOBJS}
	@echo building debugging ${LIB} library
	@rm -f lib${LIB}_g.a
	@${AR} cq lib${LIB}_g.a $$(${LORDER} ${GOBJS} | tsort -q)
	${RANLIB} lib${LIB}_g.a

SOBJS+=		${OBJS:.o=.so}
lib${LIB}_pic.a:: ${SOBJS}
	@echo building shared object ${LIB} library
	@rm -f lib${LIB}_pic.a
	@${AR} cq lib${LIB}_pic.a $$(${LORDER} ${SOBJS} | tsort -q)
	${RANLIB} lib${LIB}_pic.a

${SHLIB_SONAME}: ${SOBJS} ${CRTBEGIN} ${CRTEND} ${CRTI} ${CRTN} ${DPADD}
.if defined(SHLIB_VERSION)
	@echo building shared ${LIB} library \(version ${SHLIB_VERSION}\)
.else
	@echo building shared library ${SHLIB_SONAME}
.endif
	@rm -f ${SHLIB_SONAME}
	${LINK.shlib} -o $@
.for _i in ${SHLIB_LINKS}
	@rm -f ${_i}
	ln -s ${SHLIB_SONAME} ${_i} || cp ${SHLIB_SONAME} ${_i}
.endfor

LOBJS+=		${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln}
# the following looks XXX to me... -- cgd
LLIBS?=		-lc
llib-l${LIB}.ln: ${LOBJS}
	@echo building llib-l${LIB}.ln
	@rm -f llib-l${LIB}.ln
	@${LINT} -C${LIB} ${LOBJS} ${LLIBS}

.if !target(clean)
clean: _SUBDIRUSE
	rm -f a.out [Ee]rrs mklog core *.core ${CLEANFILES}
	rm -f lib${LIB}.a ${OBJS}
	rm -f lib${LIB}_g.a ${GOBJS}
	rm -f lib${LIB}_pic.a lib${LIB}.so.*.* lib${LIB}{,.*}.dylib ${SOBJS}
	rm -f llib-l${LIB}.ln ${LOBJS}
.endif

cleandir: _SUBDIRUSE clean

.if defined(SRCS)
afterdepend: .depend
	@(TMP=$$(mktemp -q /tmp/_dependXXXXXXXXXX); \
	  if [ $$? -ne 0 ]; then \
		echo "$$0: cannot create temp file, exiting..."; \
		exit 1; \
	  fi; \
	  sed -e 's/^\([^\.]*\).o[ ]*:/\1.o \1.so:/' \
	    <.depend >$$TMP; mv $$TMP .depend)
.endif

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m 600 lib${LIB}.a \
	    ${DESTDIR}${LIBDIR}/
.  if ${INSTALL_COPY} != "-p"
	${RANLIB} -t ${DESTDIR}${LIBDIR}/lib${LIB}.a
.  endif
	chmod ${LIBMODE} ${DESTDIR}${LIBDIR}/lib${LIB}.a
.  if ${DEBUGLIBS:L} == "yes"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m 600 \
	    lib${LIB}_g.a ${DESTDIR}${LIBDIR}/debug/lib${LIB}.a
.    if ${INSTALL_COPY} != "-p"
	${RANLIB} -t ${DESTDIR}${LIBDIR}/debug/lib${LIB}.a
.    endif
	chmod ${LIBMODE} ${DESTDIR}${LIBDIR}/debug/lib${LIB}.a
.  endif
.  ifdef SHLIB_SONAME
.    if ${OBJECT_FMT} == "Mach-O"
	@echo Relinking dynamic ${LIB} library
	${LINK.shlib} -install_name ${LIBDIR}/${SHLIB_SONAME} \
	    -o ${SHLIB_SONAME}
.    endif
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    ${SHLIB_SONAME} ${DESTDIR}${LIBDIR}/
.    for _i in ${SHLIB_LINKS}
	@rm -f ${DESTDIR}${LIBDIR}/${_i}
	cd ${DESTDIR}${LIBDIR} && if ! ln -s ${SHLIB_SONAME} ${_i}; then \
		cp ${SHLIB_SONAME} ${_i}; \
	fi
.    endfor
.  elif ${NOPIC:L} == "no"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m 600 \
	    lib${LIB}_pic.a ${DESTDIR}${LIBDIR}/
.    if ${INSTALL_COPY} != "-p"
	${RANLIB} -t ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.    endif
	chmod ${LIBMODE} ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.  endif
.  if ${NOLINT:L} == "no"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    llib-l${LIB}.ln ${DESTDIR}${LINTLIBDIR}/
.  endif
.  if defined(LINKS) && !empty(LINKS)
.    for lnk file in ${LINKS}
	@l=${DESTDIR}${lnk}; \
	 t=${DESTDIR}${file}; \
	 echo $$t -\> $$l; \
	 rm -f $$t; ln $$l $$t || cp $$l $$t
.    endfor
.  endif

install: maninstall _SUBDIRUSE
maninstall: afterinstall
afterinstall: realinstall
realinstall: beforeinstall
.endif	# not target install

.if ${NOMAN:L} == "no"
.  include <bsd.man.mk>
.endif

.include <bsd.obj.mk>
.include <bsd.dep.mk>
.include <bsd.subdir.mk>
.include <bsd.sys.mk>

.endif
