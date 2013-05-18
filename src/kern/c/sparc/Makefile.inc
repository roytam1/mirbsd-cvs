# $MirOS: src/kern/c/sparc/Makefile.inc,v 1.12 2010/01/10 20:18:49 tg Exp $

XSRCS+=		htonl.c htons.c ntohl.c ntohs.c

XSRCS+=		strlen.S
LSRCS+=		strlen.c
UIF_NUSRCS+=	wcslen.c strlen.c -DWIDEC

XSRCS+=		strchr.c strrchr.c
XSRCS+=		strncmp.c
XSRCS+=		strncpy.c

UIF_KUSRCS+=	mempcpy.c memcpy.c -DL_mempcpy

XSRCS+=		bzero.S ffs.S memchr.c memcmp.c memcpy.c memset.c strcmp.c
LSRCS+=		Lbzero.c Lffs.c

# broken standard API
CFLAGS_memchr.o= -Wno-cast-qual
CFLAGS_strchr.o= -Wno-cast-qual
CFLAGS_strrchr.o= -Wno-cast-qual

XSRCS+=		mul.S umul.S
KUSRCS+=	fixunsdfsi.S
XSRCS+=		saveregs.S

XSRCS+=		rem.S sdiv.S udiv.S urem.S
CLEANFILES+=	rem.S sdiv.S udiv.S urem.S

.for _t _n _o _s in \
    sdiv div div true \
    udiv udiv div false \
    rem rem rem true \
    urem urem rem false
${_t}.S: ${KERNBASE}/c/sparc/divrem.m4
	@print building ${.TARGET:Q} from ${.ALLSRC:Q}
	@(print "define(NAME,\`.${_n}')define(NAME2,\`_C_LABEL(_${_n})')define(OP,\`${_o}')define(S,\`${_s}')"; \
	  cat ${.ALLSRC}) | m4 >$@
.endfor
