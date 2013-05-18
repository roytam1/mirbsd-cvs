/* $MirOS: src/sys/sys/localedef.h,v 1.3 2005/09/30 21:43:08 tg Exp $ */

#ifndef _SYS_LOCALEDEF_H_
#define _SYS_LOCALEDEF_H_

#include <sys/param.h>

typedef struct {
	const char *abday[7];
	const char *day[7];
	const char *abmon[12];
	const char *mon[12];
	const char *am_pm[2];
	const char *d_t_fmt;
	const char *d_fmt;
	const char *t_fmt;
	const char *t_fmt_ampm;
} _TimeLocale;

extern _TimeLocale _DefaultTimeLocale;

#endif
