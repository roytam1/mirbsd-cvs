# $MirOS: src/distrib/tools/Makefile,v 1.2 2007/09/28 22:44:36 tg Exp $

all: i386_chain sundsklbl

.include <bsd.own.mk>

CHAINSECTOR?=	24
CDROM?=		cdrom${OSrev}.iso

CPPFLAGS+=	-DCHAINSECTOR=${CHAINSECTOR}

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

makebootcd_i386:
	/usr/mdec/installboot -S 24 -v -I $$(fgrep \
	    b_i386.ldr mkisofs.log | \
	    while read start end rest; do \
		print -- $$start $$end; \
	done) /usr/mdec/bootxx ${CDROM}

makebootcd_sparc:
	# XXX see ../common/Makefile.sparc::cdrom-mdboot if this doesn’t work
	/usr/mdec/installboot -v $$(fgrep \
	    b_sparc.ldr mkisofs.log | \
	    while read start end rest; do \
		print -- -s $$start -e $$end; \
	done) dummy /usr/mdec/bootxx ${CDROM}

.include <bsd.obj.mk>
