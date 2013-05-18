# $MirOS: src/usr.sbin/rdate/GNUmakefile,v 1.3 2009/01/11 00:36:03 tg Exp $
#-
# You may need: https://www.mirbsd.org/MirOS/dist/hosted/other/arc4random.c

SRCS=		ntp.c ntpleaps.c rdate.c rfc868time.c
ifeq ($(strip ${HAVE_ARC4RANDOM}),)
SRCS+=		arc4random.c
endif
OBJS=		$(addsuffix .o,$(basename $(notdir ${SRCS})))
BINDIR?=	/usr/sbin
MANDIR?=	/usr/share/man
CC?=		gcc
CFLAGS?=	-O2
CPPFLAGS+=	-DNO_UTIL -DEXT_A4R -DHAVE_STDINT_H
CPPFLAGS+=	-D'__RCSID(x)=static const char __rcsid[] = x'

all: rdate

install:
	install -c -s -m 555 rdate ${DESTDIR}${BINDIR}/
	install -c -m 444 rdate.8 ${DESTDIR}${MANDIR}/man8/

clean:
	-rm -f rdate *.o

rdate: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} ${LIBS} ${LDADD}

%.o: %.c
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ -c $<
