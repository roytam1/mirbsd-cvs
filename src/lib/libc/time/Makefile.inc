# $MirOS: src/lib/libc/time/Makefile.inc,v 1.5 2009/11/09 21:30:56 tg Exp $
# $OpenBSD: Makefile.inc,v 1.8 2000/08/22 16:19:50 millert Exp $

.PATH: ${LIBCSRCDIR}/time

SRCS+=	asctime.c difftime.c localtime.c strftime.c strptime.c
MAN+=	ctime.3 strftime.3 strptime.3 taitime.3 tzfile.5 tzset.3

CFLAGS_localtime.o+= -Wno-old-style-definition
CFLAGS_strftime.o+= -Wno-old-style-definition

SRCS+=		taileaps.c
UIF_KUSRCS+=	tai_time.c tailibc.c -DL_tai_time
UIF_KUSRCS+=	taina_time.c tailibc.c -DL_taina_time
UIF_KUSRCS+=	tai_djb.c tailibc.c -DL_djbtai

MLINKS+=ctime.3 asctime.3 ctime.3 difftime.3 ctime.3 gmtime.3 \
	ctime.3 localtime.3 ctime.3 mktime.3 ctime.3 asctime_r.3 \
	ctime.3 ctime_r.3 ctime.3 gmtime_r.3 ctime.3 localtime_r.3 \
	ctime.3 timelocal.3 ctime.3 timegm.3
MLINKS+=tzset.3 tzsetwall.3
MLINKS+=taitime.3 tai_time.3 taitime.3 taina_time.3 taitime.3 tai_leaps.3 \
	taitime.3 tai_isleap.3 taitime.3 timet2tai.3 taitime.3 tai2timet.3 \
	taitime.3 utc2tai.3 taitime.3 tai2utc.3 taitime.3 mjd2tai.3 \
	taitime.3 tai2mjd.3 taitime.3 mjd2tm.3 taitime.3 tm2mjd.3 \
	taitime.3 exporttai.3 taitime.3 importtai.3
