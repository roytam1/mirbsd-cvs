# $MirOS: src/lib/libedit/Makefile,v 1.9 2007/08/07 21:21:26 tg Exp $
# $NetBSD: Makefile,v 1.29 2003/12/05 13:37:48 lukem Exp $
# @(#)Makefile	8.1 (Berkeley) 6/4/93

SHLIB_VERSION?=	7.0

LIB=	edit
DPADD+=	${LIBTERMCAP}
LDADD+=	-ltermcap

OSRCS=	chared.c common.c el.c emacs.c fcns.c help.c hist.c key.c map.c \
	parse.c prompt.c read.c refresh.c search.c sig.c term.c tty.c vi.c

MAN=	editline.3 editrc.5

MLINKS=	editline.3 el_init.3 editline.3 el_end.3 editline.3 el_reset.3 \
	editline.3 el_gets.3 editline.3 el_getc.3 editline.3 el_push.3 \
	editline.3 el_parse.3 editline.3 el_set.3 editline.3 el_get.3 \
	editline.3 el_source.3 editline.3 el_resize.3 editline.3 el_line.3 \
	editline.3 el_insertstr.3 editline.3 el_deletestr.3 \
	editline.3 history_init.3 editline.3 history_end.3 \
	editline.3 history.3 \
	editline.3 tok_init.3 editline.3 tok_end.3 editline.3 tok_reset.3 \
	editline.3 tok_line.3 editline.3 tok_str.3

# For speed and debugging
#SRCS=		${OSRCS} tokenizer.c history.c readline.c
# For protection
SRCS=		editline.c tokenizer.c history.c readline.c

LIBEDITDIR?=	${.CURDIR}

HDRS2=		histedit.h histedit.h readline/readline.h readline/readline.h

.include <bsd.own.mk>
CLEANFILES+=	editline.c
CLEANFILES+=	common.h.tmp editline.c.tmp emacs.h.tmp fcns.c.tmp fcns.h.tmp
CLEANFILES+=	help.c.tmp help.h.tmp vi.h.tmp test.o test
COPTS+=		-Wall
CPPFLAGS+=	-I. -I${LIBEDITDIR}
#CPPFLAGS+=	-DDEBUG_TTY -DDEBUG_KEY -DDEBUG_READ -DDEBUG -DDEBUG_REFRESH
#CPPFLAGS+=	-DDEBUG_PASTE -DDEBUG_EDIT

AHDR=		vi.h emacs.h common.h
ASRC=		${LIBEDITDIR}/vi.c ${LIBEDITDIR}/emacs.c ${LIBEDITDIR}/common.c

DPSRCS+=	${AHDR} fcns.h help.h fcns.c help.c
CLEANFILES+=	${AHDR} fcns.h help.h fcns.c help.c

vi.h: vi.c makelist
	${SHELL} ${LIBEDITDIR}/makelist -h ${LIBEDITDIR}/vi.c \
	    > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

emacs.h: emacs.c makelist
	${SHELL} ${LIBEDITDIR}/makelist -h ${LIBEDITDIR}/emacs.c \
	    > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

common.h: common.c makelist
	${SHELL} ${LIBEDITDIR}/makelist -h ${LIBEDITDIR}/common.c \
	    > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

fcns.h: ${AHDR} makelist
	${SHELL} ${LIBEDITDIR}/makelist -fh ${AHDR} > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

fcns.c: ${AHDR} fcns.h help.h makelist
	${SHELL} ${LIBEDITDIR}/makelist -fc ${AHDR} > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

help.c: ${ASRC} makelist
	${SHELL} ${LIBEDITDIR}/makelist -bc ${ASRC} > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

help.h: ${ASRC} makelist
	${SHELL} ${LIBEDITDIR}/makelist -bh ${ASRC} > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

editline.c: ${OSRCS}
	${SHELL} ${LIBEDITDIR}/makelist -e ${.ALLSRC:T} > ${.TARGET}.tmp && \
	    mv ${.TARGET}.tmp ${.TARGET}

test.o: ${LIBEDITDIR}/TEST/test.c

test: test.o libedit.a
	${CC} ${LDFLAGS} ${LDSTATIC} -o $@ ${.ALLSRC} ${LDADD} -lotermcap

afterincludes:
	cd ${HDRDST:Q}/readline; \
	    if [[ $$(readlink history.h 2>&-) != readline.h ]]; then \
		rm -f history.h; \
		ln -sf readline.h history.h; \
	fi

.include <bsd.lib.mk>

.if ${CROSS_MODE:L} != "yes"
all: test
.endif
