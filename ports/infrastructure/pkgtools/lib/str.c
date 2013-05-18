/**	$MirOS: ports/infrastructure/pkgtools/lib/str.c,v 1.13 2009/11/29 13:42:45 bsiegert Exp $ */
/*	$OpenBSD: str.c,v 1.11 2003/07/04 17:31:19 avsm Exp $	*/

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Jordan K. Hubbard
 * 18 July 1993
 *
 * Miscellaneous string utilities.
 */

#include <err.h>
#include <fnmatch.h>
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/str.c,v 1.13 2009/11/29 13:42:45 bsiegert Exp $");

/* "normalize" a URL by replacing all the characters which are "not nice"
 * in a filename by '_' characters.
 */
void
normalize_name(char *filename)
{
	char *cp;

	if (!filename)
		return;

	for (cp = filename; *cp; cp++) {
		switch (*cp) {
			case ':':
			case '/':
			case '.':
			case '~':
			case '$':
			case '%':
			case '@':
			case '?':
			case '&':
				*cp = '_';
				break;
		}
	}
}

/* Convert a filename (which can be relative to the current directory) to
 * an absolute one. Returns a pointer to a static internal buffer.
 */
char *
toabs(const char *filename, const char *cwd)
{
	static char bname[FILENAME_MAX];

	memset(bname, 0, sizeof(bname));
	if (filename[0] == '/')
		strlcpy(bname, filename, sizeof(bname));
	else
		(void) snprintf(bname, sizeof(bname), "%s/%s", cwd, filename);

	return bname;
}

char *
strconcat(const char *s1, const char *s2)
{
    static char tmp[FILENAME_MAX];

    strlcpy(tmp, s1 ? s1 : s2, sizeof(tmp));
    if (s1 && s2)
	strlcat(tmp, s2, sizeof(tmp));
    return tmp;
}

/* Get a string parameter as a file spec or as a "contents follow -" spec */
char *
get_dash_string(char **str)
{
    char *s = *str;

    if (*s == '-')
	*str = copy_string(s + 1);
    else
	*str = fileGetContents(s);
    return *str;
}

/* Rather Obvious */
char *
copy_string(const char *str)
{
    char *ret;

    if (!str)
	ret = NULL;
    else {
	ret = strdup(str);
    }
    return ret;
}

/* Return true if 'str' ends in suffix 'suff' */
bool
suffix(char *str, char *suff)
{
    char *idx;
    bool ret = false;

    idx = strrchr(str, '.');
    if (idx && !strcmp(idx + 1, suff))
	ret = true;
    return ret;
}

/* Assuming str has a suffix, brutally murder it! */
void
nuke_suffix(char *str)
{
    char *idx;

    idx = strrchr(str, '.');
    if (idx)
	*idx = '\0';  /* Yow!  Don't try this on a const! */
}

/* Find the version number in a package name. Use this instead of
 * strrchr(name, '-').
 */
char *
find_version(const char *name)
{
    char *idx;

    if (!name)
	return NULL;
    for (idx = strchr(name + 1, '-'); idx && *idx && !isdigit(idx[1])
		&& idx[1] != '<' && idx[1] != '>'  && idx[1] != '*';
		idx = strchr(idx + 1, '-'));

    return idx;
}

/* Remove the version number from a package name. Optionally add a
 * "-*" suffix at the end.
 */
char *
nuke_version(char *name, bool wildcard)
{
    char *idx, *ret;

    if (!name)
	return NULL;

    if ((idx = find_version(name)))
	*idx = '\0';
    if (asprintf(&ret, wildcard ? "%s-[0-9]*" : "%s", name) == -1) {
	printf("nuke_version: Could not allocate buffer\n");
	return NULL;
    }
    if (idx)
	*idx = '-';
    return ret;
}

/* Find the flavour in a package name.
 */
char *
find_flavour(const char *name)
{
    char *idx;

    if (!name)
	return NULL;
    for (idx = strchr(name + 1, '-'); idx && *idx && !isalpha(idx[1])
		&& idx[1] != '!'; idx = strchr(idx + 1, '-'));

    return idx;
}

/* Lowercase a whole string */
void
str_lowercase(char *str)
{
    while (*str) {
	*str = tolower(*str);
	++str;
    }
}


enum deweycmp_ops {
	GT,
	GE,
	LT,
	LE,
	NONE
};

/* match flavour part of a package against a flavour pattern
 * used by multiversion_match below
 */
static int
flavourcmp(char *pkg_flavour, char *pattern)
{
	char tmp[FILENAME_MAX];
	char *token, *cp;		/* outer strsep loop */
	char *pkg_token, *pkg_match;	/* inner strsep loop */
	bool may_not_match, did_match = false;

	if (!pattern)
		return 1;
	if (pkg_flavour)
		pkg_flavour++; /* jump over '-' */
	
	token = pattern;
	while ((cp = strsep(&token, ",")) != NULL) {
		may_not_match = (*cp == '!');
		if (may_not_match)
			cp++;
		/* check against all flavours of pkg */
		if (pkg_flavour)
			strlcpy(tmp, pkg_flavour, sizeof(tmp));
		else
			*tmp = '\0';
		pkg_token = pkg_flavour;
		while ((pkg_match = strsep(&pkg_token, "-")) != NULL)
			did_match |= !strcmp(cp, pkg_match);
		if ((may_not_match && did_match) ||
				(!may_not_match && !did_match))
			return 0;
	}
	return 1;
}

/* compare two dewey decimal numbers */
static int
deweycmp(char *a, enum deweycmp_ops op, char *b)
{
	int             ad;
	int             bd;
	int             cmp;

	for (;;) {
		if (*a == 0 && *b == 0) {
			cmp = 0;
			break;
		}
		ad = bd = 0;
		for (; *a && *a != '.' && *a != '-'; a++) {
			ad = (ad * 10) + (*a - '0');
		}
		for (; *b && *b != '.' && *b != '-'; b++) {
			bd = (bd * 10) + (*b - '0');
		}
		if ((cmp = ad - bd) != 0) {
			break;
		}
		if (*a == '.') {
			a++;
		}
		if (*b == '.') {
			b++;
		}
		/* we might have a patchlevel in a but not in b or vice versa */
		if (*a == '-') {
			if (*b == '-') {
				a++;
				b++;
			} else if (*b == 0) {
				cmp = 0;
				break;
			}
		} else if ((*a == 0) && (*b == '-')) {
			cmp = 0;
			break;
		}
	}
	return (op == GE) ? cmp >= 0 : (op == GT) ? cmp > 0 : (op == LE) ? cmp <= 0 : cmp < 0;
}

/* perform alternate match on "pkg" against "pattern", */
/* calling pmatch (recursively) to resolve any other patterns */
/* return 1 on match, 0 otherwise */
static int
alternate_match(const char *pattern, const char *pkg)
{
	char           *sep;
	char            buf[FILENAME_MAX];
	char           *last;
	char           *alt;
	char           *cp;
	int             cnt;
	int             found;

	if ((sep = strchr(pattern, '{')) == NULL) {
		errx(1, "alternate_match(): '{' expected in \"%s\"", pattern);
	}
	(void) strncpy(buf, pattern, (size_t)(sep - pattern));
	alt = &buf[sep - pattern];
	last = NULL;
	for (cnt = 0, cp = sep; *cp && last == NULL ; cp++) {
		if (*cp == '{') {
			cnt++;
		} else if (*cp == '}' && --cnt == 0 && last == NULL) {
			last = cp + 1;
		}
	}
	if (cnt != 0) {
		pwarnx("Malformed alternate '%s'", pattern);
		return 1;
	}
	for (found = 0, cp = sep + 1; *sep != '}'; cp = sep + 1) {
		for (cnt = 0, sep = cp; cnt > 0 || (cnt == 0 && *sep != '}' && *sep != ','); sep++) {
			if (*sep == '{') {
				cnt++;
			} else if (*sep == '}') {
				cnt--;
			}
		}
		(void) snprintf(alt, sizeof(buf) - (alt - buf), "%.*s%s", (int) (sep - cp), cp, last);
		if (pmatch(buf, pkg) == 1) {
			found = 1;
		}
	}
	return found;
}

/* perform dewey match on "pkg" against "pattern" */
/* return 1 on match, 0 otherwise */
static int
dewey_match(const char *pattern, const char *pkg)
{
	char           *cp;
	char           *sep;
	char           *ver;
	int             found;
	enum deweycmp_ops op;
	int             n;
	char            name[FILENAME_MAX];

	found = 0;
	if ((sep = strpbrk(pattern, "<>")) == NULL)
		errx(1, "dewey_match(): '<' or '>' expexted in \"%s\"", pattern);

	/* next few lines are static in loops, too (-> cache!) */
	snprintf(name, sizeof(name), "%.*s", (int) (sep - pattern), pattern);
	n = (int)(sep - pattern);
	if (name[strlen(name) - 1] == '-') {
		name[strlen(name) - 1] = '\0';
		n--;
	}
	op = (*sep == '>') ? (*(sep + 1) == '=') ? GE : GT : (*(sep + 1) == '=') ? LE : LT;
	ver = (op == GE || op == LE) ? sep + 2 : sep + 1;
	if ((cp = find_version(pkg)) != NULL) {
		if (strncmp(pkg, name, (size_t)(cp - pkg)) == 0 && n == cp - pkg) {
			if (deweycmp(cp + 1, op, ver)) {
				found = 1;
			}
		}
	}
	return found;
}

/* perform glob match on "pkg" against "pattern" */
/* return 1 on match, 0 otherwise */
static int
glob_match(const char *pattern, const char *pkg)
{
	return fnmatch(pattern, pkg, FNM_PERIOD) == 0;
}

/* perform match on multiple version numbers */
/* return 1 on match, 0 otherwise */
static int
multiversion_match(const char *pattern, const char *pkg)
{
	char *cp, *ver, *token;
	char *flavour = NULL;
	char name[FILENAME_MAX];
	enum deweycmp_ops op;
	int result = 0;

	/* short-cut path if the name does not match */
	ver = find_version(pkg);
	if ((cp = find_version(pattern)) == NULL)
		errx(1, "multiversion_match(): malformed pattern '%s'!", pattern);
	/* name must have the same size, of course */
	if ((ver - pkg) != (cp - pattern))
		return 0;
	if (strncmp(pattern, pkg, (size_t)(ver - pkg)))
		return 0;

	ver++; /* jump over '-' */
	strlcpy(name, cp + 1, sizeof(name));
	token = name;

	/* Does the match have a flavour part? */
	flavour = find_flavour(name);
	if (flavour) {
		*flavour = '\0'; /* limit multiver match to non-flavour part */
		flavour++;
	}

	while ((cp = strsep(&token, ",")) != NULL) {
		op = NONE;
		if (*cp == '>')
			op = (cp[1] == '=') ? GE : GT;
		else if (*cp == '<')
			op = (cp[1] == '=') ? LE : LT;
		if (op == NONE && glob_match(cp, ver)) {
			result = 1;
			break;
		}
		if (op != NONE) {
		       	result = deweycmp(ver, op, (op == GE || op == LE) ?
					cp + 2 : cp + 1);
			if (!result)
				break;
		}
	}
	if (!result || !flavour)
		return result;
	return flavourcmp(find_flavour(find_version(pkg)), flavour);
}

/* perform simple match on "pkg" against "pattern" */
/* return 1 on match, 0 otherwise */
static int
simple_match(const char *pattern, const char *pkg)
{
	return !strcmp(pattern, pkg);
}

/* match pkg against pattern, return 1 if matching, 0 else */
/*
 * Optimize: this is called many times in readdir()-loops, where the
 * pattern doesn't change, so the {,} alternates may be unrolles/cached.
 */
int
pmatch(const char *pattern, const char *pkg)
{
	char *cp;

	if (strchr(pattern, '{')) {
		/* emulate csh-type alternates */
		return alternate_match(pattern, pkg);
	}
	if (strpbrk(pattern, ",!")) {
		/* perform match on multiple versions */
		return multiversion_match(pattern, pkg);
	}
	if ((cp = strpbrk(pattern, "<>"))) {
		if (!strchr(cp, '-')) {
			/* perform relational dewey match on version number */
			return dewey_match(pattern, pkg);
		} else {
			/* special case: one version, one flavour */
			return multiversion_match(pattern, pkg);
		}
			
	}
	if (strpbrk(pattern, "*?[]")) {
		/* glob match */
		return glob_match(pattern, pkg);
	}
	/* no alternate, dewey or glob match -> simple compare */
	return simple_match(pattern, pkg);
}


/* search dir for pattern, writing the found match in buf */
/* let's hope there's only one ... - HF */
/* returns -1 on error, 1 if found, 0 otherwise. */
int
findmatchingname(const char *dir, const char *pattern, matchfn f, char *data, int len)
{
    struct dirent  *dp;
    DIR            *dirp;
    int             found;

    found = 0;
    if ((dirp = opendir(dir)) == NULL) {
	/* pwarnx("can't opendir dir '%s'", dir); */
	return -1;
    }
    while ((dp = readdir(dirp)) != NULL) {
	if (strcmp(dp->d_name, ".") == 0 ||
	    strcmp(dp->d_name, "..") == 0) {
	    continue;
	}
	if (pmatch(pattern, dp->d_name)) {
	    if(f)
		f(dp->d_name, data, len);
	    found=1;
	}
    }
    closedir(dirp);

    return found;
}

/* does the pkgname contain any of the special chars ("{[]?*<>")? */
/* if so, return 1, else 0 */
int
ispkgpattern(const char *pkg)
{
    return strpbrk(pkg, "<>[]?*{") != NULL;
}

/* auxiliary function called by findbestmatchingname() */
static int
findbestmatchingname_fn(const char *pkg, char *data, int len)
{
    /* if pkg > data */
    char *s1, *s2;

    s1 = find_version(pkg);
    s2 = find_version(data);
    if (!s1 || !s2)
	return 0;

    if (data[0] == '\0' || deweycmp(++s1, GT, ++s2))
	strlcpy(data, pkg, len);

    return 0;
}

/* find best matching filename, i.e. the pkg with the highest
 * matching(!) version */
/* returns pointer to pkg name (which can be free(3)ed),
 * or NULL if no match is available. */
char *
findbestmatchingname(const char *dir, const char *pattern)
{
	char buf[FILENAME_MAX];

	buf[0]='\0';
	if (findmatchingname(dir, pattern, findbestmatchingname_fn, buf, sizeof(buf)) > 0 && buf[0] != '\0') {
		return strdup(buf);
	}
	return NULL;
}
