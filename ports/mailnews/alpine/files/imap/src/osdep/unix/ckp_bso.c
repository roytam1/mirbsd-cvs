/*-
 * Copyright (c) 2004
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
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

#include <sys/cdefs.h>
#include <login_cap.h>
#include <bsd_auth.h>

__RCSID("$MirOS: ports/mailnews/pine/files/ckp_bso.c,v 1.3 2005/12/15 14:24:18 tg Exp $");

struct passwd *
checkpw (struct passwd *pw, char *pass, int argc, char *argv[])
{
	return (auth_userokay(pw->pw_name, pw->pw_class, NIL, pass))
	    ? pw : NIL;
}
