# $MirOS: src/share/doc/papers/memfs/Makefile,v 1.2 2005/03/06 19:38:20 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/02/01 14:22:44 jmc Exp $

DIR=	papers/memfs
SRCS=	0.t 1.t
MACROS=	-ms
REFER=	refer -n -e -l -s -p ref.bib
EXTRA=	ref.bib A.t tmac.srefs
CLEANFILES=ref.bib.i{,a,b,c} A.gt paper.t

paper.ps: paper.t
	${ROFF} tmac.srefs paper.t >${.TARGET}

paper.t: ${SRCS} ref.bib.i A.gt
	${REFER} ${SRCS} A.gt >${.TARGET}

ref.bib.i: ref.bib
	${INDXBIB} ref.bib

A.gt: A.t
	${GRIND} - <A.t >A.gt

.include <bsd.doc.mk>
