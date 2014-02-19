# $MirOS: src/lib/libc/time/Makefile.inc,v 1.8 2011/11/20 23:40:11 tg Exp $
# $OpenBSD: Makefile.inc,v 1.8 2000/08/22 16:19:50 millert Exp $

.PATH: ${LIBCSRCDIR}/time

SRCS+=	asctime.c difftime.c localtime.c strftime.c strptime.c
MAN+=	ctime.3 strftime.3 strptime.3 tzfile.5 tzset.3 mirtime.3

CFLAGS_localtime.o+= -Wno-old-style-definition
CFLAGS_strftime.o+= -Wno-old-style-definition

MLINKS+=ctime.3 asctime.3 ctime.3 difftime.3 ctime.3 gmtime.3 \
	ctime.3 localtime.3 ctime.3 mktime.3 ctime.3 asctime_r.3 \
	ctime.3 ctime_r.3 ctime.3 gmtime_r.3 ctime.3 localtime_r.3 \
	ctime.3 timelocal.3 ctime.3 timegm.3
MLINKS+=tzset.3 tzsetwall.3
MLINKS+=mirtime.3 mirtime_getleaps.3 mirtime.3 mirtime_isleap.3 \
	mirtime.3 timet2posix.3 mirtime.3 posix2timet.3 \
	mirtime.3 timet2mjd.3 mirtime.3 mjd2timet.3 \
	mirtime.3 timet2tm.3 mirtime.3 tm2timet.3 \
	mirtime.3 mjd_explode.3 mirtime.3 mjd_implode.3
