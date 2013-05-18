# $MirOS: ports/infrastructure/mk/bsd.port.subdir.mk,v 1.14 2008/10/16 19:47:54 tg Exp $
# $OpenBSD: bsd.port.subdir.mk,v 1.64 2004/04/07 13:06:33 espie Exp $
# $FreeBSD: bsd.port.subdir.mk,v 1.20 1997/08/22 11:16:15 asami Exp $
#
# The include file <bsd.port.subdir.mk> contains the default targets
# for building ports subdirectories.
#
#
# +++ variables +++
#
# STRIP		The flag passed to the install program to cause the binary
#		to be stripped.  This is to be used when building your
#		own install script so that the entire system can be made
#		stripped/not-stripped using a single knob. [-s]
#
# ECHO_MSG	Used to print all the '===>' style prompts - override this
#		to turn them off [echo].
#
# SUBDIR	A list of subdirectories that should be built as well.
#		Each of the targets will execute the same target in the
#		subdirectories.
#
#
# +++ targets +++
#
#	README.html:
#		Creating README.html for package.
#
#	afterinstall, all, beforeinstall, build, checksum, clean, cleandir,
#	configure, depend, describe, extract, fetch, fetch-list,
#	install, package, readmes, deinstall, reinstall,
#	tags

.ifndef	MIRPORTS_SYS_MK
ERRORS+=		"Please upgrade your system Makefile includes."
ERRORS+=		"See http://mirbsd.de/ for instructions."
.endif

.if defined(show)
.MAIN: show
.elif defined(clean)
.MAIN: clean
.else
.MAIN: all
.endif

.if !defined(DEBUG_FLAGS)
STRIP?=		-s
.endif

ECHO_MSG?=	echo

BULK?=		No
.if ${BULK:L} == "yes"
REPORT_PROBLEM?=env PORTSDIR=${PORTSDIR} ${SHELL} ${PORTSDIR}/infrastructure/scripts/failedport $$dir,$$f
.else
REPORT_PROBLEM?=exit 1
.endif

# create a list of subdirectories
.ifdef SUBONLY
SUBDIR=		${SUBONLY}
.elifndef _MANUAL_SUBDIR
_SUBDIR!=	cd ${.CURDIR} && echo */Makefile | \
		    sed -e 's!/Makefile!!g' | sort -R' '
.  if ${_SUBDIR:N\*}
SUBDIR+=	${_SUBDIR}
.  endif
.endif

# create a full list of SUBDIRS...
.if empty(PKGPATH)
_FULLSUBDIR:=	${SUBDIR}
.else
_FULLSUBDIR:=	${SUBDIR:S@^@${PKGPATH}/@g}
.endif

_SKIPPED=
.for i in ${SKIPDIR}
_SKIPPED:+=	${_FULLSUBDIR:M$i}
_FULLSUBDIR:=	${_FULLSUBDIR:N$i}
.endfor


_subdir_fragment= \
	: $${echo_msg:=${ECHO_MSG:Q}}; \
	: $${target:=${.TARGET}}; \
	unset SUBONLY || :; \
	for i in ${_SKIPPED}; do \
		eval $${echo_msg} "===\> $$i skipped"; \
	done; \
	for d in ${_FULLSUBDIR}; do \
		dir=$$d; \
		${_flavour_fragment}; \
		set +e; \
		if [[ $$d != *,* && -r bulklist ]]; then \
			while read flavour; do \
				f=$$([[ -z $$flavour ]] || \
				    sed -e 's/ /,/g' <<<"$$flavour"); \
				tmp_toset="$$toset FLAVOUR=\"$$flavour\""; \
				eval $${echo_msg} "===\> $$dir,$$f"; \
				if ! eval $$tmp_toset ${MAKE} $$target; then \
					${REPORT_PROBLEM}; \
				fi; \
			done <bulklist; \
		else \
			eval $${echo_msg} "===\> $$d"; \
			if ! eval $$toset ${MAKE} $$target; then \
				${REPORT_PROBLEM}; \
			fi; \
		fi; \
	done; set -e

.for __target in all build checksum cleandir configure \
    deinstall describe distclean extract fake fetch fetch-all fetch-makefile \
    homepage-links install lib-depends-check link-categories manpages-check \
    package regress reinstall relevant-checks show unlink-categories
${__target}:
	@${_subdir_fragment}
.endfor

.for __target in all-dir-depends build-dir-depends run-dir-depends
${__target}:
	@${_depfile_fragment}; echo_msg=:; ${_subdir_fragment}
.endfor

clean:
.if defined(clean) && ${clean:L:Mdepends}
	@{ target=all-dir-depends; echo_msg=:; \
	${_depfile_fragment}; ${_subdir_fragment}; }| tsort -r|while read dir; do \
		unset FLAVOUR SUBPACKAGE || true; \
		${_flavour_fragment}; \
		eval $$toset ${MAKE} _CLEANDEPENDS=No clean; \
	done
.else
	@${_subdir_fragment}
.endif
.if defined(clean) && ${clean:L:Mreadmes}
	rm -f ${.CURDIR}/README.html
.endif

readmes:
	@${_subdir_fragment}
	@rm -f ${.CURDIR}/README.html
	@cd ${.CURDIR} && exec ${MAKE} README.html

TEMPLATES?=	${PORTSDIR}/infrastructure/templates
.if defined(PORTSTOP)
README=		${TEMPLATES}/README.top
.else
README=		${TEMPLATES}/README.category
.endif

README.html:
	@>$@.tmp
.for d in ${_FULLSUBDIR}
	@dir=$d; ${_flavour_fragment}; \
	name=$$(eval $$toset ${MAKE} _print-packagename); \
	case $$name in \
		README) comment=;; \
		*) comment=$$(eval $$toset ${MAKE} show=_COMMENT | ${HTMLIFY});; \
	esac; \
	cd ${.CURDIR}; \
	echo "<dt><a href=\"${PKGDEPTH}$$dir/$$name.html\">$d</a><dd>$$comment" >>$@.tmp
.endfor
	@f=${.CURDIR:Q}/pkg/DESCR; \
	 [[ -e $$f ]] || f=${.CURDIR:Q}/DESCR; \
	 sed -e \
	    's%%CATEGORY%%'$$(echo ${.CURDIR:Q} | \
	    sed -e 's.*/\([^/]*\)$$\1')'g' \
	    -e '/%%DESCR%%/r'"$$f" -e '//d' \
	    -e '/%%SUBDIR%%/r$@.tmp' -e '//d' \
	    <${README:Q} >$@
	@rm $@.tmp

_print-packagename:
	@echo "README"

.PHONY: _print-packagename all all-dir-depends build build-dir-depends \
    checksum clean cleandir configure deinstall describe distclean \
    extract fake fetch fetch-all fetch-makefile homepage-links install \
    lib-depends-check link-categories manpages-check package \
    readmes regress reinstall relevant-checks run-dir-depends show \
    unlink-categories
