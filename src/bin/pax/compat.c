/*-
 * Copyright © 2018
 *	mirabilos <t.glaser@tarent.de>
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

#include "pax.h"

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

#if !HAVE_DPRINTF
/* replacement only as powerful as needed for this */
void
dprintf(int fd, const char *fmt, ...)
{
	write(fd, "\nERROR: dprintf not yet implemented!\n", 37);
}
#endif
