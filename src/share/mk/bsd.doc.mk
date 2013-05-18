# $MirOS: src/share/mk/bsd.doc.mk,v 1.2 2005/02/14 18:57:46 tg Exp $
# $OpenBSD: bsd.doc.mk,v 1.8 2001/04/03 23:00:09 espie Exp $
# $NetBSD: bsd.doc.mk,v 1.20 1994/07/26 19:42:37 mycroft Exp $
# @(#)bsd.doc.mk	8.1 (Berkeley) 8/14/93

.if !defined(BSD_DOC_MK)
BSD_DOC_MK=1

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

FILES?=	${SRCS}
.PATH: ${.CURDIR}

.if !target(all)
.MAIN: all
.  if target(paper.)
all:
	@echo 'Fix Makefile and replace paper.$${PRINTER} target by paper.ps'
	@false
.  else
all: paper.txt
.  endif
.endif

.if !target(paper.ps)
paper.ps: ${SRCS}
	${TBL} ${SRCS} | ${ROFF} >${.TARGET}
.endif

.if !target(paper.txt)
paper.txt: ${SRCS}
	@(test -e paper.ps && mv paper.ps paper.tmp) 2>/dev/null || true
	@${MAKE} paper.ps 'ROFF=${NROFF}' 2>&1 | sed 's/paper\.ps/$@/'
	@mv paper.ps $@ || { mv paper.tmp paper.ps 2>/dev/null; false; }
	@mv paper.tmp paper.ps 2>/dev/null || true
.endif

.if !target(print)
print: paper.ps
	lpr -P${PRINTER} paper.ps
.endif

.if !target(manpages)
manpages:
.endif

.if !target(obj)
obj:
.endif

clean cleandir:
	rm -f paper.{txt,tmp,ps} [eE]rrs mklog ${CLEANFILES}

install:
	${INSTALL} ${INSTALL_COPY} -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    Makefile ${FILES} ${EXTRA} ${DESTDIR}${DOCDIR}/${DIR}/

spell: paper.spell

paper.spell: ${SRCS}
	spell ${SRCS} | sort | comm -23 - spell.ok >paper.spell

.endif
