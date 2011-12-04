# $MirOS: src/share/mk/bsd.own.mk,v 1.13 2005/06/09 20:49:39 tg Exp $
# $OpenBSD: bsd.own.mk,v 1.84 2004/06/22 19:50:01 pvalchev Exp $
# $NetBSD: bsd.own.mk,v 1.24 1996/04/13 02:08:09 thorpej Exp $

.if !defined(BSD_OWN_MK)
BSD_OWN_MK=1

# Host-specific overrides
.if defined(MAKECONF) && exists(${MAKECONF})
.  include "${MAKECONF}"
.elif exists(/etc/mk.conf)
.  include "/etc/mk.conf"
.endif

CROSS_MODE?=	No
.if make(obj)
CROSS_MODE:=	No
.endif
.if ${CROSS_MODE:L} == "yes"
DEFFLAGS=	No
EXPERIMENTAL=	Yes
.endif

# Automatic CC/COPTS assignment system
DEFFLAGS?=	Yes

.if ${DEFFLAGS:L} != "no"
CC?=		mgcc
COPTS?=		${DEFCOPTS} ${GCEXTRA}
.  ifdef __CRAZY
WARNINGS=	yes
CFLAGS+=	-Wall -Wextra -Wunused -Wdeclaration-after-statement -Wundef \
		-Wendif-labels -Wshadow -Wpointer-arith -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes -Winline \
		-Wmissing-declarations -Wmissing-noreturn -pedantic \
		-Wmissing-format-attribute -Wredundant-decls -std=c99
.  endif
.endif

.if ${MACHINE} == "macppc"
CRTN?=		${DESTDIR}/usr/lib/ncrtn.o
.endif

# Set to yes to add CDIAGFLAGS to CFLAGS
WARNINGS?=		No
# Set to no to avoid building with support for S/key authentication
SKEY?=			Yes
# Set to yes to build debugging versions of shared libraries
DEBUGLIBS?=		No
# Set to yes for a stricter patent policy
MKC_USAP?=		No
# Set to sudo to automatically switch to root and only if needed
SUDO?=
# where the system object and source trees are kept; can be configurable
# by the user in case they want them in ~/foosrc and ~/fooobj, for example
BSDSRCDIR?=		/usr/src
BSDOBJDIR?=		/usr/obj
BSDRELDIR?=		/usr/releng
PORTSDIR?=		/usr/ports
# Shared files for system GNU configure and build process
GNUSYSTEM_AUX_DIR?=	${BSDSRCDIR}/gnu/share


BINGRP?=	bin
BINOWN?=	root
BINMODE?=	555
NONBINMODE?=	444
DIRMODE?=	755

SHAREDIR?=	/usr/share
SHAREGRP?=	${BINGRP}
SHAREOWN?=	${BINOWN}
SHAREMODE?=	${NONBINMODE}

MANDIR?=	/usr/share/man/cat
MANGRP?=	${SHAREGRP}
MANOWN?=	${SHAREOWN}
MANMODE?=	${NONBINMODE}

LIBDIR?=	/usr/lib
LINTLIBDIR?=	/usr/libdata/lint
LIBGRP?=	${BINGRP}
LIBOWN?=	${BINOWN}
LIBMODE?=	${NONBINMODE}

DOCDIR?=	/usr/share/doc
DOCGRP?=	${SHAREGRP}
DOCOWN?=	${SHAREOWN}
DOCMODE?=	${NONBINMODE}

LKMDIR?=	/usr/lkm
LKMGRP?=	${BINGRP}
LKMOWN?=	${BINOWN}
LKMMODE?=	${NONBINMODE}

INSTALL_COPY?=	-c
.ifndef	DEBUG
INSTALL_STRIP?=	-s
.else
INSTALL_STRIP?=
.endif

# This may be changed for _single filesystem_ configurations (such as
# routers and other embedded systems); normal systems should leave it alone!
STATIC?=	-static

# Define SYS_INCLUDE to indicate whether you want symbolic links to the system
# source (''symlinks''), or a separate copy (''copies''); (latter useful
# in environments where it's not possible to keep /sys publicly readable)
SYS_INCLUDE?=	copies

# don't try to generate PIC versions of libraries on machines
# which don't support PIC.
#.if (${MACHINE_ARCH} == "vax") || (${MACHINE_ARCH} == "m88k")
#NOPIC=		yes
#.endif

NOLINT?=	yes
NOMAN?=		no
NOOBJ?=		no
NOPIC?=		no

LDFLAGS?=
.if ${NOPIC:L} != "no" && !${LDFLAGS:M-static}
LDFLAGS+=	${STATIC}
.endif

# MirOS is always ELF for now, although the possible choices
# are: ELF a.out COFF Mach-O PE (consistent with nbsd)
.if ${OStype} == "Darwin"
OBJECT_FMT=	Mach-O
RTLD_TYPE=	dyld
.elif !empty(OStype:M*Interix)
OBJECT_FMT=	PE
RTLD_TYPE=	GNU
.else
OBJECT_FMT=	ELF
RTLD_TYPE=	BSD
.endif

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

# XXX fixme
PIC?=		cat --
BIB?=		cat --

BIB?=		bib
EQN?=		neqn
GREMLIN?=	grn
GRIND?=		vgrind -f
INDXBIB?=	indxbib
MKSH?=		/bin/mksh
NROFF?=		nrcon ${MACROS} ${PAGES}
PIC?=		pic
REFER?=		refer
ROFF?=		groff -Tps -M/usr/share/tmac ${MACROS} ${PAGES}
SOELIM?=	soelim
TBL?=		tbl

# this used to be in <bsd.prog.mk> but we need it
# e.g. for depending DLLs on CSU objects

.if ${OBJECT_FMT} == "ELF"
CRTBEGIN?=	${DESTDIR}/usr/lib/crtbegin.o
CRTEND?=	${DESTDIR}/usr/lib/crtend.o
CRTI?=		${DESTDIR}/usr/lib/crti.o
CRTN?=		${DESTDIR}/usr/lib/crtn.o
.  if defined(DESTDIR)
${CRTBEGIN} ${CRTEND} ${CRTI} ${CRTN}: .OPTIONAL .NOTMAIN
.  endif
.endif

LIBCRT0?=	${DESTDIR}/usr/lib/crt0.o
LIBC?=		${DESTDIR}/usr/lib/libc.a
LIBCDK?=	${DESTDIR}/usr/lib/libcdk.a
LIBCOMPAT?=	${DESTDIR}/usr/lib/libcompat.a
LIBCRYPTO?=	${DESTDIR}/usr/lib/libcrypto.a
LIBCURSES?=	${DESTDIR}/usr/lib/libcurses.a
LIBDES?=	${DESTDIR}/usr/lib/libdes.a
LIBEDIT?=	${DESTDIR}/usr/lib/libedit.a
LIBEVENT?=	${DESTDIR}/usr/lib/libevent.a
LIBEXPAT?=	${DESTDIR}/usr/lib/libexpat.a
LIBF2C?=	${DESTDIR}/usr/lib/libg2c.a
LIBFL?=		${DESTDIR}/usr/lib/libfl.a
LIBFORM?=	${DESTDIR}/usr/lib/libform.a
LIBFRTBEGIN?=	${DESTDIR}/usr/lib/libfrtbegin.a
LIBG2C?=	${DESTDIR}/usr/lib/libg2c.a
LIBGCC?=	${DESTDIR}/usr/lib/libgcc.a
LIBGPC?=	${DESTDIR}/usr/lib/libgpc.a
LIBKEYNOTE?=	${DESTDIR}/usr/lib/libkeynote.a
LIBKVM?=	${DESTDIR}/usr/lib/libkvm.a
LIBL?=		${DESTDIR}/usr/lib/libl.a
LIBM?=		${DESTDIR}/usr/lib/libm.a
LIBMENU?=	${DESTDIR}/usr/lib/libmenu.a
LIBMILTER?=	${DESTDIR}/usr/lib/libmilter.a
LIBOBJC?=	${DESTDIR}/usr/lib/libobjc.a
LIBOLDCURSES?=	${DESTDIR}/usr/lib/libocurses.a
LIBPANEL?=	${DESTDIR}/usr/lib/libpanel.a
LIBPCAP?=	${DESTDIR}/usr/lib/libpcap.a
LIBPERL?=	${DESTDIR}/usr/lib/libperl.a
LIBPNG?=	${DESTDIR}/usr/lib/libpng.a
LIBRPCSVC?=	${DESTDIR}/usr/lib/librpcsvc.a
LIBRX?=		${DESTDIR}/usr/lib/librx.a
LIBSECTOK?=	${DESTDIR}/usr/lib/libsectok.a
LIBSKEY?=	${DESTDIR}/usr/lib/libskey.a
LIBSSL?=	${DESTDIR}/usr/lib/libssl.a
LIBTERMCAP?=	${DESTDIR}/usr/lib/libtermcap.a
LIBTERMLIB?=	${DESTDIR}/usr/lib/libtermlib.a
LIBUSB?=	${DESTDIR}/usr/lib/libusbhid.a
LIBUTIL?=	${DESTDIR}/usr/lib/libutil.a
LIBWRAP?=	${DESTDIR}/usr/lib/libwrap.a
LIBY?=		${DESTDIR}/usr/lib/liby.a
LIBZ?=		${DESTDIR}/usr/lib/libz.a

.if (${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "amd64" || \
     ${MACHINE_ARCH} == "i386")
LIBARCH?=	${DESTDIR}/usr/lib/lib${MACHINE_ARCH}.a
.else
LIBARCH?=
.endif

# old stuff
LIBOSSAUDIO?=	${DESTDIR}/usr/lib/libossaudio.a
LIBOTERMCAP?=	${DESTDIR}/usr/lib/libotermcap.a
LIBRESOLV?=	${DESTDIR}/usr/lib/libresolv.a

.PHONY: spell clean cleandir obj manpages print all \
	depend beforedepend afterdepend cleandepend \
	all lint cleanman includes \
	beforeinstall realinstall maninstall afterinstall install

.endif
