/* $MirOS: ports/infrastructure/pkgtools/lib/libspec.c,v 1.1.2.2 2010/06/12 20:27:11 bsiegert Exp $ */

/*-
 * Copyright (c) 2010
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
 * routines handling library specifications (libspecs)
 */

#include <assert.h>
#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/libspec.c,v 1.1.2.2 2010/06/12 20:27:11 bsiegert Exp $");

/* special value for major below if the libspec was of the ".la" type */
#define LIBSPEC_LA -1

struct libspec {
	const char *libname;
	const char *path;
	long int major;
	long int minor;
};

/* find a dot followed by one or more digits at the end of str.
 * Returns a pointer to the dot or NULL if other characters were
 * found instead.
 */
static char *
strrdot(char *str)
{
	char *s;

	assert(str != NULL);

	s = str + strlen(str) - 1;
	if (!isdigit(*s))
		return NULL;

	while (isdigit(*s) && s > str)
		s--;
	return *s == '.' ? s : NULL;
}

/* Parses the libspec given in spec, of the form:
 * [path/]name[.major[.minor]] or [path/]name.la
 *
 * Elements of spec will be stored in ls along with the version numbers.
 * Do not free() spec before ls.
 */
static void
parse_libspec(char *spec, struct libspec *ls)
{
	char *slash, *dot, *dot2;
	int len;

	assert(spec != NULL);
	assert(ls != NULL);

	/* search for a path, of the form path/name.1.2 */
	if ((slash = strrchr(spec, '/')) != NULL) {
		*slash = '\0';
		ls->path = spec;
		spec = slash + 1;
	} else
		ls->path = NULL;

	if ((dot = strrdot(spec)) == NULL) {
		/* shortcut path */
		len = strlen(spec);
		if (!strcmp(spec+len-3, ".la"))
			ls->major = LIBSPEC_LA;
		else
			ls->major = 0;
		ls->minor = 0;
		ls->libname = spec;
		return;
	}

	*dot = '\0';
	if ((dot2 = strrdot(spec)) == NULL) {
		/* foo.2 */
		ls->major = strtol(dot + 1, NULL, 10);
		ls->minor = 0;
	} else {
		/* foo.2.1 */
		ls->major = strtol(dot2 + 1, NULL, 10);
		ls->minor = strtol(dot + 1, NULL, 10);
		*dot2 = '\0';
	}
	ls->libname = spec;
	if (!ls->path)
		ls->path = "lib";
	return;
}

/* Returns true if the library at filename has at least the given major
 * and minor. path contains the full path up to and including libname.
 */
static bool
library_matches(char *filename, const char *path, long int major, long int minor)
{
	char *endptr;
	long num;

	/* filename begins with path? */
	if (strncmp(filename, path, strlen(path))) {
		pwarnx("Internal error: filename does not match prefix path");
		return false;
	}
	filename += strlen(path);

	/* match any version */
	if (major <= 0)
		return true;

	/* check major */
	if (*filename == '.')
		filename++;
	if (strlen(filename) > 3 && !strncmp(filename, "so.", 3))
		filename += 3;
	num = strtol(filename, &endptr, 10);
	if (filename == endptr || num < major)
		return false;
	if (num > major || (num == major && minor == 0L))
		return true;

	/* check minor */
	filename = endptr;
	if (*filename == '.')
		filename++;
	num = strtol(filename, &endptr, 10);
	if (filename == endptr || num < minor)
		return false;

	return true;
}

/* Given a libspec or several ones with a comma in between,
 * check if a matching library exists in the prefix.
 */
bool
match_libspec(char *spec, const char *prefix, ld_type_t ld_type)
{
	struct libspec ls;
	char *s, filename[FILENAME_MAX];
	int i;
	bool found;
	glob_t pglob;

	assert(prefix != NULL);

	while ((s = strsep(&spec, ",")) != NULL) {
		parse_libspec(s, &ls);
		if (!ls.libname || *ls.libname == '\0') {
			pwarnx("malformed library specification '%s'", s);
			return false;
		}
		if (ls.major == LIBSPEC_LA) {
			diag(" searching for libtool library %s in %s",
				ls.libname, ls.path ? ls.path : "lib");
			snprintf(filename, sizeof (filename), "%s/%s/lib%s",
					prefix, ls.path ? ls.path : "lib",
					ls.libname);
			if (!fexists(filename)) {
				diag(" - not found\n");
				return false;
			}
			diag(" - found\n");
			continue;
		} else
			diag(" searching for shared library %s (at least %ld.%ld) in %s\n",
				ls.libname, ls.major, ls.minor,	ls.path);

		snprintf(filename, sizeof (filename), ld_type == LD_DYLD ?
				"%s/%s/lib%s*dylib" : "%s/%s/lib%s.so.*",
				prefix, ls.path, ls.libname);
		memset(&pglob, 0, sizeof (pglob));
		glob(filename, 0, NULL, &pglob);
		if (pglob.gl_matchc == 0) {
			diag(" - not found\n");
			return false;
		}
		snprintf(filename, sizeof (filename), "%s/%s/lib%s",
				prefix, ls.path, ls.libname);
		found = false;
		for (i = 0; i < pglob.gl_matchc; i++) {
			if (library_matches(pglob.gl_pathv[i], filename,
						ls.major, ls.minor)) {
				diag(" - found %s\n", pglob.gl_pathv[i]);
				found = true;
				break;
			}
		}
		if (!found) {
			diag(" - not found\n");
			return false;
		}
	}
	return true;
}
