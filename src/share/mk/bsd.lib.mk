# $MirOS: src/share/mk/bsd.lib.mk,v 1.82 2009/08/30 22:06:40 tg Exp $
# $OpenBSD: bsd.lib.mk,v 1.43 2004/09/20 18:52:38 espie Exp $
# $NetBSD: bsd.lib.mk,v 1.67 1996/01/17 20:39:26 mycroft Exp $
# @(#)bsd.lib.mk	5.26 (Berkeley) 5/2/91

.if !defined(BSD_LIB_MK)
BSD_LIB_MK=1

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

.if ${LTMIRMAKE:L} == "yes"
.  include <bsd.lt.mk>
.endif

.if defined(SHLIB_MAJOR) && !empty(SHLIB_MAJOR) \
    && defined(SHLIB_MINOR) && !empty(SHLIB_MINOR)
SHLIB_VERSION=	${SHLIB_MAJOR}.${SHLIB_MINOR}
.elif exists(${.CURDIR}/shlib_version)
.  include "${.CURDIR}/shlib_version"
SHLIB_VERSION?=	${major}.${minor}
.endif

SHLIB_TYPE?=	DLL
.ifdef SHLIB_VERSION
.  if empty(SHLIB_VERSION) || (${SHLIB_VERSION} == ".")
.    undef SHLIB_VERSION
.  endif
.endif
.ifndef SHLIB_VERSION
SHLIB_TYPE=	none
.endif

.if defined(SHLIB_VERSION) && ${NOPIC:L} == "no"
.  if ${RTLD_TYPE} == "dyld"
.    if ${SHLIB_TYPE:L} == "plugin"
_OSX_TYPE=	-bundle -undefined dynamic_lookup
.      if ${SHLIB_VERSION} == "-"
# DyLD, unversioned plugin
SHLIB_SONAME?=	lib${LIB}.bundle
.      else
# DyLD, versioned plugin
SHLIB_SONAME?=	lib${LIB}.${SHLIB_VERSION}.0.bundle
.      endif
.    else
_OSX_TYPE=	-dynamiclib -undefined error
.      if ${SHLIB_VERSION} == "-"
# DyLD, unversioned DLL
SHLIB_SONAME?=	lib${LIB}.dylib
.      else
# DyLD, versioned DLL
SHLIB_SONAME?=	lib${LIB}.${SHLIB_VERSION}.0.dylib
SHLIB_LINKS?=	lib${LIB}.${SHLIB_VERSION:R}.dylib lib${LIB}.dylib
.      endif
.    endif
.  elif ${RTLD_TYPE} == "GNU"
.    if (${SHLIB_TYPE:L} == "plugin") && (${SHLIB_VERSION} == "-")
SHLIB_SONAME?=	lib${LIB}.so
.    else
SHLIB_SONAME?=	lib${LIB}.so.${SHLIB_VERSION}.0
.    endif
.    if ${SHLIB_TYPE:U} == "DLL"
SHLIB_LINKS?=	lib${LIB}.so.${SHLIB_VERSION:R} lib${LIB}.so
.    endif
.  else
.    if (${SHLIB_TYPE:L} == "plugin") && (${SHLIB_VERSION} == "-")
SHLIB_SONAME?=	lib${LIB}.so
.    else
SHLIB_SONAME?=	lib${LIB}.so.${SHLIB_VERSION}
.    endif
.  endif
.  if ${OBJECT_FMT} == "PE"
.    if ${SHLIB_TYPE:U} == "DLL"
SHLIB_FLAGS?=	-Wl,--image-base,$$((RANDOM % 0x1000 / 4 * 0x40000 + 0x40000000))
.    else
.      warning I do not know how to do plugins on Interix
.    endif
.  else
SHLIB_FLAGS?=	${PICFLAG}
.  endif
.  if (${SHLIB_TYPE:U} == "DLL") && (${RTLD_TYPE} != "dyld") && \
    (${LTMIRMAKE:L} != "yes")
# GNU or BSD, DLL
SHLIB_FLAGS+=	-Wl,--no-undefined
.    if ${LIB} != "c"
LDADD+=		-lc
.    endif
.  endif
SHLIB_FLAGS+=	${LDFLAGS}
.  if ${LTMIRMAKE:L} == "yes"
SHLIB_SONAME=	lib${LIB}.la
SHLIB_FLAGS+=	-rpath ${LIBDIR}
.  elif (${OBJECT_FMT} == "ELF") || (${OBJECT_FMT} == "PE")
SHLIB_FLAGS+=	-Wl,-rpath,${LIBDIR} -Wl,-rpath-link,${DESTDIR}${LIBDIR}
.  endif
.endif
SHLIB_LINKS?=

.if !empty(SRCS:M*.cc) || !empty(SRCS:M*.C) || \
    !empty(SRCS:M*.cxx) || !empty(SRCS:M*.cpp)
.  if ${LTMIRMAKE:L} == "yes"
LINKER?=	${LIBTOOL} --tag=CXX --mode=link ${CXX}
.  else
LINKER?=	${CXX}
.  endif
.elif !empty(SRCS:M*.F) || !empty(SRCS:M*.f)
.  if ${LTMIRMAKE:L} == "yes"
LINKER?=	${LIBTOOL} --tag=CC --mode=link ${FC}
.  else
LINKER?=	${FC}
.  endif
.else
.  if ${LTMIRMAKE:L} == "yes"
LINKER?=	${LIBTOOL} --tag=CC --mode=link ${CC}
.  else
LINKER?=	${CC}
.  endif
.endif

.if ${SHLIB_TYPE:L} == "plugin"
_LIBS_STATIC=	No
NOLINT=		Yes
.else
_LIBS_STATIC?=	Yes
.endif
.if ${NOPIC:L} == "no"
_LIBS_SHARED?=	Yes
.else
_LIBS_SHARED=	No
.endif

.if (${_LIBS_SHARED:L} != "yes") || (!defined(SHLIB_SONAME)) || \
    (defined(SHLIB_SONAME) && empty(SHLIB_SONAME))
.  undef SHLIB_SONAME
.  undef SHLIB_LINKS
.elif !defined(SHLIB_VERSION) || empty(SHLIB_VERSION)
.  error SHLIB_SONAME (${SHLIB_SONAME}) set, but SHLIB_VERSION unset
.elif ${LTMIRMAKE:L} == "yes"
.  if ${SHLIB_TYPE:L} == "plugin"
.    warning I do not know how to do plugins with LTMIRMAKE
.  endif
.  if ${SHLIB_VERSION} == "-"
# Libtool, unversioned DLLs
SHLIB_FLAGS+=	-avoid-version
.  else
# Libtool, versioned DLLs
# slow
#lt_current!=	print $$((${SHLIB_VERSION:R} + ${SHLIB_VERSION:E}))
lt_revision?=	0
#lt_age=	${SHLIB_VERSION:E}
#SHLIB_FLAGS+=	-version-info ${lt_current}:${lt_revision}:${lt_age}
SHLIB_FLAGS+=	-version-number ${SHLIB_VERSION:R}:${SHLIB_VERSION:E}:${lt_revision}
.  endif
.elif ${RTLD_TYPE} == "dyld"
.  if ${SHLIB_VERSION} == "-"
# DyLD, unversioned DLLs and plugins
LINK.shlib?=	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} ${_OSX_TYPE} \
		$$(${LORDER} ${SOBJS}|tsort -q) ${LDADD}
.  else
# DyLD, versioned DLLs and plugins
LINK.shlib?=	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} ${_OSX_TYPE} \
		$$(${LORDER} ${SOBJS}|tsort -q) ${LDADD} \
		-compatibility_version ${SHLIB_VERSION:R}.0 \
		-current_version ${SHLIB_VERSION}
.  endif
.elif ${RTLD_TYPE} == "GNU"
.  if ${SHLIB_VERSION} == "-"
# GNU, unversioned DLL or plugin
LINK.shlib?=	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) \
		-Wl,--start-group ${LDADD} -Wl,--end-group \
		-Wl,-soname,lib${LIB}.so
.  else
# GNU, versioned DLL or plugin
LINK.shlib?=	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) \
		-Wl,--start-group ${LDADD} -Wl,--end-group \
		-Wl,-soname,lib${LIB}.so.${SHLIB_VERSION:R}
.  endif
.else
# BSD, DLL or plugin
LINK.shlib?=	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} -shared \
		$$(${LORDER} ${SOBJS}|tsort -q) \
		-Wl,--start-group ${LDADD} -Wl,--end-group
.endif

.MAIN: all

# prefer .S to a .c, remove stuff not used in the BSD libraries.
# .so used for PIC object files.  .ln used for lint output files.
# .m for objective c files.
.SUFFIXES:
.SUFFIXES:	.out .o .so .lo .S .s .c .m .cc .C .cxx .cpp .y .l .i .ln .m4

.if ${SHLIB_TYPE:L} == "plugin"
.c.o .m.o:
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -DPIC ${PICFLAG} -o $@ $<

.cc.o .C.o .cxx.o .cpp.o:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET}:M*} -DPIC ${PICFLAG} -o $@ $<

.S.o .s.o:
	${COMPILE.S} ${AFLAGS_${.TARGET}:M*} -DPIC \
	    ${ASPICFLAG:S/^/-Wa,/} ${CFLAGS:M-[ID]*} ${AINC} -o $@ $<
.else
.c.o .m.o:
	@print -r -- ${COMPILE.c:Q} \
	    ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*:Q} ${.IMPSRC:Q} -o '$@'
	@${COMPILE.c} ${CFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*} \
	    ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.c.so .m.so:
	${COMPILE.c} ${CFLAGS_${.TARGET:.so=.o}:M*} -DPIC ${PICFLAG} -o $@ $<

.c.ln:
	env CC=${_ORIG_CC:Q} ${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} \
	    ${CPPFLAGS:M-[IDU]*} -i ${.IMPSRC}

.cc.o .C.o .cxx.o .cpp.o:
	@print -r -- ${COMPILE.cc:Q} \
	    ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*:Q} ${.IMPSRC:Q} -o '$@'
	@${COMPILE.cc} ${CXXFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*} \
	    ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.cc.so .C.so .cxx.so .cpp.so:
	${COMPILE.cc} ${CXXFLAGS_${.TARGET:.so=.o}:M*} -DPIC ${PICFLAG} -o $@ $<

.S.o .s.o:
	@print -r -- ${COMPILE.S:Q} \
	    ${AFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*:Q} ${CFLAGS:M-[ID]*:Q} \
	    ${AINC} ${.IMPSRC} -o '$@'
	@${COMPILE.S} ${AFLAGS_${.TARGET:C/\.(g|s)o$/.o/}:M*} \
	    ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} -o $@.o
	@${LD} ${_DISCARD} -r $@.o -o $@
	@rm -f $@.o

.S.so .s.so:
	${COMPILE.S} ${AFLAGS_${.TARGET:.so=.o}:M*} -DPIC \
	    ${ASPICFLAG:S/^/-Wa,/} ${CFLAGS:M-[ID]*} ${AINC} -o $@ $<
.endif

.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
CXXFLAGS+=	${CXXDIAGFLAGS}
.endif
.if !${COPTS:M-fhonour-copts} || !${CFLAGS:M-fhonour-copts}
CFLAGS+=	${COPTS}
.endif
CXXFLAGS+=	${CXXOPTS} -fno-omit-frame-pointer
HOSTCFLAGS?=	${CFLAGS}

.if ${DEBUGLIBS:L} == "yes"
.  if !${CFLAGS:M-g*}
CFLAGS+=	-g1 -fno-omit-frame-pointer
CXXFLAGS+=	-g1
.  endif
DEBUG?=		-g
_DISCARD=	-X
_SODISCARD=	-X
.elif ${RTLD_TYPE} == "dyld"
_DISCARD=	-X
_SODISCARD=	-X
.else
_DISCARD=	-x
_SODISCARD=	-g -x
.endif

_LIBS=
.if ${LTMIRMAKE:L} == "yes"
_LIBS+=		lib${LIB}.la
.else
.  if ${_LIBS_STATIC:L} == "yes"
_LIBS+=		lib${LIB}.a
.  endif
.  if ${_LIBS_SHARED:L} == "yes"
_LIBS+=		lib${LIB}_pic.a ${SHLIB_SONAME}
.  endif
.endif
.if ${NOLINT:L} == "no"
_LIBS+=		llib-l${LIB}.ln
.endif

all: ${_LIBS} _SUBDIRUSE

.if ${LTMIRMAKE:L} == "yes"
OBJS+=		${SRCS:N*.h:R:S/$/.lo/g}
.elif ${SHLIB_TYPE:L} != "plugin"
OBJS+=		${SRCS:N*.h:R:S/$/.o/g}
.endif
CLEANFILES+=	${SHLIB_LINKS}

.if ${LTMIRMAKE:L} == "yes"
lib${LIB}.la:: ${OBJS}
.  if defined(SHLIB_VERSION) && (${SHLIB_VERSION} != "-")
	@print -r building libtool ${LIB} library \(version ${SHLIB_VERSION}\)
.  else
	@print -r building libtool ${LIB} library
.  endif
	@rm -f lib${LIB}.la
	${LINKER} ${CFLAGS:M*} ${SHLIB_FLAGS} ${OBJS} ${LDADD} -o $@
.endif

.if ${SHLIB_TYPE:L} != "plugin"
lib${LIB}.a:: ${OBJS}
	@print -r building standard ${LIB} library
	@rm -f lib${LIB}.a
	@${AR} cq lib${LIB}.a $$(${LORDER} ${OBJS} | tsort -q)
.  if ${OBJECT_FMT} == "Mach-O"
	@${RANLIB} lib${LIB}.a
.  endif
.endif

# If new-style debugging libraries are in effect, libFOO_pic.a
# contains debugging information - this is actually wanted.
.if ${SHLIB_TYPE:L} == "plugin"
SOBJS+=		${SRCS:N*.h:R:S/$/.o/g}
.else
SOBJS+=		${OBJS:.o=.so}
.endif
lib${LIB}_pic.a:: ${SOBJS}
	@print -r building shared object ${LIB} library
	@rm -f lib${LIB}_pic.a
	@${AR} cq lib${LIB}_pic.a $$(${LORDER} ${SOBJS} | tsort -q)
.if ${OBJECT_FMT} == "Mach-O"
	@${RANLIB} lib${LIB}_pic.a
.endif

.if ${LTMIRMAKE:L} != "yes"
${SHLIB_SONAME}: ${CRTI} ${CRTBEGIN} ${SOBJS} ${DPADD} ${CRTEND} ${CRTN}
.  if defined(SHLIB_VERSION) && (${SHLIB_VERSION} != "-")
	@print -r building ${SHLIB_TYPE} ${LIB} \(version ${SHLIB_VERSION}\)
.  else
	@print -r building unversioned ${SHLIB_TYPE} ${SHLIB_SONAME}
.  endif
	@rm -f ${SHLIB_SONAME}
	${LINK.shlib} -o $@
.  for _i in ${SHLIB_LINKS}
	@rm -f ${_i}
	ln -s ${SHLIB_SONAME} ${_i} || cp ${SHLIB_SONAME} ${_i}
.  endfor
.endif

LOBJS+=		${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln} \
		${SRCS:M*.l:.l=.ln} ${SRCS:M*.y:.y=.ln}
LLIBS?=		-lc
llib-l${LIB}.ln: ${LOBJS}
	@print -r building llib-l${LIB}.ln
	@rm -f llib-l${LIB}.ln
	@env CC=${_ORIG_CC:Q} ${LINT} -C${LIB} ${LOBJS} ${LLIBS}

.for _i in ${SRCS:M*.l} ${SRCS:M*.y}
CLEANFILES+=	${_i:R}.c
.endfor
.if ${YFLAGS:M-d}
.  for _i in ${SRCS:M*.y}
CLEANFILES+=	${_i:R}.h
.  endfor
.endif

.if !target(clean)
clean: _SUBDIRUSE
.  if ${LTMIRMAKE:L} == "yes"
	-${LIBTOOL} --mode=clean rm *.la *.lo
.  endif
	rm -f a.out [Ee]rrs mklog core *.core ${CLEANFILES}
	rm -f lib${LIB}.a ${OBJS}
	rm -f lib${LIB}_pic.a lib${LIB}.so.*.* lib${LIB}{,.*}.dylib ${SOBJS}
	rm -f llib-l${LIB}.ln ${LOBJS}
.endif

cleandir: _SUBDIRUSE clean

.if defined(SRCS)
afterdepend: .depend
.  if ${LTMIRMAKE:L} == "yes"
	@print ',g/^\([^\.]*\).o[ ]*:/s//\1.o \1.lo:/\nwq' | ed -s .depend
.  else
	@print ',g/^\([^\.]*\).o[ ]*:/s//\1.o \1.so:/\nwq' | ed -s .depend
.  endif
.endif

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif

realinstall:
.  if ${LTMIRMAKE:L} == "yes"
	${LIBTOOL} --mode=install ${INSTALL} ${INSTALL_COPY} -m ${LIBMODE} \
	    -o ${LIBOWN} -g ${LIBGRP} lib${LIB}.la ${DESTDIR}${LIBDIR}/
.  else
.    if ${_LIBS_STATIC:L} == "yes"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}.a ${DESTDIR}${LIBDIR}/
.      if ${OBJECT_FMT} == "Mach-O"
	chmod 600 ${DESTDIR}${LIBDIR}/lib${LIB}.a
	${RANLIB} ${DESTDIR}${LIBDIR}/lib${LIB}.a
	chmod ${LIBMODE} ${DESTDIR}${LIBDIR}/lib${LIB}.a
.      endif
.    endif
.    ifdef SHLIB_SONAME
.      if (${OBJECT_FMT} == "Mach-O") && (${SHLIB_TYPE:L} != "plugin")
	@print -r Relinking dynamic ${LIB} library
	${LINK.shlib} -install_name ${LIBDIR}/${SHLIB_SONAME} -o ${SHLIB_SONAME}
.      endif
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m 600 \
	    ${SHLIB_SONAME} ${DESTDIR}${LIBDIR}/${SHLIB_SONAME}~
.      if !defined(MKC_DEBG) || ${MKC_DEBG:L} == "no"
	${STRIP} ${_SODISCARD} ${DESTDIR}${LIBDIR}/${SHLIB_SONAME}~
.      endif
	cd ${DESTDIR}${LIBDIR} && \
	    chmod ${LIBMODE} ${SHLIB_SONAME}~ && \
	    mv -f ${SHLIB_SONAME}~ ${SHLIB_SONAME}
.      for _i in ${SHLIB_LINKS}
	@rm -f ${DESTDIR}${LIBDIR}/${_i}
	cd ${DESTDIR}${LIBDIR}; \
	    ln -s ${SHLIB_SONAME} ${_i} || cp ${SHLIB_SONAME} ${_i}
.      endfor
.    elif ${_LIBS_SHARED:L} == "yes"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}_pic.a ${DESTDIR}${LIBDIR}/
.      if ${OBJECT_FMT} == "Mach-O"
	chmod 600 ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
	${RANLIB} ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
	chmod ${LIBMODE} ${DESTDIR}${LIBDIR}/lib${LIB}_pic.a
.      endif
.    endif
.  endif
.  if ${NOLINT:L} == "no"
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${SHAREMODE} \
	    llib-l${LIB}.ln ${DESTDIR}${LINTLIBDIR}/
.  endif
.  if defined(LINKS) && !empty(LINKS)
.    for lnk file in ${LINKS}
	@l=${DESTDIR}${lnk}; \
	 t=${DESTDIR}${file}; \
	 print -r -- $$t -\> $$l; \
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
	${CTAGS} -w -f $@ ${.ALLSRC:N*.S:N*.s}
	egrep "^SYSENTRY(.*)|^ENTRY(.*)|^NENTRY(.*)|^ALTENTRY(.*)|^FUNC(.*)|^SYSCALL(.*)" \
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
