/*-
 * Copyright (c) 2006, 2007, 2008
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/param.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#include "sqliteInt.h"
#include "regexp.h"

__RCSID("$MirOS: ports/databases/sqlite/files/regexp.c,v 1.6 2008/08/26 12:53:58 tg Exp $");

#define ERRSTR_TEXT	"REGEXP error: "
static unsigned char errstr[256];

void
sqlite3_regexp_posixext_func(sqlite3_context *ctx, int ac, sqlite3_value **av)
{
	const unsigned char *retext = sqlite3_value_text(av[0]);
	const unsigned char *haystack = sqlite3_value_text(av[1]);
	regex_t re;
	int rv;

	if ((retext == NULL) || (haystack == NULL))
		return;

	if ((rv = regcomp(&re, retext, REG_EXTENDED | REG_NOSUB)) == 0)
		rv = regexec(&re, haystack, 0, NULL, 0);

	if ((rv == 0) || (rv == REG_NOMATCH))
		sqlite3_result_int(ctx, ((rv == REG_NOMATCH) ? 0 : 1));
	else {
		memcpy(errstr, ERRSTR_TEXT, sizeof (ERRSTR_TEXT));
		regerror(rv, &re, errstr + (sizeof (ERRSTR_TEXT) - 1),
		    sizeof (errstr) - (sizeof (ERRSTR_TEXT) - 1));
		sqlite3_result_error(ctx, errstr, -1);
	}

	regfree(&re);
}

void
sqlite3_regexp_posixext_register(sqlite3 *db)
{
	sqlite3_create_function(db, "regexp", 2, SQLITE_UTF8, NULL,
	    sqlite3_regexp_posixext_func, NULL, NULL);
}
