# $MirOS: src/gnu/usr.bin/rcs/Makefile,v 1.2 2005/04/19 21:30:31 tg Exp $

.include <bsd.own.mk>

  PROGS+= ci
  PROGS+= co
  PROGS+= ident
  PROGS+= merge
  PROGS+= rcs
  PROGS+= rcsclean
  PROGS+= rcsdiff
  PROGS+= rcsfreeze
  PROGS+= rcsmerge
  PROGS+= rlog

  SUBDIR+= lib
  SUBDIR+= ${PROGS}
.if ${NOMAN:L} == "no"
  SUBDIR+= man
.endif
.if make(install)
  SUBDIR+= paper
.endif
  SUBDIR+= getdate

VERBOSE=

check:
	mkdir -p test; \
	    for i in ${PROGS}; do \
		ln -f $$i/$$i test/; \
	    done; \
	    cd test; \
	    PATH=".:$$PATH" CC="${CC}" ALL_CFLAGS="${CFLAGS} ${COPTS}" \
	    ${SHELL} ${.CURDIR}/src/rcstest ${VERBOSE} 2>&1
	-rm -rf test
	@echo Check successful.

check-v:
	cd ${.CURDIR} && ${MAKE} check VERBOSE=-v

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
