# $MirOS$

PDFFILES=	Flag_of_France.pdf
PDFFILES+=	Flag_of_Germany.pdf
PDFFILES+=	Flag_of_the_United_Kingdom.pdf
PDFFILES+=	bsdaemon.pdf
PDFFILES+=	m-color.pdf

.SUFFIXES: .eps .pdf

all: ${PDFFILES}

clean:
	rm -f ${PDFFILES}

.PHONY: all clean

.eps.pdf:
	ps2pdf $<
