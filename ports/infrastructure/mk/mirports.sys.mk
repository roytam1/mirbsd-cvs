# $MirOS: ports/infrastructure/mk/mirports.sys.mk,v 1.10.2.14 2005/09/12 22:13:48 tg Exp $
#-
# Copyright (c) 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.

.ifndef	MIRPORTS_SYS_MK

# Provide consistent MirPorts behaviour. (Sync with mirports.bsd.mk)
DEBUGLIBS=		No
DEBUGPROGS=		No

# Basic defaults.
.ifndef	OSname
OSNAME!=		uname -s
OSname=			${OSNAME:L}
.endif

.ifndef OSREV
OSREV!=			uname -r
.endif
.ifndef OSrev
OSrev=			${OSREV:S/./_/g}
.endif

#--- Specific OS Dependencies

.if ${OStype} == "Darwin"
NOPIC=			No	# XXX
LDCONFIG=
_CKSUM_A=
HAS_TIMET64=		No
USE_SYSTRACE=		No
FETCH_CMD?=		/usr/bin/ftp
TAR=			${LOCALBASE}/bin/tar
UNZIP=			/usr/bin/unzip
BZIP2=			/usr/bin/bzip2
CHOWN=			/usr/sbin/chown
M4?=			/usr/bin/gm4
.endif

#---

.if ${OStype} == "Interix"
# Use a better working resolver
CPPFLAGS+=		-I/usr/local/include/bind

HAS_TIMET64=		No
USE_SYSTRACE=		No
UNZIP=			/usr/contrib/bin/unzip
CHOWN=			/bin/chown
_MAKE_COOKIE=		/bin/touch
GZIP_CMD=		/usr/contrib/bin/gzip -nf ${GZIP}
GZCAT?=			/usr/contrib/bin/gzip -dc

.  ifndef BOOTSTRAP	# Install these first
_CKSUM_A=		${LOCALBASE}/bin/cksum -a
M4=			${LOCALBASE}/bin/gm4
FETCH_CMD?=		${LOCALBASE}/bin/wget
TAR=			${LOCALBASE}/bin/tar
.  endif
.endif

#---

.if ${OStype} == "OpenBSD"
MKC_USAP?=		Yes
PKG_ARGS_ADD+=		-Z
PKG_SUFX=		.tgz
HAS_TIMET64=		No
FETCH_CMD=		/usr/bin/ftp -V -m

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
.  if ${OSrev} < 8
.    error Operating System too old and unsupported.
.  elif ${OSrev} == 8
.    ifndef OSrpl
OSrpl!=			x=$(uname -l); x=16#${x#@(#[0-9][a-z])}; let x=${x%%-*}; print $x
.    endif
.    if ${OSrpl} < 40
HAS_CXX=		reason
NO_CXX=			C++ is still broken, please update
.    endif
.  endif
.endif

#--- End of OS Dependencies

SHELL=			${MKSH}		# missing ? not an oversight

# this is supposed to be alphabetically supported.
_MIRPORTS_ADDRESS=	<miros-discuss@MirBSD.org>
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
OSREV?=			${OSrev}
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

# These used to be in <bsd.port.mk> but here they're more
# easily checked and overridden by ports' Makefiles.
USE_CXX?=		No
USE_GMAKE?=		No
USE_MOTIF?=		No
USE_SCHILY?=		No
USE_SYSTRACE?=		Yes
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
