# $MirOS: src/kern/c/sparc/Makefile.inc,v 1.4 2008/08/01 18:09:21 tg Exp $

SRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
LSRCS+=		strlen.c
UIF_KUSRCS+=	wcslen.c strlen.c -DWIDEC

SRCS+=		bzero.S ffs.S memchr.c memcmp.c memset.c strcmp.c
UNIFDEF_SRCS+=	bcmp.c memcmp.c -DL_bcmp
UNIFDEF_SRCS+=	strcoll.c strcmp.c -DL_strcoll
LSRCS+=		Lbzero.c Lffs.c

SRCS+=		mul.S umul.S
SRCS+=		saveregs.S

SRCS+=		rem.S sdiv.S udiv.S urem.S
CLEANFILES+=	rem.S sdiv.S udiv.S urem.S

.for _t _n _o _s in \
    sdiv div div true \
    udiv udiv div false \
    rem rem rem true \
    urem urem rem false
${_t}.S: ${KERNBASE}/c/sparc/divrem.m4
	@print building ${.TARGET:Q} from ${.ALLSRC:Q}
	@(print "define(NAME,\`.${_n}')define(OP,\`${_o}')define(S,\`${_s}')"; \
	  cat ${.ALLSRC}) | m4 >$@
.endfor
