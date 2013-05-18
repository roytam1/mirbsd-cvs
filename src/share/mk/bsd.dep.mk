# $MirOS: src/share/mk/bsd.dep.mk,v 1.8 2005/12/15 01:13:44 tg Exp $
# $OpenBSD: bsd.dep.mk,v 1.5 2003/08/07 11:24:03 espie Exp $
# $NetBSD: bsd.dep.mk,v 1.12 1995/09/27 01:15:09 christos Exp $

.if !defined(BSD_DEP_MK)
BSD_DEP_MK=1

# some of the rules involve .h sources, so remove them from mkdep line
# add them to the beforedepend target
.if !target(depend)
depend: beforedepend .depend _SUBDIRUSE afterdepend
.  if defined(SRCS)
.depend: ${SRCS}
	@rm -f .depend
	@files="${.ALLSRC:M*.s} ${.ALLSRC:M*.S}"; \
	if [[ $$files != " " ]]; then \
		echo ${MKDEP_SH} -a ${MKDEP} ${CFLAGS:M-[ID]*} \
		    ${CPPFLAGS} ${AINC} $$files; \
		CC=${CC:Q} ${MKDEP_SH} -a ${MKDEP} ${CFLAGS:M-[ID]*} \
		    ${CPPFLAGS} ${AINC} $$files; \
	fi
	@files="${.ALLSRC:M*.c} ${.ALLSRC:M*.m}"; \
	if [[ $$files != " " ]]; then \
		echo ${MKDEP_SH} -a ${MKDEP} ${CFLAGS:M-[ID]*} \
		    ${CPPFLAGS} $$files; \
		CC=${CC:Q} ${MKDEP_SH} -a ${MKDEP} ${CFLAGS:M-[ID]*} \
		    ${CPPFLAGS} $$files; \
	fi
	@files="${.ALLSRC:M*.cc} ${.ALLSRC:M*.C} ${.ALLSRC:M*.cxx}"; \
	if [[ $$files != "  " ]]; then \
		echo ${MKDEP_SH} -a ${MKDEP} ${CXXFLAGS:M-[ID]*} \
		    ${CPPFLAGS} $$files; \
		CC=${CXX:Q} ${MKDEP_SH} -a ${MKDEP} ${CXXFLAGS:M-[ID]*} \
		    ${CPPFLAGS} $$files; \
	fi
.  else
.depend:
.  endif
.  if !target(beforedepend)
beforedepend:
.  endif
.  if !target(afterdepend)
afterdepend:
.  endif
.endif	# not target depend

.if !target(tags)
.  if defined(SRCS)
tags: ${SRCS} _SUBDIRUSE
	-cd ${.CURDIR} && ${CTAGS} -f /dev/stdout ${.ALLSRC:N*.h} | \
	    sed "s;\${.CURDIR}/;;" >tags
.  else
tags:
.  endif
.endif

.if defined(SRCS)
cleandir: cleandepend
cleandepend:
	rm -f .depend ${.CURDIR}/tags
.endif

.if exists(${.CURDIR}/Makefile.bsd-wrapper)
.depend: ${.CURDIR}/Makefile.bsd-wrapper
.elif exists(${.CURDIR}/BSDmakefile)
.depend: ${.CURDIR}/BSDmakefile
.elif exists(${.CURDIR}/makefile)
.depend: ${.CURDIR}/makefile
.elif exists(${.CURDIR}/Makefile)
.depend: ${.CURDIR}/Makefile
.endif

.PHONY: beforedepend depend afterdepend cleandepend

.endif
