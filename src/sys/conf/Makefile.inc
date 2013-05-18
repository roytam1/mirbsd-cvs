# $MirOS: src/sys/conf/Makefile.inc,v 1.14 2006/06/12 21:57:09 tg Exp $
#-
# Copyright (c) 2005, 2006
#	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# This file includes most kernel compile rules commonly used, by all
# architectures' kernel Makefiles.

MKDEP?=	mkdep
SIZE?=	size
STRIP?=	strip

INCLUDES=	-nostdinc -I. -I$S/arch -I$S -I${BSDSRCDIR}/lib/libz
CDIAGFLAGS=	-Werror -Wall -Wstrict-prototypes -Wmissing-prototypes \
		-Wno-uninitialized -Wno-format -Wno-main -ffreestanding
.if ${IDENT:M-DNO_PROPOLICE}
CDIAGFLAGS+=	-fno-stack-protector
.endif
CDIAGFLAGS+=	-fno-builtin-printf -fno-builtin-log
COPTS?=		-O2
CFLAGS=		${DEBUG} ${CDIAGFLAGS} ${CMACHFLAGS} \
		${COPTS:S/-g//:C/-g[0-9]//} ${PIPE} ${CSYS}
AFLAGS=		-x assembler-with-cpp -traditional-cpp -D_LOCORE
STRIPFLAGS=	-g -X -x

# load lines for config "xxx" will be emitted as:
# xxx: ${SYSTEM_DEP} swapxxx.o
#	${SYSTEM_LD_HEAD}
#	${SYSTEM_LD} swapxxx.o
#	${SYSTEM_LD_TAIL}
SYSTEM_OBJ?=	locore.o tai_leaps.o init_ssp.o \
		param.o ioconf.o ${OBJS} ${LIBKERN} ${LIBCOMPAT}
SYSTEM_DEP?=	Makefile ${SYSTEM_OBJ}
SYSTEM_LD_HEAD?=rm -f $@
SYSTEM_LD?=	@echo ${LD} ${LINKFLAGS} -o $@ '$${SYSTEM_OBJ}' vers.o; \
		${LD} ${LINKFLAGS} -o $@ ${SYSTEM_OBJ} vers.o
SYSTEM_LD_TAIL?=@${SIZE} $@; chmod 755 $@
DEBUG?=
.if ${DEBUG} == "-g"
LINKFLAGS+=	-X
SYSTEM_LD_TAIL+=; \
		echo cp $@ $@.gdb; rm -f $@.gdb; cp $@ $@.gdb; \
		echo ${STRIP} ${STRIPFLAGS} $@; ${STRIP} ${STRIPFLAGS} $@
.else
LINKFLAGS+=	-x
.endif

SYSTEM_LD_TAIL+=; \
		echo Running kvm_mkdb...; kvm_mkdb -o . ./$@

.ifndef NO_GZIP
SYSTEM_LD_GZIP=	echo gzip -n9 $@; rm -f $@.gz; gzip -n9 $@; mv $@.gz $@
.endif

.if ${MKC_USAP:L} == "yes"
CPPFLAGS+=	-DMSDOSFS_NO_LFN
.endif

# XXX no a.out arches in MirOS?
CPPFLAGS+=	-DDB_NO_AOUT

HOSTCC=		${CC}
HOSTCPPFLAGS=	${CPPFLAGS:N-nostdinc:N-D_KERNEL}
HOSTCFLAGS?=	${CFLAGS}

### find out what to use for libkern
.include "$S/lib/libkern/Makefile.inc"
LIBKERN=	${KERNLIB}

### find out what to use for libcompat
.include "$S/compat/common/Makefile.inc"
LIBCOMPAT=	${COMPATLIB}

# compile rules: rules are named ${TYPE}_${SUFFIX}${CONFIG_DEP}
# where TYPE is NORMAL or DRIVER; SUFFIX is the file suffix,
# capitalized (e.g. C for a .c file), and CONFIG_DEP is _C if the file
# is marked as config-dependent.

NORMAL_C=	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
NORMAL_C_C=	${CC} ${CFLAGS} ${CPPFLAGS} ${PARAM} -c $<

DRIVER_C=	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
DRIVER_C_C=	${CC} ${CFLAGS} ${CPPFLAGS} ${PARAM} -c $<

NORMAL_S=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} -c $<
NORMAL_S_C=	${CC} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} ${PARAM} -c $<

HOSTED_C=	${HOSTCC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} -c $<

.MAIN: all

# these are 'make depend'ed
_COMMON_SRCS=	param.c ioconf.c tai_leaps.c
SRCS?=		${_MDINC}/locore.s ${_COMMON_SRCS} ${CFILES} ${SFILES}

# Propolice init
init_ssp.o: $S/kern/init_ssp.c
	${NORMAL_C} -fno-stack-protector

assym.h: $S/kern/genassym.sh ${_MDINC}/genassym.cf Makefile
	${SHELL} $S/kern/genassym.sh ${CC} ${CFLAGS} ${CPPFLAGS} \
	    ${PARAM} <${_MDINC}/genassym.cf >assym.h.tmp && \
	    mv -f assym.h.tmp assym.h

ioconf.o: ioconf.c
	${NORMAL_C}

locore.o: ${_MDINC}/locore.s assym.h
	${NORMAL_S}

param.c: $S/conf/param.c
	rm -f param.c
	cp $S/conf/param.c .

param.o: param.c Makefile
	${NORMAL_C_C}

tai_leaps.o: tai_leaps.c
	${NORMAL_C}

tai_leaps.c: $S/lib/libkern/tai_make.c
	${HOSTCC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} -o tai_make $>
	./tai_make >$@ || (rm -f $@; false)

# depend on root or device configuration
autoconf.o conf.o: Makefile

# depend on maxusers
machdep.o: Makefile

.PATH: ${BSDSRCDIR}/lib/libz
.include "${BSDSRCDIR}/lib/libz/Makefile.gen"

clean::
	rm -f eddep *bsd *bsd.gdb tags *.[io] [a-z]*.s \
	    [Ee]rrs linterrs makelinks genassym genassym.o assym.h

depend:: .depend
.depend: ${SRCS} assym.h param.c ${APMINC} crc32.h inffixed.h trees.h
	CC=${CC:Q} ${MKDEP} -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} \
	    ${_MDINC}/locore.s
	CC=${CC:Q} ${MKDEP} -a ${CFLAGS} ${CPPFLAGS} param.c ioconf.c ${CFILES}
.if defined(SFILES) && !empty(SFILES)
	CC=${CC:Q} ${MKDEP} -a -D_ASM_SOURCE ${AFLAGS} ${CPPFLAGS} ${SFILES}
.endif
	CC=${CC:Q} ${SHELL} $S/kern/genassym.sh ${MKDEP} -f assym.dep \
	    ${CFLAGS} ${CPPFLAGS} <${_MDINC}/genassym.cf
	@sed -e 's/.*\.o:.* /assym.h: /' <assym.dep >>.depend
	@rm -f assym.dep

install:
	@if [[ -e /bsd ]]; then \
		echo Move /bsd out of the way!; \
		exit 1; \
	elif [[ ! -e /bsd.old ]]; then \
		echo Back up your old kernel to /bsd.old!; \
		exit 1; \
	else \
		set -x; \
		install -c -o root -g daemon -m 400 bsd /; \
	fi

links:
	egrep '#if' ${CFILES} | sed -f $S/conf/defines | \
	  sed -e 's/:.*//' -e 's/\.c/.o/' | sort -u >dontlink
	echo ${CFILES} | tr -s ' ' '\12' | sed 's/\.c/.o/' | \
	  sort -u | comm -23 - dontlink | \
	  sed 's,.*/\(.*.o\),rm -f \1; ln -s ../GENERIC/\1 \1,' >makelinks
	${SHELL} makelinks && rm -f dontlink makelinks

lint:
	@lint -hbxncez -DGENERIC -Dvolatile= ${CPPFLAGS} ${PARAM} -UKGDB \
	    ${CFILES} ioconf.c param.c | \
	    grep -v 'static function .* unused'

newvers: ${SYSTEM_DEP} ${SYSTEM_SWAP_DEP}
	${SHELL} $S/conf/newvers.sh "${OSrev}" "${OSrpl}" "${OScompat}"
	${CC} ${CFLAGS} ${CPPFLAGS} -c vers.c

tags:
	@echo "see $S/kern/Makefile for tags"
