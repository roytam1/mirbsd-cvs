# $MirOS: src/usr.sbin/rdate/GNUmakefile,v 1.6 2010/08/05 13:02:42 tg Exp $
#-
# You may need: https://www.mirbsd.org/MirOS/dist/hosted/other/arc4random.c

SRCS=		cutil.c ntp.c rdate.c rfc868time.c
ifeq ($(strip ${HAVE_ARC4RANDOM}),)
SRCS+=		arc4random.c
endif
OBJS=		$(addsuffix .o,$(basename $(notdir ${SRCS})))
BINDIR?=	/usr/sbin
MANDIR?=	/usr/share/man
CC?=		gcc
CFLAGS?=	-O2
CPPFLAGS+=	-DNO_UTIL -DEXT_A4R -DHAVE_STDINT_H -DIN_RDATE
CPPFLAGS+=	-D'__RCSID(x)=static const char __rcsid[] = x'

INSTALL_STRIP?=	-s
BINMODE?=	555
MANMODE?=	444

all: rdate

install:
	install -c ${INSTALL_STRIP} -m ${BINMODE} rdate ${DESTDIR}${BINDIR}/
	install -c -m ${MANMODE} rdate.8 ${DESTDIR}${MANDIR}/man8/

clean:
	-rm -f rdate *.o

rdate: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} ${LIBS} ${LDADD}

%.o: %.c
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ -c $<
