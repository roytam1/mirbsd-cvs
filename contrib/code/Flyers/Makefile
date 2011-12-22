all: de.pdf

.SUFFIXES: .tex .pdf

.tex.pdf:
	xelatex -output-driver="xdvipdfmx -q -E -p a4 -l" $<
	
