/*-
 * Copyright © 2018
 *	mirabilos <t.glaser@tarent.de>
 * The copyright notices and licences of the files in .linked/ inclu‐
 * ded below shall be considered being part of this copyright notice.
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 */

#include <unistd.h>

#include "compat.h"

__RCSID("$MirOS: src/bin/pax/compat.c,v 1.1.2.2 2018/12/12 04:04:48 tg Exp $");

#if !HAVE_DPRINTF
/* replacement only as powerful as needed for this */
void
dprintf(int fd, const char *fmt, ...)
{
	write(fd, "\nERROR: dprintf not yet implemented!\n", 37);
}
#endif

#if !HAVE_REALLOCARRAY
#include ".linked/reallocarray.inc"
#endif

#if !HAVE_STRMODE
#include ".linked/strmode.inc"
#endif

#if !HAVE_STRLCPY
#undef WIDEC
#define OUTSIDE_OF_LIBKERN
#define L_strlcat
#define L_strlcpy
#include ".linked/strlfun.inc"
#endif
