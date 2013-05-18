/* $MirOS: ports/infrastructure/pkgtools/lib/cfgfile.c,v 1.1.2.3 2009/12/23 13:54:14 bsiegert Exp $ */

/*-
 * Copyright (c) 2009
 *	Benny Siegert <bsiegert@gmx.de>
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
 *-
 * Configuration file routines
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include "queue.h"
#include "lib.h"

#ifndef SYSCONFDIR
# define SYSCONFDIR "."
#endif
#define CFG_FILE SYSCONFDIR "/pkgtools/pkgtools.conf"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/cfgfile.c,v 1.1.2.3 2009/12/23 13:54:14 bsiegert Exp $");

typedef SLIST_HEAD(cfg_varlist, cfg_var) cfg_varlist;
struct cfg_var {
	char *key;
	char *val;
	SLIST_ENTRY(cfg_var) entries;
};

static cfg_varlist Vars = SLIST_HEAD_INITIALIZER(Vars);
static char *Pager = NULL;

FILE
*cfg_open(void)
{
	FILE *cfgfile;

	cfgfile = fopen(CFG_FILE, "r");
	if (!cfgfile)
		warn("Error opening configuration file");
	return cfgfile;
}

/* Parse a line of the form "key=value", where i is the index of the '='
 * sign and len is the length of the string. Works even when the string is
 * not null-terminated.
 */
static void
parse_var(char *line, size_t i, size_t len)
{
	struct cfg_var *var;

	var = malloc(sizeof (struct cfg_var));
	if (!var) {
		warn(NULL);
		return;
	}

	/* i is the position of the '='; everything before is the name,
	 * the value is everything after it */
	var->key = malloc(i + 1);
	if (!var->key) {
		warn(NULL);
		return;
	}
	strlcpy(var->key, line, i + 1);

	var->val = cfg_expand_vars(line + i + 1, len - i - 1);
	if (!var->val) {
		warnx("%s: Variable expansion failed", var->key);
		return;
	}
	SLIST_INSERT_HEAD(&Vars, var, entries);
}


/* Parse a configuration directive. i is the index of the space separating
 * the directive from the arguments.
 */
static void
parse_command(char *line, size_t i, size_t len)
{
	if (i == 5 && !strncasecmp(line, "Pager", i)) {
		if (Pager)
			free(Pager);
		Pager = cfg_expand_vars(line + i + 1, len - i - 1);
	} else
		warnx("Unrecognized command: %s", line);
}

/* Read the configuration file. Returns true if successful, false otherwise.
 * The contents are saved in static variables, use the appropriate functions
 * to probe for them. */
bool
cfg_read_config(void)
{
	FILE *cfgfile;
	char *line;
	size_t len, i;
	bool line_end;

	cfgfile = cfg_open();
	if (!cfgfile)
		return false;

	do {
		line = fgetln(cfgfile, &len);
		if (!line)
			break;
		if (line[len - 1] == '\n')
			line[--len] = '\0';
		line_end = false;
		for (i = 0; i < len; i++) {
			switch (line[i]) {
				case '\n':
					line_end = true;
					break;
				case '\0':
					line_end = true;
					break;
				case '#':
					line_end = true;
					break;
				case '=':
					parse_var(line, i, len);
					line_end = true;
					break;
				case ' ':
					parse_command(line, i, len);
					line_end = true;
					break;
			}
			if (line_end)
				break;
		}

	} while (1);

	if (ferror(cfgfile)) {
		warn("Error reading configuration file");
		fclose(cfgfile);
		return false;
	}
	/* otherwise assume EOF */
	return true;
}

/* Debug function: dump the names and values of all variables to stdout. */
void
cfg_dump_vars(void)
{
	struct cfg_var *var;

	SLIST_FOREACH(var, &Vars, entries)
		printf("%s = %s\n", var->key, var->val);
}

/* Replace all occurrences of "$$" with a single dollar sign, and all
 * variables of the form ${FOO} or $(FOO) with their respective contents.
 * Returns dynamically allocated storage which has to be freed by the caller.
 */
char
*cfg_expand_vars(char *string, size_t len)
{
	char *rv, *cp, *rv_cp;
	struct cfg_var *var;
	size_t rv_len;
	size_t rv_size = len + 1;

	/* this is enough if there are no substitutions */
	rv = malloc(rv_size);
	if (!rv) {
		warn(NULL);
		return NULL;
	}
	*rv = '\0';

	/* cp: position in string at which there is a '$'
	 * len: remaining length of string
	 * rv: return value (null-terminated)
	 * rv_size: complete length of the rv buffer
	 * rv_len: remaining length of the rv buffer
	 */
	rv_cp = rv;
	rv_len = rv_size;
	while ((cp = (char *)memchr(string, '$', len)) != NULL) {
		size_t match_len;
		char paren = '\0';
		*cp = '\0';
		match_len = strlen(string);
		strlcpy(rv_cp, string, rv_len);
		len -= match_len + 1;
		rv_cp += match_len;
		rv_len -= match_len;

		/* '$' was the last character */
		if (len == 0) {
			assert(rv_len > 1);
			strlcpy(rv_cp, "$", rv_len);
			rv_cp++;
			break;
		}

		switch (cp[1]) {
		case '$':
			assert(rv_len > 1);
			strlcpy(rv_cp, "$", rv_len);
			rv_len--;
			rv_size--;
			rv_cp++;
			cp++;
			len--;
			break;
		case '{':
			paren = '}';
			/* FALLTRU */
		case '(':
			if (!paren)
				paren = ')';
			string = cp + 2;
			len--;
			cp = (char *)memchr(string, paren, len);
			if (!cp) {
				warnx("Syntax error in config file: "
					"no closing parenthesis");
				break;
			}
			*cp = '\0';
			SLIST_FOREACH(var, &Vars, entries)
				if (!strcmp(string, var->key)) {
					size_t n;
				       	n = strlen(var->val)-strlen(string);
					rv_size += n;
					if (!(rv = reallocf(rv, rv_size))) {
						warn(NULL);
						return NULL;
					}
					strlcat(rv, var->val, rv_size);
					rv_cp = rv + strlen(rv);
					len -= strlen(string) + 1;
				}
		}
		string = cp + 1;	
	}	

	/* no '$', just copy the rest */
	memcpy(rv_cp, string, len);
	rv_cp[len] = '\0';
	return rv;
}

const char
*cfg_get_pager(void)
{
	return Pager ? (const char *)Pager : "/bin/cat";
}
