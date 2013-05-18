/* $MirOS: ports/infrastructure/pkgtools/lib/cfgfile.c,v 1.1.2.14 2010/10/19 19:41:16 bsiegert Exp $ */

/*-
 * Copyright (c) 2009, 2010
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
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/cfgfile.c,v 1.1.2.14 2010/10/19 19:41:16 bsiegert Exp $");

SLIST_HEAD(cfg_varlist, cfg_var);
struct cfg_var {
	char *key;
	char *val;
	SLIST_ENTRY(cfg_var) entries;
};

static struct cfg_varlist Vars = SLIST_HEAD_INITIALIZER(Vars);
static struct cfg_sourcelist Sources = LIST_HEAD_INITIALIZER(Sources);
static char *Pager = NULL;

/* Parse a line of the form "key=value", where i is the index of the '='
 * sign and len is the length of the string. Works even when the string is
 * not null-terminated.
 */
static void
parse_var(char *line, size_t i, size_t len)
{
	struct cfg_var *var;
	char *key, *val;

	assert(i < len);

	/* i is the position of the '='; everything before is the name,
	 * the value is everything after it */
	key = cfg_expand_vars(line, i);
	if (!key)
		return;
	val = cfg_expand_vars(line + i + 1, len - i - 1);
	if (!val) {
		warnx("%s: Variable expansion failed", key);
		free(key);
		return;
	}

	/* overwrite existing variable */
	SLIST_FOREACH(var, &Vars, entries) {
		if (!strcmp(key, var->key)) {
			free(var->val);
			var->val = val;
			free(key);
			return;
		}
	}

	var = malloc(sizeof (struct cfg_var));
	if (!var) {
		warn(NULL);
		free(key);
		free(val);
		return;
	}

	var->key = key;
	var->val = val;
	SLIST_INSERT_HEAD(&Vars, var, entries);
}

/* Parse a configuration directive of the form
 * 	Source 1 /usr/ports/Packages
 * where the first number is a priority (unsigned) and the rest is the
 * path---either local or remote, ftp and http.
 */
static void
parse_source(char *string, size_t len)
{
	char *arg, *sep;
	unsigned long priority;

	arg = cfg_expand_vars(string, len);
	if (!arg)
		return;
	
	priority = (unsigned long)strtol(arg, &sep, 0);
	if (!sep || *sep == '\0') {
		warnx("Syntax error in Source line '%s'", arg);
		free(arg);
		return;
	}
	while (*sep && isspace(*sep))
		sep++;
	
	cfg_add_source(priority, isURL(sep), sep);

	free(arg);
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
	} else if (i == 6 && !strncasecmp(line, "Source", i)) {
		parse_source(line + i + 1, len - i - 1);
	} else
		warnx("Unrecognized command: %s", line);
}

/* Read the configuration file. Returns true if successful, false otherwise.
 * The contents are saved in static variables, use the appropriate functions
 * to probe for them.
 * The argument is the filename for the configuration file, or NULL to use
 * the default.
 */
bool
cfg_read_config(const char *filename)
{
	FILE *cfgfile;
	char *line;
	size_t len, i;
	bool line_end;
	char *hashmark;

	cfgfile = fopen(filename ? filename : DEFAULT_CFGFILE, "r");
	if (!cfgfile) {
		warn("Error opening configuration file");
		return false;
	}

	do {
		line = fgetln(cfgfile, &len);
		if (!line)
			break;
		hashmark = (char *)memchr(line, '#', len);
		if (hashmark) {
			*hashmark = '\0';
			len = strlen(line);
		}
		if ((len > 0) && line[len - 1] == '\n')
			line[--len] = '\0';
		while ((len > 0) && isspace(line[len - 1]))
			line[--len] = '\0';
		while (isspace(*line)) {
			line++; len--;
		}
		line_end = false;
		for (i = 0; i < len; i++) {
			switch (line[i]) {
				case '\n':
				case '\0':
					line_end = true;
					break;
				case '=':
					parse_var(line, i, len);
					line_end = true;
					break;
				case '\t':
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
	fclose(cfgfile);
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

/* Dump name and value of _one_ variable to stdout. Used in regression tests.
 */
void
cfg_dump_var(const char *varname)
{
	struct cfg_var *var;
	
	SLIST_FOREACH(var, &Vars, entries) {
		if (!strcmp(varname, var->key)) {
			printf("%s = %s\n", var->key, var->val);
			return;
		}
	}
	printf("%s is undefined\n", varname);
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
	
	while (isspace(*string)) {
		string++; len--;
	}	

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
					if (!(rv = realloc(rv, rv_size))) {
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

/* Get the name of the pager for showing "DISPLAY" files */
const char
*cfg_get_pager(void)
{
	return Pager ? (const char *)Pager : "/bin/cat";
}

/* Debug function; dumps the list of sources to stdout */
void
cfg_dump_sources(void)
{
	struct cfg_source *sp;

	if (LIST_EMPTY(&Sources))
		return;

	LIST_FOREACH(sp, &Sources, entries)
		printf("Source %lu\t%s%s\n", sp->priority, sp->source,
				sp->remote ? " (remote)" : "");
}

/* Adds a package source to the list */
void
cfg_add_source(unsigned long priority, bool remote, const char *source)
{
	struct cfg_source *sp, *newsp;

	/* Check for duplicates */
	LIST_FOREACH(sp, &Sources, entries) {
		if (!strcmp(sp->source, source)) {
			if (sp->remote == remote && sp->priority == priority)
				return; /* entry already exists */
			else {
				/* entry exists but with different prio */
				LIST_REMOVE(sp, entries);
				free(sp->source);
				free(sp);
				break;
			}
		}
	}

	newsp = malloc(sizeof (struct cfg_source));
	if (!newsp) {
		warn(NULL);
		return;
	}

	newsp->source = strdup(source);
	if (!newsp->source) {
		warn(NULL);
		free(newsp);
		return;
	}
	newsp->remote = remote;
	newsp->priority = priority;

	if (Verbose)
		printf("Got package source '%s'%s, priority %lu\n",
				newsp->source,
				newsp->remote ? " (remote)" : "",
				newsp->priority);

	if (LIST_EMPTY(&Sources) ||
			LIST_FIRST(&Sources)->priority >= newsp->priority)
		LIST_INSERT_HEAD(&Sources, newsp, entries);
	else {
		LIST_FOREACH(sp, &Sources, entries) {
			if (sp->priority >= newsp->priority) {
				LIST_INSERT_BEFORE(sp, newsp, entries);
				return;
			}
			/* if not, insert at the end */
			if (!LIST_NEXT(sp, entries)) {
				LIST_INSERT_AFTER(sp, newsp, entries);
				return;
			}
		}
	}
}

/* delete a source from the list by giving its name. Returns true if the
 * source was in the list, false otherwise.
 */
bool
cfg_remove_source(const char *source)
{
	struct cfg_source *sp;

	if (!source)
		return NULL;

	LIST_FOREACH(sp, &Sources, entries) {
		if (!strcmp(source, sp->source)) {
			LIST_REMOVE(sp, entries);
			free(sp->source);
			free(sp);
			return true;
		}
	}

	return false;
}

/* Returns a static pointer to the existing source list */
const struct cfg_sourcelist *
cfg_get_sourcelist(void)
{
	if (LIST_EMPTY(&Sources)) {
		/* fill in a minimal default */
		cfg_add_source(0L, false, ".");
	}

	return &Sources;
}
