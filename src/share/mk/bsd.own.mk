# $MirOS: src/share/mk/bsd.own.mk,v 1.63 2010/12/24 00:11:00 tg Exp $
# $OpenBSD: bsd.own.mk,v 1.92 2005/01/18 00:28:42 mickey Exp $
# $NetBSD: bsd.own.mk,v 1.24 1996/04/13 02:08:09 thorpej Exp $

.if !defined(BSD_OWN_MK)
BSD_OWN_MK=1

# Host-specific overrides
.if defined(MAKECONF) && exists(${MAKECONF})
.  include "${MAKECONF}"
.elif exists(/etc/${MAKE:T}.cfg)
.  include "/etc/${MAKE:T}.cfg"
.endif

SKEY?=		Yes	# no = avoid building with support for S/Key auth
DEBUGLIBS?=	Yes	# yes (snapshots), no (releases), removed (mirmake)
MALLOC_TYPE?=	omalloc	# default: omalloc, other: brk, mmap

CROSS_MODE?=	No
.if !make(obj) && (${CROSS_MODE:L} == "yes")
DEFFLAGS=	No
EXPERIMENTAL=	Yes
.endif

DEFFLAGS?=	Yes
.if ${DEFFLAGS:L} != "no"
COPTS?=		${_DEFCOPTS} ${GCEXTRA}
.else
COPTS?=		# at least define it
.endif

.ifdef __CRAZY
WARNINGS=	yes
CFLAGS+=	-Wall -Wextra -Wunused -Wdeclaration-after-statement -Wundef \
		-Wendif-labels -Wshadow -Wpointer-arith -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Winline \
		-Wmissing-declarations -Wmissing-noreturn -Winit-self \
		-Wmissing-format-attribute -Wredundant-decls
.endif

# Set to yes to add CDIAGFLAGS to CFLAGS
WARNINGS?=		No
# Set to yes to build shared libraries with basic debugging information
DEBUGLIBS?=		No	# yes, we have this twice
# Set to sudo to automatically switch to root and only if needed
SUDO?=
# where the system object and source trees are kept; can be configurable
# by the user in case they want them in ~/foosrc and ~/fooobj, for example
BSDSRCDIR?=		/usr/src
BSDOBJDIR?=		/usr/obj
BSDRELDIR?=		/usr/releng
# Shared files for system GNU configure and build process
GNUSYSTEM_AUX_DIR?=	${BSDSRCDIR}/gnu/share
LTMIRMAKE?=		No


BINOWN?=	root
BINGRP?=	bin
CONFGRP?=	wheel
BINMODE?=	555
NONBINMODE?=	444
DIRMODE?=	755

BSD_PREFIX?=	/usr

SHAREDIR?=	${BSD_PREFIX}/share
SHAREOWN?=	${BINOWN}
SHAREGRP?=	${BINGRP}
SHAREMODE?=	${NONBINMODE}

.if ${BSD_PREFIX} == "/usr"
MANDIR?=	${BSD_PREFIX}/share/man/cat
.else
MANDIR?=	${BSD_PREFIX}/man/cat
.endif
MANOWN?=	${SHAREOWN}
MANGRP?=	${SHAREGRP}
MANMODE?=	${NONBINMODE}

LIBDIR?=	${BSD_PREFIX}/lib
LINTLIBDIR?=	${BSD_PREFIX}/libdata/lint
LIBOWN?=	${BINOWN}
LIBGRP?=	${BINGRP}
LIBMODE?=	${NONBINMODE}

DOCDIR?=	${SHAREDIR}/doc
DOCOWN?=	${SHAREOWN}
DOCGRP?=	${SHAREGRP}
DOCMODE?=	${NONBINMODE}

LKMDIR?=	${BSD_PREFIX}/lkm
LKMOWN?=	${BINOWN}
LKMGRP?=	${BINGRP}
LKMMODE?=	${NONBINMODE}

NOLINT?=	yes
NOMAN?=		no
NOOBJ?=		no
NOPIC?=		no

LDFLAGS?=
.if ${NOPIC:L} != "no"
LDSTATIC=	-static
.endif

OBJECT_FMT=	ELF		# ELF a.out COFF Mach-O PE
RTLD_TYPE=	BSD		# dyld GNU BSD

.if ${OBJECT_FMT} == "Mach-O"
PICFLAG=	-fno-common
.elif ${OBJECT_FMT} == "PE"
PICFLAG=	# not needed; -fpic/-fPIC generates broken code
.elif (${MACHINE_ARCH} == "sparc") || (${MACHINE_ARCH} == "sparc64")
PICFLAG=	-fPIC
.else
PICFLAG=	-fpic
.endif

.if ${MACHINE_ARCH} == "sparc"
ASPICFLAG=	-KPIC
.elif ${OBJECT_FMT} == "a.out"
ASPICFLAG=	-k
.endif

INSTALL_COPY?=	-c
.ifndef DEBUG
.  if ${OBJECT_FMT} == "Mach-O"
INSTALL_STRIP?=
STRIP?=		strip -x
.  else
INSTALL_STRIP?=	-s
STRIP?=		strip
.  endif
.endif
INSTALL_STRIP?=
STRIP?=		:

# XXX fixme
PIC?=		cat --
BIB?=		cat --

BIB?=		bib
EQN?=		neqn
GREMLIN?=	grn
GRIND?=		vgrind -f
INDXBIB?=	indxbib
MKDEP_SH?=	mkdep
MKSH?=		/bin/mksh
NROFF?=		nrcon ${MACROS} ${PAGES}
PIC?=		pic
REFER?=		refer
ROFF?=		groff -Tps -P-p28c,21c ${MACROS} ${PAGES}
SOELIM?=	soelim
TBL?=		tbl

# this used to be in <bsd.prog.mk> but we need it
# e.g. for depending DLLs on CSU objects

.if ${OBJECT_FMT} == "ELF"
LIBCRT0?=	${DESTDIR}/usr/lib/crt0.o
CRTBEGIN?=	${DESTDIR}/usr/lib/crtbegin.o
CRTEND?=	${DESTDIR}/usr/lib/crtend.o
CRTI?=		${DESTDIR}/usr/lib/crti.o
CRTN?=		${DESTDIR}/usr/lib/crtn.o
.  if defined(DESTDIR)
${CRTBEGIN} ${CRTEND} ${CRTI} ${CRTN} ${LIBCRT0}: .OPTIONAL .NOTMAIN
.  endif
.endif
LIBC?=		${DESTDIR}/usr/lib/libc.a
LIBCOMPAT?=	${DESTDIR}/usr/lib/libcompat.a
LIBCRYPTO?=	${DESTDIR}/usr/lib/libcrypto.a
LIBCURSES?=	${DESTDIR}/usr/lib/libcurses.a
LIBDES?=	${DESTDIR}/usr/lib/libdes.a
LIBEDIT?=	${DESTDIR}/usr/lib/libedit.a
LIBEVENT?=	${DESTDIR}/usr/lib/libevent.a
LIBEXPAT?=	${DESTDIR}/usr/lib/libexpat.a
LIBFL?=		${DESTDIR}/usr/lib/libfl.a
LIBFORM?=	${DESTDIR}/usr/lib/libform.a
LIBICONV?=	${DESTDIR}/usr/lib/libiconv.a
LIBKEYNOTE?=	${DESTDIR}/usr/lib/libkeynote.a
LIBKVM?=	${DESTDIR}/usr/lib/libkvm.a
LIBL?=		${DESTDIR}/usr/lib/libl.a
LIBM?=		${DESTDIR}/usr/lib/libm.a
LIBMBFUN?=	${DESTDIR}/usr/lib/libmbfun.a
LIBMDSUP?=	${DESTDIR}/usr/lib/libmdsup.a
LIBMENU?=	${DESTDIR}/usr/lib/libmenu.a
LIBMILTER?=	${DESTDIR}/usr/lib/libmilter.a
LIBOLDCURSES?=	${DESTDIR}/usr/lib/libocurses.a
LIBOSSAUDIO?=	${DESTDIR}/usr/lib/libossaudio.a
LIBPANEL?=	${DESTDIR}/usr/lib/libpanel.a
LIBPCAP?=	${DESTDIR}/usr/lib/libpcap.a
LIBPERL?=	${DESTDIR}/usr/lib/libperl.a
LIBPNG?=	${DESTDIR}/usr/lib/libpng.a
LIBPTHREAD?=	${DESTDIR}/usr/lib/libpthread.a
LIBRPCSVC?=	${DESTDIR}/usr/lib/librpcsvc.a
LIBSECTOK?=	${DESTDIR}/usr/lib/libsectok.a
LIBSKEY?=	${DESTDIR}/usr/lib/libskey.a
LIBSSL?=	${DESTDIR}/usr/lib/libssl.a
LIBTERMCAP?=	${DESTDIR}/usr/lib/libtermcap.a
LIBTERMLIB?=	${DESTDIR}/usr/lib/libtermlib.a
LIBUSB?=	${DESTDIR}/usr/lib/libusbhid.a
LIBUTIL?=	${DESTDIR}/usr/lib/libutil.a
LIBY?=		${DESTDIR}/usr/lib/liby.a
LIBZ?=		${DESTDIR}/usr/lib/libz.a

.if ${MACHINE_ARCH} == "i386"
LIBARCH?=	${DESTDIR}/usr/lib/lib${MACHINE_ARCH}.a
.else
LIBARCH?=
.endif

# old stuff
LIBOSSAUDIO?=	${DESTDIR}/usr/lib/libossaudio.a

.PHONY: spell clean cleandir obj manpages print all \
	depend beforedepend afterdepend cleandepend \
	all lint cleanman includes \
	beforeinstall realinstall maninstall afterinstall install

.endif
