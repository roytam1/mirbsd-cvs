# $MirOS$

all: i386_chain sundsklbl

.include <bsd.own.mk>

depend:
prereq:

clean: .PHONY
	-rm -f i386_chain sundsklbl *.o

cleandir: .PHONY clean

i386_chain: i386_chain.o
	ld -o $@ --oformat binary -Ttext 0 $>

sundsklbl: sundsklbl.c
	cd ${.CURDIR} && ${MAKE} -f ${.SYSMK}/bsd.prog.mk \
	    PROG=$@ NOMAN=Yes EXPERIMENTAL=Yes

.include <bsd.obj.mk>
