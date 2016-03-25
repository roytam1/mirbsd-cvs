/* $MirOS: src/kern/include/mirtime.h,v 1.2 2011/11/20 23:40:11 tg Exp $ */

/* Do not include this header, include <time.h> and/or <sys/time.h> */

#ifndef SYSKERN_MIRTIME_H
#define SYSKERN_MIRTIME_H 1


/* Definition of basic types */


/* pulled out from <time.h> and/or <sys/time.h> */

/* seconds since the epoch */
#ifdef _BSD_TIME_T_
typedef _BSD_TIME_T_ time_t;
#undef _BSD_TIME_T_
#endif

/* calendaric broken-down date */
struct tm {
	int tm_sec;		/* seconds [0-60] */
	int tm_min;		/* minutes [0-59] */
	int tm_hour;		/* hours [0-23] */
	int tm_mday;		/* day of month [1-31] */
	int tm_mon;		/* month of year - 1 [0-11] */
	time_t tm_year;		/* years since 1900 */
	int tm_wday;		/* day of week (0 = sunday) */
	int tm_yday;		/* day of year [0-365] */
	int tm_isdst;		/* summer time effective? [0/1] */
	long tm_gmtoff;		/* offset from UTC in seconds */
	char *tm_zone;		/* abbreviation of timezone name */
};

/* new types */

/* Modified Julian Date */
typedef struct {
	time_t mjd;		/* Julian Date minus 2'400'000.5, floor'd */
	int32_t sec;		/* UTC (not TT) seconds into that [0-86400] */
} mirtime_mjd;


/* functions */
__BEGIN_DECLS

/* conversion between time-since-the-epoch with and without leap seconds */
time_t timet2posix(time_t);
time_t posix2timet(time_t);

/* conversion between time-since-the-epoch with leap seconds and MJD */
mirtime_mjd *timet2mjd(mirtime_mjd *, time_t);
time_t mjd2timet(mirtime_mjd *);

/* easy conversion between epoch and calendaric time */
struct tm *timet2tm(struct tm *, time_t);
time_t tm2timet(struct tm *);
#ifdef __GNUC__
#define timet2tm(dst, src) __extension__({				\
	mirtime_mjd timet2tm_storage;					\
	mjd_explode((dst), timet2mjd(&timet2tm_storage, (src)));	\
})
#define tm2timet(src) __extension__({					\
	mirtime_mjd tm2timet_storage;					\
	mjd2timet(mjd_implode(&tm2timet_storage, (src)));		\
})
#endif

/* internal conversion between broken-down calendaric date and MJD */
struct tm *mjd_explode(struct tm *, const mirtime_mjd *);
mirtime_mjd *mjd_implode(mirtime_mjd *, const struct tm *);

/* internal leap second management */
const time_t *mirtime_getleaps(void);
int mirtime_isleap(time_t);

__END_DECLS

#endif
