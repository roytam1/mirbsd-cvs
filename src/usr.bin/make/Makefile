# $MirOS: src/usr.bin/make/Makefile,v 1.5 2005/11/24 12:37:43 tg Exp $
# $OpenBSD: Makefile,v 1.38 2004/01/28 02:50:28 espie Exp $

.include <bsd.own.mk>

PROG=		make
CDIAGFLAGS=	-Wall -W -Wno-char-subscripts -Wstrict-prototypes -pedantic \
		-Wmissing-prototypes -Werror -Wno-cast-qual
#CPPFLAGS+=	-DHAS_STATS	# Throw out statistics after running
CPPFLAGS+=	-I. -DMACHINE=\"${MACHINE}\" -DMACHINE_ARCH=\"${MACHINE_ARCH}\"

SRCS=	arch.c buf.c cmd_exec.c compat.c cond.c dir.c error.c for.c \
	init.c job.c lowparse.c main.c make.c memory.c parse.c \
	parsevar.c str.c stats.c suff.c targ.c timestamp.c \
	var.c varmodifiers.c varname.c
SRCS+=	lstAddNew.c lstAppend.c lstConcat.c lstConcatDestroy.c \
	lstDeQueue.c lstDestroy.c lstDupl.c lstFindFrom.c lstForEachFrom.c \
	lstInsert.c lstMember.c lstRemove.c lstReplace.c lstSucc.c
.PATH:	${.CURDIR}/lst.lib

.ifdef MAKE_BOOTSTRAP
MKFEATURES?=	-DNEED_FGETLN -D_PATH_DEFSYSPATH=\"/usr/share/mk\" \
		-DHAS_STDBOOL_H # -DNEED_VSNPRINTF # -DNO_REGEX
CPPFLAGS+=	-Iohash -DMACHINE_OS=\"${MACHINE_OS}\" -DMAKE_BOOTSTRAP
SRCS+=		ohash_create_entry.c ohash_delete.c ohash_do.c \
		ohash_entries.c ohash_enum.c ohash_init.c ohash_interval.c \
		ohash_lookup_interval.c ohash_lookup_memory.c \
		ohash_qlookup.c ohash_qlookupi.c
.PATH:		${.CURDIR}/ohash
.else
MKFEATURES?=	-DUSE_TIMESPEC
.endif
CPPFLAGS+=	${MKFEATURES} -D_PATH_MIRBSDKSH=\"${MKSH}\"

.if !exists(${MKSH})
.BEGIN:
	@echo 'You know, $${MKSH} (${MKSH}) should exist!'
	@exit 1
.endif

make.1: ${.CURDIR}/make.1
	sed -e 's#@@MKSH@@#${MKSH}#g' <$> >$@

CLEANFILES+=	${LIBOBJS} check condhashconsts.h generate.o generate \
		hashconsts.h libohash.a regress.o varhashconsts.h
.if ${.OBJDIR} != ${.CURDIR}
CLEANFILES+=	make.1
.endif

beforedepend: varhashconsts.h condhashconsts.h
# may need tweaking if you add variable synonyms or change the hash function
MAGICVARSLOTS=	82
MAGICCONDSLOTS=	65

varhashconsts.h: generate
	${.OBJDIR}/generate 1 ${MAGICVARSLOTS} >$@

condhashconsts.h: generate
	${.OBJDIR}/generate 2 ${MAGICCONDSLOTS} >$@

generate: generate.c stats.c memory.c
	${HOSTCC} ${LDSTATIC} -o $@ ${CFLAGS} ${CPPFLAGS} $> ${LDADD}

check: regress.o str.o memory.o buf.o
	${CC} -o $@ ${CFLAGS} $> ${LDADD}

regress: check
	${.OBJDIR}/check

.if make(install)
SUBDIR+= PSD.doc
.endif

.PHONY: regress

.include <bsd.prog.mk>
