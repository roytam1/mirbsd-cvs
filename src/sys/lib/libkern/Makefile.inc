#	$MirOS: src/sys/lib/libkern/Makefile.inc,v 1.3 2006/02/01 19:22:45 tg Exp $
#	$OpenBSD: Makefile.inc,v 1.11 2000/06/29 16:28:29 mickey Exp $
#	$NetBSD: Makefile.inc,v 1.22 1996/09/30 15:54:35 ws Exp $
#
#	NOTE: $S must correspond to the top of the 'sys' tree

KERNDIR=	$S/lib/libkern

KERNDST?=	${.OBJDIR}/lib/kern
KERN_AS?=	obj

.if (${KERN_AS} == "library")
KERNLIB=	${KERNDST}/libkern.a
.else
KERNLIB=	${KERNDST}/libkern.o
.endif

KERNMAKE= \
	cd ${KERNDIR} && MAKEOBJDIR=${KERNDST} ${MAKE} S=${S:Q} \
	    CC=${CC:Q} CFLAGS=${CFLAGS:Q} AS=${AS:Q} AFLAGS=${AFLAGS:Q} \
	    LD=${LD:Q} STRIP=${STRIP:Q} CPP=${CPP:Q} STRIP=${STRIP:Q} \
	    AR=${AR:Q} NM=${NM:Q} LORDER=${LORDER:Q} XMACHINE=${MACHINE:Q} \
	    XMACHINE_ARCH=${MACHINE_ARCH:Q} KERNDIR=${KERNDIR} COPTS= \
	    KERNCPPFLAGS=${CPPFLAGS:S@^-I.@-I../../.@g:Q}

${KERNLIB}:		.NOTMAIN __always_make_kernlib
	@echo making sure the kern library is up to date...
.if (${KERN_AS} == "library")
	@${KERNMAKE} libkern.a
.else
	@${KERNMAKE} libkern.o
.endif

clean::			.NOTMAIN __always_make_kernlib
	@echo cleaning the kern library objects
	@${KERNMAKE} clean

depend:: 		.NOTMAIN __always_make_kernlib
	@echo depending the kern library objects
	@${KERNMAKE} depend

__always_make_kernlib:	.NOTMAIN
	-mkdir -p ${KERNDST}
