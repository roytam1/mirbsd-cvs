# $MirOS$
# $OpenBSD: bsd.obj.mk,v 1.12 2003/10/28 17:09:33 espie Exp $
# $NetBSD: bsd.obj.mk,v 1.9 1996/04/10 21:08:05 thorpej Exp $

.if !defined(BSD_OBJ_MK)
BSD_OBJ_MK=1

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

.if !target(obj)
.  if ${NOOBJ:L} != "no"
obj:
.  else

.    if defined(MAKEOBJDIR) && !empty(MAKEOBJDIR)
__baseobjdir=	${MAKEOBJDIR}
.    else
__baseobjdir=	obj
.    endif

.    if defined(OBJMACHINE)
__objdir=	${__baseobjdir}.${MACHINE}
.    else
__objdir=	${__baseobjdir}
.    endif

.    if defined(USR_OBJMACHINE)
__usrobjdir=	${BSDOBJDIR}.${MACHINE}
__usrobjdirpf=
.    else
__usrobjdir=	${BSDOBJDIR}
.      if defined(OBJMACHINE)
__usrobjdirpf=	.${MACHINE}
.      else
__usrobjdirpf=
.      endif
.    endif

_SUBDIRUSE:

obj! _SUBDIRUSE
	@cd ${.CURDIR}; \
	here=$$(/bin/pwd); bsdsrcdir=$$( (cd ${BSDSRCDIR} && /bin/pwd) \
	    2>/dev/null || print '${BSDSRCDIR}'); \
	subdir=$${here#$${bsdsrcdir}/}; \
	if test $$here != $$subdir ; then \
		dest=${__usrobjdir}/$$subdir${__usrobjdirpf} ; \
		echo "$$here/${__objdir} -> $$dest"; \
		if test ! -L ${__objdir} -o \
		    X$$(readlink ${__objdir}) != X$$dest; \
		    then \
			if test -e ${__objdir}; then rm -rf ${__objdir}; fi; \
			ln -sf $$dest ${__objdir}; \
		fi; \
		if test -d ${__usrobjdir} -a ! -d $$dest; then \
			mkdir -p $$dest; \
		else \
			true; \
		fi; \
	else \
		true ; \
		dest=$$here/${__objdir} ; \
		if test ! -d ${__objdir} ; then \
			echo "making $$dest" ; \
			mkdir $$dest; \
		fi ; \
	fi;
.  endif
.endif	# ! not target obj

.endif
