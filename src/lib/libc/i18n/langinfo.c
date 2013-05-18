/* $MirOS: src/lib/libc/i18n/langinfo.c,v 1.10 2006/05/21 12:38:39 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 * Derived from work placed into the public domain by
 *	J.T. Conklin <jtc@netbsd.org>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Fake locale support, just enough to fool people. Functions are de-
 * fined weak in case someone wants to override these.
 */

#define _LOCALE_CONST_LCONV
#include <sys/param.h>
#include <sys/localedef.h>
#include <langinfo.h>
#include <locale.h>
#include <nl_types.h>
#include <stdlib.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/langinfo.c,v 1.10 2006/05/21 12:38:39 tg Exp $");

/* fake locale support */

struct lconv *__weak_localeconv(void);
/* const for gcc's sake */
const char *__weak_nl_langinfo(nl_item);

_TimeLocale _DefaultTimeLocale = {
	{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"	},
	{ "Sunday", "Monday", "Tuesday", "Wednesday",
	  "Thursday", "Friday", "Saturday"			},
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"		},
	{ "January", "February", "March", "April",
	  "May", "June", "July", "August", "September",
	  "October", "November", "December"			},
	{ "AM", "PM"						},
	"%a %b %d %H:%M:%S %Y", "%m/%d/%y",
	"%H:%M:%S", "%I:%M:%S %p"
};

struct lconv _DefaultLocaleConv = {
	".", "", "", "", "", "", "", "", "", "",
	CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
	CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX
};

struct lconv *
__weak_localeconv(void)
{
	return ((struct lconv *)&_DefaultLocaleConv);
}

const char *
__weak_nl_langinfo(nl_item item)
{
	const char *s;

	switch (item) {
	case CODESET:
		/* if MIR18N_SB_{MAX,CVT} are both 0xFF, we in fact
		 * have ISO-8859-1 character set, but we don't care
		 * because we're on the path to a full UTF-8 system */
		s = __locale_is_utf8 ? "UTF-8" : "ISO_646.irv:1991";
		break;
	case D_T_FMT:
		s = _DefaultTimeLocale.d_t_fmt;
		break;
	case D_FMT:
		s = _DefaultTimeLocale.d_fmt;
		break;
	case T_FMT:
		s = _DefaultTimeLocale.t_fmt;
		break;
	case T_FMT_AMPM:
		s = _DefaultTimeLocale.t_fmt_ampm;
		break;
	case AM_STR:
	case PM_STR:
		s = _DefaultTimeLocale.am_pm[item - AM_STR];
		break;
	case DAY_1:
	case DAY_2:
	case DAY_3:
	case DAY_4:
	case DAY_5:
	case DAY_6:
	case DAY_7:
		s = _DefaultTimeLocale.day[item - DAY_1];
		break;
	case ABDAY_1:
	case ABDAY_2:
	case ABDAY_3:
	case ABDAY_4:
	case ABDAY_5:
	case ABDAY_6:
	case ABDAY_7:
		s = _DefaultTimeLocale.abday[item - ABDAY_1];
		break;
	case MON_1:
	case MON_2:
	case MON_3:
	case MON_4:
	case MON_5:
	case MON_6:
	case MON_7:
	case MON_8:
	case MON_9:
	case MON_10:
	case MON_11:
	case MON_12:
		s = _DefaultTimeLocale.mon[item - MON_1];
		break;
	case ABMON_1:
	case ABMON_2:
	case ABMON_3:
	case ABMON_4:
	case ABMON_5:
	case ABMON_6:
	case ABMON_7:
	case ABMON_8:
	case ABMON_9:
	case ABMON_10:
	case ABMON_11:
	case ABMON_12:
		s = _DefaultTimeLocale.abmon[item - ABMON_1];
		break;
	case RADIXCHAR:
		s = _DefaultLocaleConv.decimal_point;
		break;
	case YESSTR:
		s = "yes";
		break;
	case YESEXPR:
		s = "^[Yy]";
		break;
	case NOSTR:
		s = "no";
		break;
	case NOEXPR:
		s = "^[Nn]";
		break;
	case THOUSEP:
	case CRNCYSTR:
	default:
		s = _DefaultLocaleConv.thousands_sep;
		break;
	}

	return (s);
}

__weak_alias(localeconv, __weak_localeconv);
__weak_alias(nl_langinfo, __weak_nl_langinfo);
