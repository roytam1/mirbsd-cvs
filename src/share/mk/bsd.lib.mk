# $MirOS: src/share/mk/bsd.lib.mk,v 1.38 2006/05/27 11:07:02 tg Exp $
# $OpenBSD: bsd.lib.mk,v 1.43 2004/09/20 18:52:38 espie Exp $
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
.  if ${RTLD_TYPE} == "dyld"
SHLIB_SONAME?=	lib${LIB}.${SHLIB_VERSION}.0.dylib
SHLIB_LINKS?=	lib${LIB}.${SHLIB_VERSION:R}.dylib lib${LIB}.dylib
.  elif ${RTLD_TYPE} == "GNU"
SHLIB_SONAME?=	lib${LIB}.so.${SHLIB_VERSION}.0
SHLIB_LINKS?=	lib${LIB}.so.${SHLIB_VERSION:R} lib${LIB}.so
.  else
SHLIB_SONAME?=	lib${LIB}.so.${SHLIB_VERSION}
.  endif
.  if ${OBJECT_FMT} == "PE"
SHLIB_FLAGS?=	-Wl,--image-base,$$((RANDOM % 0x1000 / 4 * 0x40000 + 0x40000000))
.  else
SHLIB_FLAGS?=	${PICFLAG}
.  endif
SHLIB_FLAGS+=	${LDFLAGS}
.  if (${OBJECT_FMT} == "ELF") || (${OBJECT_FMT} == "PE")
SHLIB_FLAGS+=	-Wl,-rpath,${LIBDIR} -Wl,-rpath-link,${DESTDIR}${LIBDIR}
.  endif
.endif
SHLIB_LINKS?=

.if !empty(SRCS:M*.C) || !empty(SRCS:M*.cc) || !empty(SRCS:M*.cxx)
LINKER?=	${CXX}
.else
LINKER?=	${CC}
.endif

.if defined(SHLIB_SONAME) && empty(SHLIB_SONAME)
.  undef SHLIB_SONAME
.  undef SHLIB_LINKS
.elif ${RTLD_TYPE} == "dyld"
LINK.shlib?=	${LINKER} ${CFLAGS} ${SHLIB_FLAGS} -dynamiclib \
		$$(${LORDER} ${SOBJS}|tsort -q) ${LDADD} \
		-compatibility_version ${SHLIB_VERSION} \
		-current_version ${SHLIB_VERSION}
.elif ${RTLD_TYPE} == "GNU"
LINK.shlib?=	${LINKER} ${CFLAGS} ${SHLIB_FLAGS} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) \
		-Wl,--start-group ${LDADD} -Wl,--end-group \
		-Wl,-h,${SHLIB_SONAME:R}
.else
LINK.shlib?=	${LINKER} ${CFLAGS} ${SHLIB_FLAGS} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) \
		-Wl,--start-group ${LDADD} -Wl,--end-group
.endif

.MAIN: all

# prefer .S to a .c, remove stuff not used in the BSD libraries.
# .so used for PIC object files.  .ln used for lint output files.
# .m for objective c files.
.SUFFIXES:
.SUFFIXES:	.out .o .so .S .s .c .m .cc .cxx .y .l .i .ln .m4

.c.o .m.o:
	@echo "${COMPILE.c} ${CFLAGS_${.TARGET:C/(g|s)o$/.o/}}" \
	    "${.IMPSRC} -o $@"
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.c.so .m.so:
	@echo "${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}}" \
	    "-DPIC ${PICFLAG} ${.IMPSRC} -o $@"
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    -DPIC ${PICFLAG} ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.c.ln:
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

.cc.o .cxx.o:
	@echo "${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}}" \
	    "${.IMPSRC} -o $@"
	@${COMPILE.cc}  ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.cc.so .cxx.so:
	@echo "${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}}" \
	    "-DPIC ${PICFLAG} ${.IMPSRC} -o $@"
	@${COMPILE.cc}  ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}} \
	    -DPIC ${PICFLAG} ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.S.o .s.o:
	@echo "${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} |" \
	    "${AS} -o $@"
	@${CPP} ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.S.so .s.so:
	@echo "${CPP} -DPIC ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} $< |" \
	    "${AS} ${ASPICFLAG} -o $@"
	@${CPP} -DPIC ${CPPFLAGS} ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} ${ASPICFLAG} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
CXXFLAGS+=	${CXXDIAGFLAGS}
.endif
.if !${COPTS:M-fhonour-copts} || !${CFLAGS:M-fhonour-copts}
CFLAGS+=	${COPTS}
.endif
CXXFLAGS+=	${CXXOPTS}
HOSTCFLAGS?=	${CFLAGS}

.if ${DEBUGLIBS:L} == "yes"
DEBUG?=		-g1
_DISCARD=	-X
.else
_DISCARD=	-x
.endif

_LIBS=		lib${LIB}.a

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

# If new-style debugging libraries are in effect, libFOO_pic.a
# contains debugging information - this is actually wanted.
SOBJS+=		${OBJS:.o=.so}
lib${LIB}_pic.a:: ${SOBJS}
	@echo building shared object ${LIB} library
	@rm -f lib${LIB}_pic.a
	@${AR} cq lib${LIB}_pic.a $$(${LORDER} ${SOBJS} | tsort -q)

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
LLIBS?=		-lc
llib-l${LIB}.ln: ${LOBJS}
	@echo building llib-l${LIB}.ln
	@rm -f llib-l${LIB}.ln
	@${LINT} -C${LIB} ${LOBJS} ${LLIBS}

.if !target(clean)
clean: _SUBDIRUSE
	rm -f a.out [Ee]rrs mklog core *.core ${CLEANFILES}
	rm -f lib${LIB}.a ${OBJS}
	rm -f lib${LIB}_pic.a lib${LIB}.so.*.* lib${LIB}{,.*}.dylib ${SOBJS}
	rm -f llib-l${LIB}.ln ${LOBJS}
.endif

cleandir: _SUBDIRUSE clean

.if defined(SRCS)
afterdepend: .depend
	@print '%g/^\([^\.]*\).o[ ]*:/s//\1.o \1.so:/\nwq' | ed -s .depend
.endif

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}.a ${DESTDIR}${LIBDIR}/
.  ifdef SHLIB_SONAME
.    if ${OBJECT_FMT} == "Mach-O"
	@echo Relinking dynamic ${LIB} library
	${LINK.shlib} -install_name ${LIBDIR}/${SHLIB_SONAME} -o ${SHLIB_SONAME}
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
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}_pic.a ${DESTDIR}${LIBDIR}/
.  endif
.  if ${NOLINT:L} == "no"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${SHAREMODE} \
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

.if !target(tags)
tags: ${.CURDIR}/tags

${.CURDIR}/tags: ${SRCS}
	ctags -w -f $@ ${.ALLSRC:N*.S:N*.s}
	egrep "^SYSENTRY(.*)|^ENTRY(.*)|^NENTRY(.*)|^FUNC(.*)|^SYSCALL(.*)" \
	    /dev/null ${.ALLSRC:M*.S} ${.ALLSRC:M*.s} | sed \
	    "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" >>$@
	sort -o $@ $@
.endif

.if ${NOMAN:L} == "no"
.  include <bsd.man.mk>
.endif

.include <bsd.obj.mk>
.include <bsd.dep.mk>
.include <bsd.subdir.mk>
.include <bsd.sys.mk>

.endif
