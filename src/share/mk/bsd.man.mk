# $MirOS: src/share/mk/bsd.man.mk,v 1.4 2008/04/10 14:07:46 tg Exp $
# $OpenBSD: bsd.man.mk,v 1.28 2004/02/08 01:19:54 espie Exp $
# $NetBSD: bsd.man.mk,v 1.23 1996/02/10 07:49:33 jtc Exp $
# @(#)bsd.man.mk	5.2 (Berkeley) 5/11/90

.if !defined(BSD_MAN_MK)
BSD_MAN_MK=1

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

MACROS?=	-mandoc
MINSTALL=       ${INSTALL} ${INSTALL_COPY} -o ${MANOWN} -g ${MANGRP} \
		-m ${MANMODE}

.if !target(.MAIN)
.  if exists(${.CURDIR}/../Makefile.inc)
.    include "${.CURDIR}/../Makefile.inc"
.  endif

.MAIN: all
.endif

.SUFFIXES:	.1 .2 .3 .3p .4 .5 .6 .7 .8 .9 \
	.1tbl .2tbl .3tbl .4tbl .5tbl .6tbl .7tbl .8tbl .9tbl \
	.cat1 .cat2 .cat3 .cat3p .cat4 .cat5 .cat6 .cat7 .cat8 .cat9 \
	.ps1 .ps2 .ps3 .ps3p .ps4 .ps5 .ps6 .ps7 .ps8 .ps9 \
	.1eqn .2eqn .3eqn .4eqn .5eqn .6eqn .7eqn .8eqn .9eqn

.9.cat9 .8.cat8 .7.cat7 .6.cat6 .5.cat5 .4.cat4 .3p.cat3p .3.cat3 .2.cat2 .1.cat1:
	${NROFF} $< >$@ || (rm -f $@; false)

.9.ps9 .8.ps8 .7.ps7 .6.ps6 .5.ps5 .4.ps4 .3p.ps3p .3.ps3 .2.ps2 .1.ps1:
	${ROFF} $< >$@ || (rm -f $@; false)

.1tbl.1 .2tbl.2 .3tbl.3 .4tbl.4 .5tbl.5 .6tbl.6 .7tbl.7 .8tbl.8 .9tbl.9:
	${TBL} $< >$@ || (rm -f $@; false)

.1eqn.1tbl .2eqn.2tbl .3eqn.3tbl .4eqn.4tbl .5eqn.5tbl .6eqn.6tbl .7eqn.7tbl .8eqn.8tbl .9eqn.9tbl:
	${EQN} $< >$@ || (rm -f $@; false)

.if defined(MAN) && !empty(MAN) && !defined(MANALL)
MANALL!=	for m in ${MAN}; do \
			local x=$${m%.[1-9]?(eqn|tbl)}; \
			local y=$${m\#@($$x.)}; \
			[[ $$x = $$m ]] && print -nr -- "$$m " || \
			    print -nr -- "$${x}.cat$${y%%?(eqn|tbl)} "; \
		done
.  if !defined(MANLOCALBUILD)
.    for _i in ${MAN:M*.?tbl}
CLEANFILES+=	${_i:S/tbl$//}
.    endfor
.    for _i in ${MAN:M*.?eqn}
CLEANFILES+=	${_i:S/eqn$//} ${_i:S/eqn$/tbl/}
.    endfor
.  endif
.endif

maninstall: __MANINSTALL
.PHONY: __MANINSTALL

__MANINSTALL:
.if defined(MANALL)
.  for _i in ${MANALL}
	${MINSTALL} ${_i} ${DESTDIR}${MANDIR}${_i:E:S/^cat//}/${_i:T:R}.0
.  endfor
.endif
.if defined(MLINKS) && !empty(MLINKS)
.  for lnk file in ${MLINKS}
	@l=${DESTDIR}${MANDIR}${lnk:E}/${lnk:R}.0; \
	    t=${DESTDIR}${MANDIR}${file:E}/${file:R}.0; \
	    print -r -- $$t -\> $$l; rm -f $$t; \
	    ln $$l $$t || cp $$l $$t
.  endfor
.endif

.if defined(MANALL) && !defined(MANLOCALBUILD)
all: __MANALL

__MANALL: ${MANALL}

cleandir: cleanman
cleanman:
	rm -f ${MANALL}

.PHONY: __MANALL cleanman

.endif

.endif
