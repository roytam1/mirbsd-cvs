# $MirOS$

PROGS=		dosint mode3 vbemodeinfo vbetest vga_reset vbetool
MAN=		vbetool.1
BINDIR?=	${BSD_PREFIX}/sbin
LDADD+=		-llrmi

all: ${PROGS}

.for _i in ${PROGS}
${_i}:
	${MAKE} -f ${.SYSMK}/bsd.prog.mk PROG=$@ NOMAN=Yes \
	    LTMIRMAKE=Yes LDADD=${LDADD:M*:Q}
.endfor

.include <bsd.prog.mk>
