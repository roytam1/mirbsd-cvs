# $MirOS: src/share/mk/bsd.obj.mk,v 1.5 2005/05/06 16:57:59 tg Exp $
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
__usrobjdir!=	readlink -nf ${BSDOBJDIR}.${MACHINE} || \
		    echo ${BSDOBJDIR:Q}.${MACHINE:Q}
__usrobjdirpf=
.    else
__usrobjdir!=	readlink -nf ${BSDOBJDIR} || echo ${BSDOBJDIR:Q}
.      if defined(OBJMACHINE)
__usrobjdirpf=	.${MACHINE}
.      else
__usrobjdirpf=
.      endif
.    endif

_SUBDIRUSE:

obj! _SUBDIRUSE
	@cd ${.CURDIR}; here=$$(readlink -nf .); \
	bsdsrcdir=$$(readlink -nf ${BSDSRCDIR}); \
	subdir=$${here#$${bsdsrcdir}/}; \
	if [[ $$here != $$subdir ]]; then \
		dest=${__usrobjdir}/$$subdir${__usrobjdirpf}; \
		print -r "$$here/${__objdir} -> $$dest"; \
		if [[ ! -L ${__objdir} \
		    || $$(readlink ${__objdir}) != $$dest ]]; then \
			[[ ! -e ${__objdir} ]] || rm -rf ${__objdir}; \
			ln -sf $$dest ${__objdir}; \
		fi; \
		[[ ! -d ${__usrobjdir} || -d $$dest ]] || mkdir -p $$dest; \
	elif [[ ! -d ${__objdir} ]]; then \
		print -r "making $$here/${__objdir}"; \
		mkdir ${__objdir}; \
	fi
.  endif
.endif	# ! not target obj

.endif
