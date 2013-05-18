# $MirOS: ports/infrastructure/mk/mirports.sys.mk,v 1.35 2006/09/20 22:24:49 tg Exp $
#-
# Copyright (c) 2005, 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.

.ifndef	MIRPORTS_SYS_MK

# Basic defaults.
.if !defined(OSNAME) || empty(OSNAME)
OSNAME!=		uname -s
.endif
.if !defined(OSname) || empty(OSname)
OSname=			${OSNAME:L}
.endif

# Determine version number. OSREV is uname -r, OSver is major.minor
.if ${OStype} == "MirBSD"
OSver!=	print '.include "/usr/share/mk/sys.mk"\nall:\n.ifdef OSrelm\n\t@echo' \
	    '$${OSrel}.$${OSrelm}\n.else\n\t@echo $${OSrev}.$${OSrpl}\n.endif' \
	    | ${MAKE} -rf - all
# fake 'uname -r' for speed
OSREV=	${OSver:R}
.elif ${OStype} == "OpenBSD"
OSver!=	print '.include "/usr/share/mk/sys.mk"\nall:\n\t@echo $${OSREV}' \
	    | ${MAKE} -rf - all
# fake 'uname -r' for speed
OSREV=	${OSver}
.elif ${OStype} == "Interix"
.  error Fill in later!
.elif ${OStype} == "Darwin"
OSREV!=	uname -r
OSver=	${OSREV:C/^([0-9]*\.[0-9]*)\..*$/\1/}
.else
.  error Unknown OStype '${OStype}'!
.endif

#--- Specific OS Dependencies

.if ${OStype} == "Darwin"
CPPFLAGS+=		-D__unix__=1
LDFLAGS+=		-specs=${WRKDIR}/specs
NOPIC=			No	# XXX
LDCONFIG=
_CKSUM_A=
HAS_TIMET64=		No
NO_SYSTRACE=		not on Darwin
FETCH_CMD?=		/usr/bin/ftp
TAR=			${LOCALBASE}/bin/tar
UNZIP=			/usr/bin/unzip
BZIP2=			/usr/bin/bzip2
CHOWN=			/usr/sbin/chown
M4?=			/usr/bin/gm4
P5ARCH=			${P5SITE}/darwin-thread-multi-2level
.endif

#---

.if ${OStype} == "Interix"
# Use a better working resolver
CPPFLAGS+=		-I/usr/local/include/bind
LDFLAGS+=		-Wl,--library-after=/usr/local/lib/bind
LDADD+=			-lbind -ldb

HAS_TIMET64=		No
NO_SYSTRACE=		not on Interix
P5ARCH=			${P5SITE}/x86-interix-thread-multi
UNZIP=			/usr/contrib/bin/unzip
CHOWN=			/bin/chown
_MAKE_COOKIE=		/bin/touch
GZIP_CMD=		/usr/contrib/bin/gzip -nf ${GZIP}
GZCAT?=			/usr/contrib/bin/gzip -dc

.  ifndef BOOTSTRAP	# Install these first
_CKSUM_A=		${LOCALBASE}/bin/cksum -a
M4=			${LOCALBASE}/bin/gm4
.  endif
FETCH_CMD?=		${LOCALBASE}/bin/wget
PATCH?=			${LOCALBASE}/bin/patch
.endif

#---

.if ${OStype} == "OpenBSD"
MKC_USAP?=		Yes
PKG_ARGS_ADD+=		-Z
PKG_SUFX=		.tgz
HAS_TIMET64=		No
FETCH_CMD=		/usr/bin/ftp -V -m

OSrev=			${OSREV:S/.//}

.  if ${OSrev} < 35
MODPERL_DESTDIR=	$${${DESTDIRNAME}}
_SYSTRACE_ARGS=		-i -a
.  endif

.  if ${OSrev} < 36
HAS_DLADDR=		No
_CKSUM_A=
_GDIFFLAG=		NEED_GDIFF=yes
.  endif
.endif

#---

.if ${OStype} == "MirBSD"
.  if ${OSver:R} < 8
.    error Operating System too old and unsupported.
.  elif ${OSver:R} == 8
.    if ${OSver:E} < 40
HAS_CXX=		reason
NO_CXX=			C++ is still broken, please update
.    endif
.  endif
.  if ${_MIRMAKE_VER} >= 20060921
_CKSUM_SIZE=		#defined
.  endif
.  if ${OSver:E} > 129
_CKSUM_SIZE=		#defined
.  endif
.endif

#--- End of OS Dependencies

SHELL=			${MKSH}		# missing ? not an oversight

# this is supposed to be alphabetically supported.
_MIRPORTS_ADDRESS=	<miros-discuss@MirBSD.org>
_MIROS_ANONCVS=		anoncvs@unixforge.de:/cvs
ARCH?=			${MACHINE_ARCH}
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_CXX?=		base
HAS_DLADDR?=		Yes
HAS_TIMET64?=		No
LP64_PLATFORMS?=	*:*:alpha *:*:amd64 *:*:sparc64
MKC_USAP?=		No
MKSH?=			/bin/mksh
MODPERL_DESTDIR?=
NOPIC_PLATFORMS?=
PKG_ARGS_ADD?=
PKG_SUFX?=		.cgz
_CKSUM_A?=		cksum -a
_GDIFFLAG?=
_SYSTRACE_ARGS?=	-i -a -e

.if defined(NOPIC) && ${NOPIC:L} != "no"
NO_SHARED_LIBS?=	Yes
LDFLAGS?=
.  if !${LDFLAGS:L:M-static}
LDFLAGS+=		-static
.  endif
.endif
NO_SHARED_LIBS?=	No

.if (${BINOWN} == "root") && (${LOCALBASE} == "/usr/mpkg")
__SYSTEM_PORTS=		Yes
.else
__SYSTEM_PORTS=		No
.endif

# These used to be in <bsd.port.mk> but here they're more
# easily checked and overridden by ports' Makefiles.
USE_CXX?=		No
USE_GMAKE?=		No
USE_MOTIF?=		No
USE_SCHILY?=		No
USE_X11?=		No

#--- former pkgpath.mk

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
	multi=; flavour=; space=; sawflavour=false; \
	case "$$dir" in \
	*,) \
		dir=$${dir%,}; \
		sawflavour=true; \
		;; \
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
		trap "rm -f $${_DEPENDS_FILE}" 0 1 2 3 5 13 15; \
	fi


MIRPORTS_SYS_MK=	done
.endif
