# $MirOS$
# $OpenBSD: Makefile,v 1.2 1996/09/25 06:40:52 etheisen Exp $

PROG=		crunchgen
SRCS=		crunchgen.c crunched_skel.c
CFLAGS+=	-Wall
CPPFLAGS+=	-DMF_NAMES='"Makefile.bsd-wrapper","Makefile"'
CLEANFILES+=	crunched_skel.c

crunched_skel.c: crunched_main.c
	print '#include <stdlib.h>\nconst char *crunched_skel[] = {' >$@
	sed -e 's/\\/&&/g' -e 's/"/\\"/g' -e 's/^.*$$/	"&",/' $> >>$@
	print '	NULL\n};' >>$@

.include <bsd.prog.mk>
