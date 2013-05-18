/**	$MirOS: src/usr.bin/locale/locale.c,v 1.7 2007/02/02 19:22:38 tg Exp $ */
/*	$NetBSD: locale.c,v 1.5 2006/02/16 19:19:49 tnozaki Exp $	*/

/*-
 * Copyright (c) 2006 Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 2002, 2003 Alexey Zelkin <phantom@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * FreeBSD: src/usr.bin/locale/locale.c,v 1.10 2003/06/26 11:05:56 phantom Exp
 */

#include <sys/cdefs.h>
__RCSID("$MirOS: src/usr.bin/locale/locale.c,v 1.7 2007/02/02 19:22:38 tg Exp $");
__RCSID("$NetBSD: locale.c,v 1.5 2006/02/16 19:19:49 tnozaki Exp $");

/*
 * XXX: implement missing era_* (LC_TIME) keywords (require libc &
 *	nl_langinfo(3) extensions)
 */

#include <sys/types.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <locale.h>
#include <langinfo.h>
#include <limits.h>
#include <paths.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern const char *__progname;

/* Local prototypes */
static void list_charmaps(void);
static void list_locales(void);
static const char *lookup_localecat(int);
static char *kwval_lconv(int);
static int kwval_lookup(char *, char **, int *, int *);
static void showdetails(char *);
static void showkeywordslist(void);
static void showlocale(void);
__dead static void usage(void);

/* Global variables */
int	all_locales = 0;
int	all_charmaps = 0;
int	prt_categories = 0;
int	prt_keywords = 0;
int	more_params = 0;

struct _lcinfo {
	const char	*name;
	int		id;
} lcinfo [] = {
	{ "LC_CTYPE",		LC_CTYPE },
	{ "LC_COLLATE",		LC_COLLATE },
	{ "LC_TIME",		LC_TIME },
	{ "LC_NUMERIC",		LC_NUMERIC },
	{ "LC_MONETARY",	LC_MONETARY },
	{ "LC_MESSAGES",	LC_MESSAGES }
};
#define NLCINFO (sizeof(lcinfo)/sizeof(lcinfo[0]))

/* ids for values not referenced by nl_langinfo() */
#define	KW_ZERO			10000
#define	KW_GROUPING		(KW_ZERO+1)
#define KW_INT_CURR_SYMBOL 	(KW_ZERO+2)
#define KW_CURRENCY_SYMBOL 	(KW_ZERO+3)
#define KW_MON_DECIMAL_POINT 	(KW_ZERO+4)
#define KW_MON_THOUSANDS_SEP 	(KW_ZERO+5)
#define KW_MON_GROUPING 	(KW_ZERO+6)
#define KW_POSITIVE_SIGN 	(KW_ZERO+7)
#define KW_NEGATIVE_SIGN 	(KW_ZERO+8)
#define KW_INT_FRAC_DIGITS 	(KW_ZERO+9)
#define KW_FRAC_DIGITS 		(KW_ZERO+10)
#define KW_P_CS_PRECEDES 	(KW_ZERO+11)
#define KW_P_SEP_BY_SPACE 	(KW_ZERO+12)
#define KW_N_CS_PRECEDES 	(KW_ZERO+13)
#define KW_N_SEP_BY_SPACE 	(KW_ZERO+14)
#define KW_P_SIGN_POSN 		(KW_ZERO+15)
#define KW_N_SIGN_POSN 		(KW_ZERO+16)
#ifdef __NetBSD__
#define KW_INT_P_CS_PRECEDES 	(KW_ZERO+17)
#define KW_INT_P_SEP_BY_SPACE 	(KW_ZERO+18)
#define KW_INT_N_CS_PRECEDES 	(KW_ZERO+19)
#define KW_INT_N_SEP_BY_SPACE 	(KW_ZERO+20)
#define KW_INT_P_SIGN_POSN 	(KW_ZERO+21)
#define KW_INT_N_SIGN_POSN 	(KW_ZERO+22)
#endif

struct _kwinfo {
	const char	*name;
	int		isstr;		/* true - string, false - number */
	int		catid;		/* LC_* */
	int		value_ref;
	const char	*comment;
} kwinfo [] = {
	{ "charmap",		1, LC_CTYPE,	CODESET, "" },	/* hack */

	{ "decimal_point",	1, LC_NUMERIC,	RADIXCHAR, "" },
	{ "thousands_sep",	1, LC_NUMERIC,	THOUSEP, "" },
	{ "grouping",		1, LC_NUMERIC,	KW_GROUPING, "" },
	{ "radixchar",		1, LC_NUMERIC,	RADIXCHAR,
	  "Same as decimal_point (BSD only)" },			/* compat */
	{ "thousep",		1, LC_NUMERIC,	THOUSEP,
	  "Same as thousands_sep (BSD only)" },			/* compat */

	{ "int_curr_symbol",	1, LC_MONETARY,	KW_INT_CURR_SYMBOL, "" },
	{ "currency_symbol",	1, LC_MONETARY,	KW_CURRENCY_SYMBOL, "" },
	{ "mon_decimal_point",	1, LC_MONETARY,	KW_MON_DECIMAL_POINT, "" },
	{ "mon_thousands_sep",	1, LC_MONETARY,	KW_MON_THOUSANDS_SEP, "" },
	{ "mon_grouping",	1, LC_MONETARY,	KW_MON_GROUPING, "" },
	{ "positive_sign",	1, LC_MONETARY,	KW_POSITIVE_SIGN, "" },
	{ "negative_sign",	1, LC_MONETARY,	KW_NEGATIVE_SIGN, "" },

	{ "int_frac_digits",	0, LC_MONETARY,	KW_INT_FRAC_DIGITS, "" },
	{ "frac_digits",	0, LC_MONETARY,	KW_FRAC_DIGITS, "" },
	{ "p_cs_precedes",	0, LC_MONETARY,	KW_P_CS_PRECEDES, "" },
	{ "p_sep_by_space",	0, LC_MONETARY,	KW_P_SEP_BY_SPACE, "" },
	{ "n_cs_precedes",	0, LC_MONETARY,	KW_N_CS_PRECEDES, "" },
	{ "n_sep_by_space",	0, LC_MONETARY,	KW_N_SEP_BY_SPACE, "" },
	{ "p_sign_posn",	0, LC_MONETARY,	KW_P_SIGN_POSN, "" },
	{ "n_sign_posn",	0, LC_MONETARY,	KW_N_SIGN_POSN, "" },
#ifdef KW_INT_P_CS_PRECEDES
	{ "int_p_cs_precedes",	0, LC_MONETARY,	KW_INT_P_CS_PRECEDES, "" },
	{ "int_p_sep_by_space",	0, LC_MONETARY,	KW_INT_P_SEP_BY_SPACE, "" },
	{ "int_n_cs_precedes",	0, LC_MONETARY,	KW_INT_N_CS_PRECEDES, "" },
	{ "int_n_sep_by_space",	0, LC_MONETARY,	KW_INT_N_SEP_BY_SPACE, "" },
	{ "int_p_sign_posn",	0, LC_MONETARY,	KW_INT_P_SIGN_POSN, "" },
	{ "int_n_sign_posn",	0, LC_MONETARY,	KW_INT_N_SIGN_POSN, "" },
#endif

	{ "d_t_fmt",		1, LC_TIME,	D_T_FMT, "" },
	{ "d_fmt",		1, LC_TIME,	D_FMT, "" },
	{ "t_fmt",		1, LC_TIME,	T_FMT, "" },
	{ "am_str",		1, LC_TIME,	AM_STR, "" },
	{ "pm_str",		1, LC_TIME,	PM_STR, "" },
	{ "t_fmt_ampm",		1, LC_TIME,	T_FMT_AMPM, "" },
	{ "day_1",		1, LC_TIME,	DAY_1, "" },
	{ "day_2",		1, LC_TIME,	DAY_2, "" },
	{ "day_3",		1, LC_TIME,	DAY_3, "" },
	{ "day_4",		1, LC_TIME,	DAY_4, "" },
	{ "day_5",		1, LC_TIME,	DAY_5, "" },
	{ "day_6",		1, LC_TIME,	DAY_6, "" },
	{ "day_7",		1, LC_TIME,	DAY_7, "" },
	{ "abday_1",		1, LC_TIME,	ABDAY_1, "" },
	{ "abday_2",		1, LC_TIME,	ABDAY_2, "" },
	{ "abday_3",		1, LC_TIME,	ABDAY_3, "" },
	{ "abday_4",		1, LC_TIME,	ABDAY_4, "" },
	{ "abday_5",		1, LC_TIME,	ABDAY_5, "" },
	{ "abday_6",		1, LC_TIME,	ABDAY_6, "" },
	{ "abday_7",		1, LC_TIME,	ABDAY_7, "" },
	{ "mon_1",		1, LC_TIME,	MON_1, "" },
	{ "mon_2",		1, LC_TIME,	MON_2, "" },
	{ "mon_3",		1, LC_TIME,	MON_3, "" },
	{ "mon_4",		1, LC_TIME,	MON_4, "" },
	{ "mon_5",		1, LC_TIME,	MON_5, "" },
	{ "mon_6",		1, LC_TIME,	MON_6, "" },
	{ "mon_7",		1, LC_TIME,	MON_7, "" },
	{ "mon_8",		1, LC_TIME,	MON_8, "" },
	{ "mon_9",		1, LC_TIME,	MON_9, "" },
	{ "mon_10",		1, LC_TIME,	MON_10, "" },
	{ "mon_11",		1, LC_TIME,	MON_11, "" },
	{ "mon_12",		1, LC_TIME,	MON_12, "" },
	{ "abmon_1",		1, LC_TIME,	ABMON_1, "" },
	{ "abmon_2",		1, LC_TIME,	ABMON_2, "" },
	{ "abmon_3",		1, LC_TIME,	ABMON_3, "" },
	{ "abmon_4",		1, LC_TIME,	ABMON_4, "" },
	{ "abmon_5",		1, LC_TIME,	ABMON_5, "" },
	{ "abmon_6",		1, LC_TIME,	ABMON_6, "" },
	{ "abmon_7",		1, LC_TIME,	ABMON_7, "" },
	{ "abmon_8",		1, LC_TIME,	ABMON_8, "" },
	{ "abmon_9",		1, LC_TIME,	ABMON_9, "" },
	{ "abmon_10",		1, LC_TIME,	ABMON_10, "" },
	{ "abmon_11",		1, LC_TIME,	ABMON_11, "" },
	{ "abmon_12",		1, LC_TIME,	ABMON_12, "" },
#ifdef ERA
	{ "era",		1, LC_TIME,	ERA, "(unavailable)" },
	{ "era_d_fmt",		1, LC_TIME,	ERA_D_FMT, "(unavailable)" },
	{ "era_d_t_fmt",	1, LC_TIME,	ERA_D_T_FMT, "(unavailable)" },
	{ "era_t_fmt",		1, LC_TIME,	ERA_T_FMT, "(unavailable)" },
#endif
#ifdef ALT_DIGITS
	{ "alt_digits",		1, LC_TIME,	ALT_DIGITS, "" },
#endif

	{ "yesexpr",		1, LC_MESSAGES, YESEXPR, "" },
	{ "noexpr",		1, LC_MESSAGES, NOEXPR, "" },
	{ "yesstr",		1, LC_MESSAGES, YESSTR,
	  "(POSIX legacy)" },					/* compat */
	{ "nostr",		1, LC_MESSAGES, NOSTR,
	  "(POSIX legacy)" }					/* compat */

};
#define NKWINFO (sizeof(kwinfo)/sizeof(kwinfo[0]))

int
main(int argc, char *argv[])
{
	int	ch;
	int	tmp;

	while ((ch = getopt(argc, argv, "ackm")) != -1) {
		switch (ch) {
		case 'a':
			all_locales = 1;
			break;
		case 'c':
			prt_categories = 1;
			break;
		case 'k':
			prt_keywords = 1;
			break;
		case 'm':
			all_charmaps = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* validate arguments */
	if (all_locales && all_charmaps)
		usage();
	if ((all_locales || all_charmaps) && argc > 0)
		usage();
	if ((all_locales || all_charmaps) && (prt_categories || prt_keywords))
		usage();
	if ((prt_categories || prt_keywords) && argc <= 0)
		usage();

	/* process '-a' */
	if (all_locales) {
		list_locales();
		exit(0);
	}

	/* process '-m' */
	if (all_charmaps) {
		list_charmaps();
		exit(0);
	}

	/* check for special case '-k list' */
	tmp = 0;
	if (prt_keywords && argc > 0)
		while (tmp < argc)
			if (strcasecmp(argv[tmp++], "list") == 0) {
				showkeywordslist();
				exit(0);
			}

	/* process '-c' and/or '-k' */
	if (prt_categories || prt_keywords || argc > 0) {
		setlocale(LC_ALL, "");
		while (argc > 0) {
			showdetails(*argv);
			argv++;
			argc--;
		}
		exit(0);
	}

	/* no arguments, show current locale state */
	showlocale();

	return (0);
}

void
usage(void)
{
	printf("usage:\t%s [ -a | -m ]\n\t%s [ -ck ] name ...\n\t%s -k list\n",
	    __progname, __progname, __progname);
	exit(1);
}

/*
 * Output information about all available locales
 */
void
list_locales(void)
{
	/* Hard-coded on MirOS:
	 * C		Standard 7-bit (8-bit clean) single-byte locale
	 * xx_XX.OPTU-8	The only other locale (multi-byte LC_CTYPE)
	 * en_US.UTF-8	Since nobody knows what OPTU-8 or even CESU-8 is, we use this…
	 * POSIX	This one is mandated by SUSv3
	 */
	printf("C\nen_US.OPTU-8\nen_US.UTF-8\nPOSIX\n");
}

/*
 * Output information about all available charmaps
 */
void
list_charmaps(void)
{
	printf("UTF-8\nISO_646.irv:1991\n");
}

/*
 * Show current locale status, depending on environment variables
 */
void
showlocale(void)
{
	size_t	i;
	const char *lang, *vval, *eval, *lcallval;

	setlocale(LC_ALL, "");

	lang = getenv("LANG");
	if (lang == NULL) {
		printf("LANG=\n");
		lang = "C";
	} else
		printf("LANG=\"%s\"\n", lang);

	lcallval = getenv("LC_ALL");

	for (i = 0; i < NLCINFO; i++) {
		vval = setlocale(lcinfo[i].id, NULL);
		eval = getenv(lcinfo[i].name);
		if (lcallval || (eval == NULL) || strcmp(eval, vval)) {
			/* overridden by LC_ALL, not set, or invalid */
			printf("%s=\"%s\"\n", lcinfo[i].name, vval);
		} else if (strcmp(lang, vval)) {
			/* set and not implied, and valid */
			printf("%s=%s\n", lcinfo[i].name, vval);
		} else {
			/* set but implied */
			printf("%s=\"%s\"\n", lcinfo[i].name, vval);
		}
	}

	printf("LC_ALL=%s\n", lcallval ? lcallval : "");
}

/*
 * keyword value lookup helper (via localeconv())
 */
char *
kwval_lconv(int id)
{
	struct lconv *lc;
	char *rval;

	rval = NULL;
	lc = localeconv();
	switch (id) {
		case KW_GROUPING:
			rval = lc->grouping;
			break;
		case KW_INT_CURR_SYMBOL:
			rval = lc->int_curr_symbol;
			break;
		case KW_CURRENCY_SYMBOL:
			rval = lc->currency_symbol;
			break;
		case KW_MON_DECIMAL_POINT:
			rval = lc->mon_decimal_point;
			break;
		case KW_MON_THOUSANDS_SEP:
			rval = lc->mon_thousands_sep;
			break;
		case KW_MON_GROUPING:
			rval = lc->mon_grouping;
			break;
		case KW_POSITIVE_SIGN:
			rval = lc->positive_sign;
			break;
		case KW_NEGATIVE_SIGN:
			rval = lc->negative_sign;
			break;
		case KW_INT_FRAC_DIGITS:
			rval = &(lc->int_frac_digits);
			break;
		case KW_FRAC_DIGITS:
			rval = &(lc->frac_digits);
			break;
		case KW_P_CS_PRECEDES:
			rval = &(lc->p_cs_precedes);
			break;
		case KW_P_SEP_BY_SPACE:
			rval = &(lc->p_sep_by_space);
			break;
		case KW_N_CS_PRECEDES:
			rval = &(lc->n_cs_precedes);
			break;
		case KW_N_SEP_BY_SPACE:
			rval = &(lc->n_sep_by_space);
			break;
		case KW_P_SIGN_POSN:
			rval = &(lc->p_sign_posn);
			break;
		case KW_N_SIGN_POSN:
			rval = &(lc->n_sign_posn);
			break;
#ifdef KW_INT_P_CS_PRECEDES
		case KW_INT_P_CS_PRECEDES:
			rval = &(lc->int_p_cs_precedes);
			break;
		case KW_INT_P_SEP_BY_SPACE:
			rval = &(lc->int_p_sep_by_space);
			break;
		case KW_INT_N_CS_PRECEDES:
			rval = &(lc->int_n_cs_precedes);
			break;
		case KW_INT_N_SEP_BY_SPACE:
			rval = &(lc->int_n_sep_by_space);
			break;
		case KW_INT_P_SIGN_POSN:
			rval = &(lc->int_p_sign_posn);
			break;
		case KW_INT_N_SIGN_POSN:
			rval = &(lc->int_n_sign_posn);
			break;
#endif
		default:
			break;
	}
	return (rval);
}

/*
 * keyword value and properties lookup
 */
int
kwval_lookup(char *kwname, char **kwval, int *cat, int *isstr)
{
	int	rval;
	size_t	i;

	rval = 0;
	for (i = 0; i < NKWINFO; i++) {
		if (strcasecmp(kwname, kwinfo[i].name) == 0) {
			rval = 1;
			*cat = kwinfo[i].catid;
			*isstr = kwinfo[i].isstr;
			if (kwinfo[i].value_ref < KW_ZERO) {
				*kwval = nl_langinfo(kwinfo[i].value_ref);
			} else {
				*kwval = kwval_lconv(kwinfo[i].value_ref);
			}
			break;
		}
	}

	return (rval);
}

/*
 * Show details about requested keyword according to '-k' and/or '-c'
 * command line options specified.
 */
void
showdetails(char *kw)
{
	int	isstr, cat, tmpval;
	char	*kwval;

	if (kwval_lookup(kw, &kwval, &cat, &isstr) == 0) {
		/*
		 * invalid keyword specified.
		 * XXX: any actions?
		 */
		return;
	}

	if (prt_categories) {
		printf("%s\n", lookup_localecat(cat));
	}

	if (prt_keywords) {
		if (isstr) {
			printf("%s=\"%s\"\n", kw, kwval);
		} else {
			tmpval = (char) *kwval;
			printf("%s=%d\n", kw, tmpval);
		}
	}

	if (!prt_categories && !prt_keywords) {
		if (isstr) {
			printf("%s\n", kwval);
		} else {
			tmpval = (char) *kwval;
			printf("%d\n", tmpval);
		}
	}
}

/*
 * Convert locale category id into string
 */
const char *
lookup_localecat(int cat)
{
	size_t	i;

	for (i = 0; i < NLCINFO; i++)
		if (lcinfo[i].id == cat) {
			return (lcinfo[i].name);
		}
	return ("UNKNOWN");
}

/*
 * Show list of keywords
 */
void
showkeywordslist(void)
{
	size_t	i;

#define FMT "%-20s %-12s %-7s %-20s\n"

	printf("List of available keywords\n\n");
	printf(FMT, "Keyword", "Category", "Type", "Comment");
	printf("-------------------- ------------ ------- --------------------\n");
	for (i = 0; i < NKWINFO; i++) {
		printf(FMT,
			kwinfo[i].name,
			lookup_localecat(kwinfo[i].catid),
			(kwinfo[i].isstr == 0) ? "number" : "string",
			kwinfo[i].comment);
	}
}
