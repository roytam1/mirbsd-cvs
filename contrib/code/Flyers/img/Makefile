# $MirOS: contrib/code/Flyers/img/Makefile,v 1.1 2011/12/31 12:32:33 bsiegert Exp $

PDFFILES=	Flag_of_France.pdf
PDFFILES+=	Flag_of_Germany.pdf
PDFFILES+=	Flag_of_the_United_Kingdom.pdf
PDFFILES+=	bsdaemon.pdf
PDFFILES+=	m-color.pdf

GS?=		gs
AWK?=		awk

AWK_BBOX=	'/^%%BoundingBox:/ { \
			w = $$4 - $$2; h = $$5 - $$3; \
			print "<< /PageSize [", w, h, "] >> setpagedevice"}'

.SUFFIXES: .eps .pdf

all: ${PDFFILES}

clean:
	rm -f ${PDFFILES}

.PHONY: all clean

.eps.pdf:
	${GS} -q -dBATCH -dNOPAUSE -dSAFER -sDEVICE=pdfwrite \
		-sOutputFile=${.TARGET} -c `${AWK} ${AWK_BBOX} ${.ALLSRC}` \
		-f ${.ALLSRC}
