# $MirOS$

PDFFILES=	de.pdf

.SUFFIXES: .tex .pdf

all:
	(cd img && exec ${MAKE} ${MAKE_FLAGS} $@)
	${MAKE} ${PDFFILES}

clean:
	(cd img && exec ${MAKE} ${MAKE_FLAGS} $@)
	rm -f ${PDFFILES}
	rm -f *.aux *.log *.*.synctex* 

.PHONY: all clean

.tex.pdf:
	xelatex -output-driver="xdvipdfmx -q -E -p a4 -l" $<
	
