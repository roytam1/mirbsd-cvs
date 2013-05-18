# $MirOS: gcc/libada/Makefile,v 1.2 2007/06/10 03:19:27 tg Exp $

.ifdef _CROSSBUILD
FLAGS+=	ALL_TARGET='gnatlib cross-gnattools ada.all.cross'
FLAGS+=	GNATLIBCFLAGS=${CROSSCFLAGS:M*:Q}
.elif ${CROSS_MODE:L} == "yes"
FLAGS+=	ALL_TARGET=gnattools-xnative
FLAGS+=	GNATLIBCFLAGS=${CFLAGS:M*:Q}
.else
FLAGS+=	ALL_TARGET=gnatlib_and_tools
.endif

all:
	cd ${.CURDIR}/../gcc && ${MAKE} -f Makefile.bsd-wrapper ${FLAGS}

clean cleandir depend includes install lint obj prereq tags:
