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

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INLCUDED


typedef plistElement *(*parsefn_t)(char *);
typedef struct command_t {
	const char *cmdname;
	parsefn_t parsefn;
} command_t;

#define COMMAND_CHAR '@'

/* I/O */
void read_plist(list *, FILE *);
void write_plist(list *, FILE *);

parsefn_t plist_findcmd(char *pline);

/* parser functions */
plistElement *parseFile(char *command);
plistElement *parseCwd(char *command);
plistElement *parseMan(char *command);

#endif /* defined(PARSER_H_INCLUDED) */
