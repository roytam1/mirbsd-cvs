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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objclib.h"
#include "parser.h"

/* recognized commands */
static command_t cmdv[] = {
	{	"cwd",		parseCwd	},
	{	"man",		parseMan	},
	{	NULL,		NULL		}
};


/* originally from stools/lib/plist.c */
/* Read a packing list from a file */
void
read_plist(list *pkg, FILE *fp)
{
	char pline[FILENAME_MAX];
	parsefn_t fn;
	
	if (!pkg || !fp)
		return;
	
	while (fgets(pline, FILENAME_MAX, fp)) {
		size_t len = strlen(pline);
		while (len && isspace(pline[len - 1]))
			pline[--len] = '\0';
		if (!len)
			continue;
		
		if (pline[0] != COMMAND_CHAR)
			[pkg append: parseFile(pline)];
		else if ((fn = plist_findcmd(pline)))
			 [pkg append: fn(pline)];
	}
}

parsefn_t
plist_findcmd(char *pline)
{
	char *tmp;
	int i;
	
	tmp = strchr(pline, ' ');
	if (tmp)
		*tmp = '\0';
	for (i = 0; cmdv[i].cmdname && strcmp(pline + 1, cmdv[i].cmdname); i++);
	if (tmp)
		*tmp = ' ';
	return cmdv[i].parsefn;
}

void
write_plist(list *pkg, FILE *fp)
{
	plistElement *p;
	listEnumerator *en;
	char *tmp;
	
	if(!fp || !pkg || ![pkg head])
		return;
	
	en = [[listEnumerator alloc] initWithList: pkg];
	while ((p = [en nextObject])) {
		tmp = [p toString];
		(void) fprintf(fp, "%s\n", tmp);
		free(tmp);
	}
	[en release];
}
