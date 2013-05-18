# $MirOS: src/sys/conf/Makefile.inc,v 1.6 2006/01/15 23:46:37 tg Exp $
#-
# Copyright (c) 2005, 2006
#	Thorsten "mirabile" Glaser <tg@mirbsd.de>
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

.ifndef NO_GZIP
SYSTEM_LD_GZIP=	echo gzip -9 $@; rm -f $@.gz; gzip -9 $@; mv $@.gz $@
.endif

.if ${MKC_USAP:L} == "yes"
CPPFLAGS+=	-DMSDOSFS_NO_LFN
.endif

HOSTCC=		${CC}
HOSTED_CPPFLAGS=${CPPFLAGS:N-nostdinc:N-D_KERNEL}
HOSTED_CFLAGS=	${CFLAGS}

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

NORMAL_S=	${CC} ${AFLAGS} ${CPPFLAGS} -c $<
NORMAL_S_C=	${CC} ${AFLAGS} ${CPPFLAGS} ${PARAM} -c $<

HOSTED_C=	${HOSTCC} ${HOSTED_CFLAGS} ${HOSTED_CPPFLAGS} -c $<

.MAIN: all

# Propolice init
init_ssp.o: $S/kern/init_ssp.c
	${NORMAL_C} -fno-stack-protector

param.c: $S/conf/param.c
	rm -f param.c
	cp $S/conf/param.c .

param.o: param.c Makefile
	${NORMAL_C_C}

ioconf.o: ioconf.c
	${NORMAL_C}

tai_leaps.o: tai_leaps.c
	${NORMAL_C}

tai_leaps.c: tai_make
	./tai_make >$@ || (rm -f $@; false)

tai_make: tai_make.o
	${HOSTCC} ${HOSTED_CFLAGS} -o $@ $>

tai_make.o: $S/lib/libkern/tai_make.c
	${HOSTED_C}

.PATH: ${BSDSRCDIR}/lib/libz
.include "${BSDSRCDIR}/lib/libz/Makefile.gen"

# libz generated headers
.depend: crc32.h inffixed.h trees.h

newvers: ${SYSTEM_DEP} ${SYSTEM_SWAP_DEP}
	${SHELL} $S/conf/newvers.sh "${OSrev}" "${OSrpl}" "${OScompat}"
	${CC} ${CFLAGS} ${CPPFLAGS} -c vers.c

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

clean::
	rm -f eddep *bsd *bsd.gdb tags *.[io] [a-z]*.s \
	    [Ee]rrs linterrs makelinks genassym genassym.o assym.h

lint:
	@lint -hbxncez -DGENERIC -Dvolatile= ${CPPFLAGS} ${PARAM} -UKGDB \
	    ${CFILES} ioconf.c param.c | \
	    grep -v 'static function .* unused'

tags:
	@echo "see $S/kern/Makefile for tags"

links:
	egrep '#if' ${CFILES} | sed -f $S/conf/defines | \
	  sed -e 's/:.*//' -e 's/\.c/.o/' | sort -u >dontlink
	echo ${CFILES} | tr -s ' ' '\12' | sed 's/\.c/.o/' | \
	  sort -u | comm -23 - dontlink | \
	  sed 's,.*/\(.*.o\),rm -f \1; ln -s ../GENERIC/\1 \1,' >makelinks
	${SHELL} makelinks && rm -f dontlink makelinks

# depend on root or device configuration
autoconf.o conf.o: Makefile

# depend on maxusers
machdep.o: Makefile
