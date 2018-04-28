# $MirOS: src/sys/conf/Makefile.inc,v 1.43 2014/11/26 19:29:30 tg Exp $
#-
# Copyright (c) 2005, 2006, 2007, 2008, 2018
#	mirabilos <m@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# This file includes most kernel compile rules commonly used, by all
# architectures' kernel Makefiles.

MKDEP?=		mkdep
SIZE?=		size
STRIP?=		strip

KERNBASE?=	$S/../kern

depend:: beforedepend .WAIT

INCLUDES=	-nostdinc -I. -I$S/arch -I$S -I${KERNBASE}/include
CDIAGFLAGS=	-Werror -Wall -Wstrict-prototypes -Wmissing-prototypes \
		-Wno-uninitialized -Wno-main -ffreestanding
.if ${IDENT:M-DNO_PROPOLICE}
CDIAGFLAGS+=	-fno-stack-protector
.endif
COPTS?=		-Os
.if ${COPTS:M-O*:N-Os}
COPTS+=		-Os
.endif
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
CFLAGS=		${DEBUG} ${CDIAGFLAGS} ${CMACHFLAGS} \
		${COPTS:C/-g[0-9]//:S/-g//} ${PIPE} ${CSYS}
AFLAGS=		-x assembler-with-cpp -traditional-cpp -D_LOCORE
STRIPFLAGS=	-g -X -x -R .comment

.include "${KERNBASE}/z/Makefile.inc"

# load lines for config "xxx" will be emitted as:
# xxx: ${SYSTEM_DEP} swapxxx.o newvers
#	${SYSTEM_LD_HEAD}
#	${SYSTEM_LD} swapxxx.o
#	${SYSTEM_LD_TAIL}
#	@${SYSTEM_LD_GZIP}
SYSTEM_OBJ?=	locore.o init_ssp.o config_gz.o mirtime_getleaps.o \
		param.o ioconf.o ${OBJS} ${LIBKERN} ${LIBCOMPAT}
SYSTEM_DEP?=	Makefile ${SYSTEM_OBJ}
SYSTEM_LD_HEAD?=rm -f $@ $@~
SYSTEM_LD?=	@echo ${LD} ${LINKFLAGS} -o $@~ '$${SYSTEM_OBJ}' vers.o; \
		${LD} ${LINKFLAGS} -o $@~ ${SYSTEM_OBJ} vers.o
SYSTEM_LD_TAIL?=@set -e; ${SIZE} $@~; chmod 755 $@~
DEBUG?=
SYSTEM_LD_TAIL+=; \
		echo cp $@~ $@.unstripped; \
		rm -f $@.unstripped; cp $@~ $@.unstripped; \
		echo Running kvm_mkdb...; \
		kvm_mkdb -o . ./$@~; \
		mv kvm_$@~.db kvm_$@.db
.if ${DEBUG} == "-g"
LINKFLAGS+=	-X
SYSTEM_LD_TAIL+=; \
		echo ${STRIP} ${STRIPFLAGS} $@~; ${STRIP} ${STRIPFLAGS} $@~
.else
LINKFLAGS+=	-x
SYSTEM_LD_TAIL+=; \
		objcopy -R .comment $@~
.endif
SYSTEM_LD_POST?=:
SYSTEM_LD_TAIL+=; \
		${SYSTEM_LD_POST}
.ifndef NO_GZIP
SYSTEM_LD_GZIP=	echo gzip -n9 $@; gzip -fn9 -o $@ $@~
.else
SYSTEM_LD_GZIP=	mv $@~ $@
.endif

# currently always, not because patents but because broken
CPPFLAGS+=	-DMSDOSFS_NO_LFN

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
_COMMON_SRCS=	param.c ioconf.c
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

# depend on root or device configuration
autoconf.o conf.o: Makefile

# depend on maxusers
machdep.o: Makefile

config_gz.o: $S/conf/config_gz.S config.gz
	${NORMAL_S}

mirtime_getleaps.c: $S/conf/make_leaps.c
	${HOSTCC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} -o make_leaps $>
	./make_leaps >$@ || (rm -f $@; false)

config.gz: config.txt
	-@rm -f $@
	gzip -n9 <$> >$@

clean::
	rm -f eddep *bsd *.unstripped tags *.[io] [a-z]*.s config.gz \
	    [Ee]rrs linterrs makelinks genassym genassym.o assym.h \
	    make_leaps mirtime_getleaps.c ${ZLIB_CLEANFLS}

depend:: .depend
beforedepend:
	rm -f syskern
	ln -s ${KERNBASE:Q}/include syskern
.depend: ${SRCS} assym.h param.c ${APMINC} ${ZLIB_GENHDRS} mirtime_getleaps.c
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

INSTALL_KERNEL=	bsd
install-unstripped:
	@cd ${.CURDIR} && exec ${MAKE} install INSTALL_KERNEL=bsd.unstripped
install:
	@if [[ -e /bsd ]]; then \
		echo Move /bsd out of the way!; \
		exit 1; \
	elif [[ ! -e /bsd.old ]]; then \
		echo Back up your old kernel to /bsd.old!; \
		exit 1; \
	else \
		set -x; \
		install -c -o root -g daemon -m 400 ${INSTALL_KERNEL} /bsd; \
		install -c -o root -g wheel -m 644 \
		    kvm_bsd.db /var/db/kvm_bsd.new; \
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
