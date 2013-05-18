# $MirOS$
#-
# To build with klibc, for example.

ALL_TGT=	libregex.a test/re

AR?=		ar
RANLIB?=	ranlib
CC?=		klcc
CFLAGS?=	-Os -g

CPPFLAGS+=	-DPOSIX_MISTAKE
CPPFLAGS+=	-I.
CPPFLAGS+=	-D'__RCSID(x)='

SRCS+=		regcomp.c regerror.c regexec.c regfree.c
OBJS=		${SRCS:.c=.o}

all: ${ALL_TGT}

install:
	@echo copy regex.h and libregex.a somewhere

clean:
	-rm -f ${OBJS} ${TEST_OBJS} test/re libregex.a

libregex.a: ${OBJS}
	${AR} rc $@ ${OBJS}
	${RANLIB} $@ || echo Never mind.

TEST_SRCS=	test/debug.c test/main.c test/split.c
TEST_OBJS=	${TEST_SRCS:.c=.o}

test/re: ${TEST_OBJS} libregex.a
	${CC} -o $@ ${TEST_OBJS} -L. -lregex

check: test/re
	cd test && ./re <tests
	cd test && ./re -el <tests
	cd test && ./re -er <tests
