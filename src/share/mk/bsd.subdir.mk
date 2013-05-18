# $MirOS: src/share/mk/bsd.subdir.mk,v 1.5 2005/07/21 22:52:11 tg Exp $
# $OpenBSD: bsd.subdir.mk,v 1.14 2005/02/05 10:39:50 espie Exp $
# $NetBSD: bsd.subdir.mk,v 1.11 1996/04/04 02:05:06 jtc Exp $
# @(#)bsd.subdir.mk	5.9 (Berkeley) 2/1/91

.if !defined(BSD_SUBDIR_MK)
BSD_SUBDIR_MK=1

.if !target(.MAIN)
.MAIN: all
.endif

# Make sure this is defined
SKIPDIR?=

_SUBDIRUSE: .USE
.if defined(SUBDIR)
	@for entry in ${SUBDIR}; do ( \
		set -e; \
		if [[ -d ${.CURDIR}/$$entry.${MACHINE} ]]; then \
			_newdir_="$$entry.${MACHINE}"; \
		else \
			_newdir_="$$entry"; \
		fi; \
		if [[ -z $$_THISDIR_ ]]; then \
			_nextdir_="$$_newdir_"; \
		else \
			_nextdir_="$$_THISDIR_/$$_newdir_"; \
		fi; \
		_makefile_spec_=; \
		[[ ! -f ${.CURDIR}/$$_newdir_/Makefile.bsd-wrapper ]] \
		    || _makefile_spec_="-f Makefile.bsd-wrapper"; \
		subskipdir=; \
		for skipdir in ${SKIPDIR}; do \
			subentry=$${skipdir#$$entry}; \
			if [[ $$subentry != $$skipdir ]]; then \
				if [[ -z $$subentry ]]; then \
					echo "($$_nextdir_ skipped)"; \
					break; \
				fi; \
				subskipdir="$$subskipdir $${subentry#/}"; \
			fi; \
		done; \
		if [[ -z $$skipdir || -n $$subentry ]]; then \
			echo "===> $$_nextdir_"; \
			cd ${.CURDIR}/$$_newdir_; \
			${MAKE} SKIPDIR="$$subskipdir" $$_makefile_spec_ \
			    _THISDIR_="$$_nextdir_" ${MAKE_FLAGS} \
			    ${.TARGET:S/realinstall/install/:S/.depend/depend/}; \
		fi; \
	) done

${SUBDIR}::
	@set -e; \
	if [[ -d ${.CURDIR}/${.TARGET}.${MACHINE} ]]; then \
		_newdir_=${.TARGET}.${MACHINE}; \
	else \
		_newdir_=${.TARGET}; \
	fi; \
	_makefile_spec_=; \
	[[ ! -f ${.CURDIR}/$$_newdir_/Makefile.bsd-wrapper ]] \
	    || _makefile_spec_="-f Makefile.bsd-wrapper"; \
	echo "===> $$_newdir_"; \
	cd ${.CURDIR}/$$_newdir_; \
	${MAKE} ${MAKE_FLAGS} $$_makefile_spec_ _THISDIR_="$$_newdir_" all
.endif

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif
.  if !target(afterinstall)
afterinstall:
.  endif
install: maninstall
maninstall: afterinstall
afterinstall: realinstall
realinstall: beforeinstall _SUBDIRUSE
.endif

.if !target(includes)
BSD_SUBDIR_MK_NOINCLUDES=1
.endif

.for t in all clean cleandir includes depend lint obj tags regress
.  if !target($t)
$t: _SUBDIRUSE
.  endif
.endfor

_subdircheck:
	@missing=; \
	new=; \
	sp=; \
	all=' '; \
	_skiplist="$${_skiplist-CVS .svn}"; \
	_skiplist=" $$_skiplist "; \
	for s in ${SUBDIR}; do \
		all="$$all$$s "; \
		[[ ! -d $$s ]] || continue; \
		missing="$$missing$$sp$$s"; \
		sp=' '; \
	done; \
	sp=; \
	for s in * .*; do \
		[[ $$_skiplist != *@( $$s )* ]] || continue; \
		[[ -d $$s ]] || continue; \
		[[ $$all != *@( $$s )* ]] || continue; \
		new="$$new$$sp$$s"; \
		sp=' '; \
	done; \
	print "Missing in current directory:\n\t$$missing"; \
	print "New in current directory:\n\t$$new"

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

.endif
