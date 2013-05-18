# $MirOS: src/usr.bin/make/Makefile.boot,v 1.7 2005/11/24 12:49:37 tg Exp $
# $OpenPackages: Makefile.boot,v 1.5 2001/04/06 00:09:55 will Exp $
# $OpenBSD: Makefile.boot,v 1.8 2001/05/29 12:41:18 espie Exp $
#
# a very simple makefile...
#
# You only want to use this if you aren't running MirOS.
#
# modify MACHINE and MACHINE_ARCH as appropriate for your target architecture

#------------------------------
# System dependencies
#------------------------------

#MACHINE=sun
#MACHINE_ARCH=sparc
MACHINE=i386
MACHINE_ARCH=i386
MACHINE_OS=BSD

# set this to the true path of mirbsdksh
MKSH=		/bin/mksh

# some make(1)s don't support +=
DEFS=		-DMAKE_BOOTSTRAP #-DNEED_VSNPRINTF
#DEFS_RE=	-DNO_REGEX

# paths
LIBCDIR=	/usr/src/lib/libc
INCLDIR=	/usr/src/include

#==============================

.c.o:
	${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@

CFLAGS= -Iohash -I. ${DEFS} ${DEFS_RE} ${COPTS} -DMACHINE=\"${MACHINE}\" \
	-DMACHINE_ARCH=\"${MACHINE_ARCH}\" -DMACHINE_OS=\"${MACHINE_OS}\" \
	-D_PATH_MIRBSDKSH=\"${MKSH}\" -D_PATH_DEFSYSPATH=\"/usr/share/mk\"
LIBS=	ohash/libohash.a

OBJ=	arch.o buf.o compat.o cond.o dir.o for.o job.o main.o make.o \
	parse.o str.o suff.o targ.o var.o util.o error.o lowparse.o \
	varmodifiers.o memory.o cmd_exec.o timestamp.o parsevar.o \
	varname.o init.o strlfun.o getopt_long.o fgetln.o

LIBOBJ=	lst.lib/lstAddNew.o lst.lib/lstAppend.o \
	lst.lib/lstConcat.o lst.lib/lstConcatDestroy.o lst.lib/lstDeQueue.o \
	lst.lib/lstDestroy.o lst.lib/lstDupl.o lst.lib/lstFindFrom.o \
	lst.lib/lstForEachFrom.o lst.lib/lstInsert.o \
	lst.lib/lstMember.o lst.lib/lstRemove.o lst.lib/lstReplace.o \
	lst.lib/lstSucc.o

bmake: varhashconsts.h condhashconsts.h ${OBJ} ${LIBOBJ}
#	@echo 'make of make and make.0 started.'
	${CC} ${CFLAGS} ${OBJ} ${LIBOBJ} -o bmake ${LIBS}
	@ls -l $@
#	nroff -h -man make.1 >make.0
#	@echo 'make of make and make.0 completed.'

GENOBJ= generate.o stats.o memory.o ohash/libohash.a

OHASHOBJ= ohash/ohash_create_entry.o ohash/ohash_delete.o ohash/ohash_do.o \
	ohash/ohash_entries.o ohash/ohash_enum.o ohash/ohash_init.o \
	ohash/ohash_interval.o ohash/ohash_lookup_interval.o \
	ohash/ohash_lookup_memory.o ohash/ohash_qlookup.o \
	ohash/ohash_qlookupi.o

ohash/libohash.a: ${OHASHOBJ}
	ar cq ohash/libohash.a ${OHASHOBJ}
	ranlib ohash/libohash.a

generate: ${GENOBJ}
	${CC} ${CFLAGS} ${GENOBJ} -o generate ${LIBS}

varhashconsts.h: generate
	./generate 1 82 >varhashconsts.h

condhashconsts.h: generate
	./generate 2 65 >condhashconsts.h

clean:
	rm -f ${OBJ} ${LIBOBJ} ${PORTOBJ} ${GENOBJ} ${OHASHOBJ} bmake
	rm -f varhashconsts.h condhashconsts.h generate
