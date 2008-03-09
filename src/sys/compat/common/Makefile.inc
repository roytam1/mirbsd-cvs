# $MirOS: src/sys/compat/common/Makefile.inc,v 1.3 2006/02/01 19:22:45 tg Exp $
# $OpenBSD: Makefile.inc,v 1.7 2002/07/14 09:20:24 mdw Exp $
# $NetBSD: Makefile.inc,v 1.5 1996/05/20 17:23:59 mrg Exp $
#
#	NOTE: $S must correspond to the top of the 'sys' tree

PWD!=		readlink -nf .
COMPATDIR!=	readlink -nf $S/compat/common
COMPATDST?=	lib/compat
COMPATLIB=	${COMPATDST}/libcompat.a

COMPATMAKE= \
	cd ${COMPATDST} && ${MAKE} -f ${COMPATDIR}/Makefile \
	    CC=${CC:Q} CFLAGS=${CFLAGS:S/-I./-I${PWD}\/./g:Q} \
	    LD=${LD:Q} AR=${AR:Q} RANLIB=${RANLIB:Q} LORDER=${LORDER:Q} \
	    NM=${NM:Q} COPTS= \
	    XMACHINE=${MACHINE:Q} XMACHINE_ARCH=${MACHINE_ARCH:Q} \
	    CPPFLAGS=${CPPFLAGS:S/-I./-I${PWD}\/./g:Q} \
	    COMPATDIR=${COMPATDIR:Q}

${COMPATLIB}:		.NOTMAIN __always_make_compatlib
	@echo making sure the compat library is up to date...
	@${COMPATMAKE} libcompat.a

clean:: 		.NOTMAIN __always_make_compatlib
	@echo cleaning the compat library objects
	@${COMPATMAKE} clean

depend:: 		.NOTMAIN __always_make_compatlib
	@echo depending the compat library objects
	@${COMPATMAKE} depend

__always_make_compatlib:	.NOTMAIN
	@mkdir -p ${COMPATDST}
