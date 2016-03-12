# $MirOS: src/distrib/special/ed/Makefile,v 1.2 2011/04/09 17:23:27 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/bin/pax

PROG=		pax
SRCS=		ar_io.c ar_subs.c buf_subs.c cache.c cpio.c file_subs.c \
		ftree.c gen_subs.c getoldopt.c options.c pat_rep.c pax.c \
		sel_subs.c tables.c tar.c tty_subs.c
CPPFLAGS+=	-DHAVE_STRLCPY
CPPFLAGS+=	-DHAVE_STRMODE
CPPFLAGS+=	-DHAVE_VIS
CPPFLAGS+=	-DSMALL

.include <bsd.prog.mk>
