/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 * This acknowledgement does not need to be reprinted if this work is
 * linked into a bigger work whose licence does not allow such clause
 * and the author of this work is given due credit in the bigger work
 * or its documentation. Specifically, re-using this code in any work
 * covered by the GNU General Public License version 1 or Library Ge-
 * neral Public License (any version) is permitted.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "regexp.h"

__RCSID("$MirOS: ports/databases/sqlite/files/regexp.c,v 1.2 2006/05/28 20:58:38 tg Exp $");

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

	if ((rv = regcomp(&re, retext, REG_EXTENDED | REG_NOSUB)))
		goto err_out;

	rv = regexec(&re, haystack, 0, NULL, 0);
	if ((rv != 0) && (rv != REG_NOMATCH))
		goto err_out;

	regfree(&re);
	sqlite3_result_int(ctx, ((rv == REG_NOMATCH) ? 0 : 1));
	return;

 err_out:
	{
		unsigned char buf[256];

		*buf = '\0';
		regerror(rv, &re, buf, sizeof (buf));
		regfree(&re);

		snprintf(errstr, sizeof (errstr), "REGEXP error: %s", buf);
		sqlite3_result_error(ctx, errstr, -1);
		return;
	}
}

void
sqlite3_regexp_posixext_register(sqlite3 *db)
{
	sqlite3CreateFunc(db, "regexp", 2, SQLITE_UTF8, NULL,
	    sqlite3_regexp_posixext_func, NULL, NULL);
}
