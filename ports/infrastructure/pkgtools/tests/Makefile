# Makefile for MirPorts tests

regress: test-cfgfile
	prove *.t

.include <bsd.own.mk>
.include <../Makefile.inc>

test-cfgfile: test-cfgfile.o
	${CC} ${LDFLAGS} ${LDSTATIC} -o $@ $> ${LDADD}

test-cfgfile.o: test-cfgfile.c

clean:
	rm -f test-cfgfile.o test-cfgfile

.PHONY: regress clean
