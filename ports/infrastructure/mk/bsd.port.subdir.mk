# $MirOS: ports/infrastructure/mk/bsd.port.subdir.mk,v 1.3 2005/11/15 19:33:56 tg Exp $
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
REPORT_PROBLEM?=exit 1

# create a list of subdirectories
.ifndef _MANUAL_SUBDIR
_SUBDIR!=	cd ${.CURDIR} && echo */Makefile \
		    | sed -e 's!/Makefile!!g' | sort -R' '
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
	for i in ${_SKIPPED}; do \
		eval $${echo_msg} "===\> $$i skipped"; \
	done; \
	for d in ${_FULLSUBDIR}; do \
		dir=$$d; \
		${_flavour_fragment}; \
		set +e; \
		if [ -r bulklist ]; then \
			while read flavour; do \
				f=$$([[ -z $$flavour ]] || echo "$$flavour" \
				    | sed -e 's/ /,/g'); \
				tmp_toset="$$toset FLAVOR=\"$$flavour\""; \
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

.for __target in all fetch package fake extract cleandir configure \
		 build describe distclean deinstall install \
		 reinstall checksum show fetch-makefile \
		 link-categories unlink-categories regress lib-depends-check \
		 homepage-links manpages-check relevant-checks

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
		unset FLAVOR SUBPACKAGE || true; \
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
		*) comment=$$(eval $$toset ${MAKE} show=_COMMENT \
		    | sed -e 's,^",,' -e 's,"$$,,' | ${HTMLIFY});; \
	esac; \
	cd ${.CURDIR}; \
	echo "<dt><a href=\"${PKGDEPTH}$$dir/$$name.html\">$d</a><dd>$$comment" >>$@.tmp
.endfor
	@cat ${README} | \
		sed -e 's%%CATEGORY%%'$$(echo ${.CURDIR} | sed -e 's.*/\([^/]*\)$$\1')'g' \
			-e '/%%DESCR%%/r${.CURDIR}/pkg/DESCR' -e '//d' \
			-e '/%%SUBDIR%%/r$@.tmp' -e '//d' \
		> $@
	@rm $@.tmp

_print-packagename:
	@echo "README"

.PHONY: all fetch package fake extract configure \
	build describe distclean deinstall install \
	reinstall checksum show fetch-makefile \
	link-categories unlink-categories regress lib-depends-check \
	homepage-links manpages-check relevant-checks \
	all-dir-depends build-dir-depends run-dir-depends \
	clean cleandir readmes _print-packagename
