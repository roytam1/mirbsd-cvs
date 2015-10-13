# $MirOS: src/share/mk/bsd.subdir.mk,v 1.8 2009/03/22 15:27:34 tg Exp $
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
	@for _dirent_ in ${SUBDIR}; do \
		if [[ -d ${.CURDIR}/$$_dirent_.${MACHINE} ]]; then \
			_newdir_=$$_dirent_.${MACHINE}; \
		else \
			_newdir_=$$_dirent_; \
		fi; \
		if [[ -n $$_thisdir_ ]]; then \
			_nextdir_=$$_thisdir_/$$_newdir_; \
		else \
			_nextdir_=$$_newdir_; \
		fi; \
		if [[ -s ${.CURDIR}/$$_newdir_/Makefile.bsd-wrapper ]]; then \
			_nextmf_="-f Makefile.bsd-wrapper"; \
		else \
			_nextmf_=; \
		fi; \
		_nextsd_=; \
		for _skipck_ in ${SKIPDIR}; do \
			if [[ $$_skipck_ = $$_dirent_ ]]; then \
				print -r "($$_nextdir_ skipped)"; \
				continue 2; \
			elif [[ $$_skipck_ != $$_dirent_/* ]]; then \
				continue; \
			fi; \
			_nextsd_="$$_nextsd_ $${_skipck_#$$_dirent_/}"; \
		done; \
		print -r "===> $$_nextdir_"; \
		(cd ${.CURDIR}/$$_newdir_ && exec ${MAKE} \
		    SKIPDIR="$$_nextsd_" ${MAKE_FLAGS} $$_nextmf_ \
		    ${.TARGET:S/realinstall/install/:S/.depend/depend/}); \
	done

${SUBDIR}::
	@if [[ -d ${.CURDIR}/$@.${MACHINE} ]]; then \
		_newdir_=$@.${MACHINE}; \
	else \
		_newdir_=$@; \
	fi; \
	if [[ -s ${.CURDIR}/$$_newdir_/Makefile.bsd-wrapper ]]; then \
		_nextmf_="-f Makefile.bsd-wrapper"; \
	else \
		_nextmf_=; \
	fi; \
	print -r "===> $$_newdir_"; \
	cd ${.CURDIR}/$$_newdir_ && exec ${MAKE} \
	    ${MAKE_FLAGS} $$_nextmf_ _thisdir_="$$_newdir_" all
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

.for t in all clean cleandir includes depend lint obj tags regress __MANALL __MANINSTALL
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
