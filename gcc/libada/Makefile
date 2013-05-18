# $MirOS: gcc/libada/Makefile,v 1.4 2007/06/10 13:16:11 tg Exp $

.include "../Makefile.inc"

.ifdef _CROSSBUILD
FLAGS+=	ALL_TARGET='gnatlib cross-gnattools ada.all.cross'
FLAGS+=	GNATLIBCFLAGS=${CROSSCFLAGS:M*:Q}
.elif ${CROSS_MODE:L} == "yes"
FLAGS+=	ALL_TARGET=gnattools-xnative DO_XNATIVE=yes
FLAGS+=	GNATLIBCFLAGS=${CFLAGS:M*:Q}
.else
FLAGS+=	ALL_TARGET=gnatlib_and_tools
.endif

all:
	cd ${.CURDIR}/../gcc && ${MAKE} -f Makefile.bsd-wrapper ${FLAGS}

clean cleandir depend includes install lint obj prereq tags:
