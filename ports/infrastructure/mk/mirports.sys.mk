# $MirOS: ports/infrastructure/mk/mirports.sys.mk,v 1.10.2.3 2005/08/21 12:41:20 tg Exp $

.ifndef	MIRPORTS_SYS_MK

# First, let's have a look at what the OS says.
.ifndef	BSD_OWN_MK
.  include <bsd.own.mk>
.endif

# But provide a consistent MirPorts behaviour.
DEBUGLIBS=		No

# Basic defaults.
.ifndef	OSname
OSNAME!=		uname -s
OSname=			${OSNAME:L}
.endif
PORTSDIR?=		/usr/ports

# Do we have overrides?
.if exists(${PORTSDIR}/infrastructure/mk/mirports.osdep.mk)
.  include "${PORTSDIR}/infrastructure/mk/mirports.osdep.mk"
.endif

.if ${OSNAME} == "MirBSD"
.  if (${OSrev} == 8) && (${OSrpl} < 40)
HAS_CXX=		reason
NO_CXX=			C++ is still broken, please update
.  endif
.endif

# Let's assume a sane environment now.
_MIRPORTS_ADDRESS=	<miros-discuss@MirBSD.org>
ARCH?=			${MACHINE_ARCH}
NOPIC_PLATFORMS?=
LP64_PLATFORMS?=	*:*:alpha *:*:amd64 *:*:sparc64
LOCALBASE?=		/usr/mpkg
SYSCONFDIR?=		/etc		# comment out for co-existence
SYSCONFDIR?=		${LOCALBASE}/etc
X11BASE?=		/usr/X11R6	# may be subject to change
MKSH?=			/bin/mksh	# path to mirbsdksh
MMAKE?=			/usr/bin/make	# path to mirmake
SHELL=			${MKSH}		# missing ? not an oversight
# assume osdep provides MACHINE_OS, OStype, OStriplet, OBJECT_FMT etc.

.if defined(NOPIC) && ${NOPIC:L} != "no"
NO_SHARED_LIBS?=	Yes
LDFLAGS?=
.  if !${LDFLAGS:L:M-static}
LDFLAGS+=		-static
.  endif
.endif
NO_SHARED_LIBS?=	No

# These used to be in <bsd.port.mk> but here they're more
# easily checked and overridden by ports' Makefiles.
USE_CXX?=		No
USE_GMAKE?=		No
USE_MOTIF?=		No
USE_SCHILY?=		No
USE_SYSTRACE?=		Yes
USE_X11?=		No

# mirports.osdep.mk is expected to provide these variables
# (where they differ from defaults); only fill in changes.
# this is supposed to be alphabetically supported.
AUTOCONF_FAKEOS?=	${ARCH}-ecce-openbsd${OScompat}
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_CXX?=		base
HAS_DLADDR?=		Yes
HAS_TIMET64?=		No
MKC_USAP?=		No
MODPERL_DESTDIR?=
PKG_ARGS_ADD?=
PKG_SUFX?=		.cgz
_SYSTRACE_ARGS?=	-i -a -e
_CKSUM_A?=		cksum -a
_GDIFFLAG?=
OSREV?=			${OSrev}

# former pkgpath.mk

.ifndef	PKGPATH
_PORTSDIR!=		readlink -nf ${PORTSDIR}
_CURDIR!=		readlink -nf ${.CURDIR}
PKGPATH=		${_CURDIR:S,${_PORTSDIR}/,,}
.endif
.if empty(PKGPATH)
PKGDEPTH=
.else
PKGDEPTH=		${PKGPATH:C|[^./][^/]*|..|g}/
.endif

PORTSDIR_PATH?=		${PORTSDIR}:${PORTSDIR}/Mystuff
HTMLIFY=		sed -e 's/&/\&amp;/g' -e 's/>/\&gt;/g' -e 's/</\&lt;/g'

# Code to invoke to split dir,-multi,flavour

_flavour_fragment= \
	multi=''; flavour=''; space=''; sawflavour=false; \
	case "$$dir" in \
	*,*) \
		IFS=,; first=true; for i in $$dir; do \
			if $$first; then \
				dir=$$i; first=false; \
			else \
				case X"$$i" in \
				X-*) \
					multi="$$i"	;; \
				*) \
					sawflavour=true; \
					flavour="$$flavour$$space$$i"; \
					space=' '	;; \
				esac \
			fi; \
		done; unset IFS	;; \
	esac; \
	toset="PKGPATH=$$dir"; \
	[[ -z $$multi ]] || toset="$$toset SUBPACKAGE=\"$$multi\""; \
	if $$sawflavour; then \
		toset="$$toset FLAVOR=\"$$flavour\""; \
	fi; \
	IFS=:; found_dir=false; bases=${PORTSDIR_PATH}; \
	for base in $$bases; do \
		cd $$base 2>/dev/null || continue; \
		if [ -L "$$dir" ]; then \
			print -u2 ">> Broken dependency:" \
			    "$$base/$$dir is a symbolic link"; \
			exit 1; \
		fi; \
		if cd $$dir 2>/dev/null; then \
			found_dir=true; \
			break; \
		fi; \
	done; unset IFS; \
	if ! $$found_dir; then \
		print -u2 ">> Broken dependency: $$dir non-existent"; \
		exit 1; \
	fi

_depfile_fragment= \
	if [[ -z $$_DEPENDS_FILE ]]; then \
		_DEPENDS_FILE=$$(mktemp /tmp/depends.XXXXXXXXXXXX|| exit 1); \
		export _DEPENDS_FILE; \
		trap "rm -f $${_DEPENDS_FILE}" 0 1 2 3 13 15; \
	fi


MIRPORTS_SYS_MK=	done
.endif
