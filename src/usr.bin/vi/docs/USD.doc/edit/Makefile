# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/02/09 21:09:10 jmc Exp $

DIR=	usd/11.edit
SRCS=	edittut.ms
MACROS=	-ms

# index for versatec is different from the one in edit.tut
# because the fonts are different and entries reference page
# rather than section numbers.  if you have a typesetter
# you should just use the index in edit.tut, and ignore editvindex.

editvindex:
	${TROFF} ${MACROS} -n22 edit.vindex

.include <bsd.doc.mk>
