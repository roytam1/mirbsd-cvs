/* $MirOS$
 *-
 * Copyright (c) 2005
 *	Benny Siegert <bsiegert@gmx.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objclib.h"
#include "parser.h"

@implementation plistFile

- (char *)toString
{
	return strdup(name);
}

@end

/* Parse a file or directory entry.
 */
plistElement *parseFile(char *command)
{
	size_t len;
	
	if (!command)
		return nil;
	len = strlen(command);
	if (command[len - 1] == '/') {
		command[--len] = '\0';
		return [[plistDir alloc] initWithName: command];
	} else
		return [[plistFile alloc] initWithName: command];
}
