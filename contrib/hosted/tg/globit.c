/*-
 * Copyright © 2014
 *	Thorsten “mirabilos” Glaser <t.glaser@tarent.de>
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

#define _GNU_SOURCE
#include <errno.h>
#include <glob.h>
#include <limits.h>
#include <paths.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#undef __RCSID
#define __RCSID(x)	static const char rcsid[] = "@(""#)rcsid: " x

int globit_best(const char *, char **);

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

int
main(int argc, char *argv[])
{
	int rsn;
	char *rsv;

	if (argc != 2) {
		fprintf(stderr, "%s\nusage: globit filename\n", rcsid);
		return (2);
	}

	if ((rsn = globit_best(argv[1], &rsv)) == -1) {
		fprintf(stderr, "globit error: %s\n",
		    rsv ? rsv : "unknown error");
		free(rsv);
		return (2);
	}
	if (rsn == 0) {
		fprintf(stderr, "no match\n");
		return (1);
	}
	fprintf(stderr, "%i match%s\n", rsn, rsn == 1 ? "" : "es");
	printf("%s\n", rsv);
	free(rsv);
	return (0);
}

/*
 * globit_best – return the “best præfix” for a pattern, or the sole match
 *
 * Arguments:
 * – [in] const char *pattern
 * – [out] char **result
 * Return value:
 * – (int) number of matches
 *   + if -1: an error occurred; *result is the error string (or NULL)
 *   + if 0: *result is unchanged
 *   + if 1: *result contains the sole match
 *   + else: *result contains the longest common præfix
 * In all cases where it is set, the caller has to free(*result) later.
 */

/* helper functions */

#ifndef _PATH_DEFPATH
#define _PATH_DEFPATH "/bin:/usr/bin:/sbin:/usr/sbin"
#endif

static char *
globit_escape(const char *istr)
{
	char c, *cp, *ostr;
	size_t i;

	if (!(cp = ostr = calloc((i = strlen(istr)) + 1, 2)))
		return (NULL);

	/* strictly spoken, newline should be single-quoted instead */
	while (i--) {
		if (strchr("\t\n \"#$&'()*:;<=>?[\\`{|}", (c = *istr++)))
			*cp++ = '\\';
		*cp++ = c;
	}
	*cp = '\0';

	return (ostr);
}

static int
globit_pfxlen(char **words, int nwords)
{
	int j, prefix_len;
	char *p;
	int i;

	prefix_len = strlen(words[0]);
	for (i = 1; i < nwords; i++)
		for (j = 0, p = words[i]; j < prefix_len; j++)
			if (p[j] != words[0][j]) {
				prefix_len = j;
				break;
			}
	return (prefix_len);
}

/* main function */

int
globit_best(const char *pattern_, char **result)
{
	char c, *cp, **results = NULL;
	size_t z, nresults = 0;
	int i;
	int glob_flags = GLOB_MARK |
#ifdef GLOB_NO_DOTDIRS
	    GLOB_NO_DOTDIRS |
#endif
	    GLOB_NOSORT;
	int is_absolute = 0;
	char *pattern, *pf = NULL, *pp = NULL, *pathpfx = NULL, *pathstr = NULL;
	size_t pathlen = 0;
	glob_t glob_block;
	const char *errstr = NULL;

	/* initialise pattern, with ‘*’ appended unless it already has magic */
	if (!(pattern = malloc((z = strlen(pattern_)) + 2))) {
		*result = strdup("not enough memory");
		return (-1);
	}
	memcpy(pattern, pattern_, z);
	if (glob_pattern_p(pattern_, 1) == 0)
		pattern[z++] = '*';
	pattern[z] = '\0';
	cp = pattern;

	/* check if pattern is absolute */
	if (*pattern == '/') {
		/* yes, pathname */
		is_absolute = 1;
	} else if (*pattern == '~') {
		/* yes, tilde */
		is_absolute = 2;
		glob_flags |= GLOB_TILDE;
		/* any slash in the pattern? */
		while (*cp && *cp != '/')
			++cp;
		if (!*cp) {
			/* no, so don’t append ‘*’ */
			memcpy(pattern, pattern_, z + 1);
		}
		cp = pattern;
		/* TODO: keep tilde unexpanded in return value (hard) */
	} else {
		/* no, get $PATH */
		cp = getenv("PATH");
		pp = pathstr = strdup(cp && *cp ? cp : _PATH_DEFPATH);
 glob_repeatedly:
		/* get one path element */
		cp = pp;
		while ((c = *cp) && c != ':')
			++cp;
		*cp = '\0';
		free(pathpfx);
		pathpfx = strdup(cp == pp ? "." : pp);
		*cp = c;
		/* advance path præfix */
		pp = cp;
		if (c)
			++pp;
		/* construct pattern for this round */
		pathlen = strlen(pathpfx) + 1;
		if (!(cp = globit_escape(pathpfx)))
			goto oom;
		free(pathpfx);
		pathpfx = cp;
		if (asprintf(&cp, "%s/%s", pathpfx, pattern) == -1) {
			errstr = "could not compose path";
			goto errout;
		}
		free(pf);
		pf = cp;
	}

	/* collect (one round of) glob results */
	memset(&glob_block, '\0', sizeof(glob_block));
	switch (glob(cp, glob_flags, NULL, &glob_block)) {
	case 0:
		/* success */
		if ((i = glob_block.gl_pathc) < 0) {
			globfree(&glob_block);
			errstr = "negative result set size";
			goto errout;
		}
		break;
	case GLOB_NOMATCH:
		/* or close enough */
		i = 0;
		break;
	case GLOB_NOSPACE:
		errstr = "not enough space for glob";
		if (0)
			/* FALLTHROUGH */
	case GLOB_ABORTED:
		  errstr = "glob was aborted due to an error";
		if (0)
			/* FALLTHROUGH */
	case GLOB_NOSYS:
		  errstr = "glob library does not support requested function";
		if (0)
			/* FALLTHROUGH */
	default:
		  errstr = "unknown glob error";
		globfree(&glob_block);
		goto errout;
	}

	/* if we have only one round, work directly on the results */
	if (is_absolute) {
		switch (i) {
		case 0:
			break;
		case 1:
			*result = globit_escape(glob_block.gl_pathv[0]);
			break;
		default:
			z = globit_pfxlen(glob_block.gl_pathv, i);
			if (z == 0) {
				i = 0;
				break;
			}
			if (!(cp = strdup(glob_block.gl_pathv[0])))
				goto oom;
			cp[z] = '\0';
			*result = globit_escape(cp);
			free(cp);
			break;
		}
		globfree(&glob_block);
 ok_out:
		if (i && !*result)
			goto oom;
		free(pf);
		free(pathpfx);
		free(pathstr);
		free(pattern);
		return (i);
	}

	/* otherwise, post-process the results */
	if (i) {
		int j = 0;
		char **r2;

		if (((size_t)i > ((size_t)INT_MAX - nresults)) ||
		    ((SIZE_MAX / sizeof(char *)) < (z = nresults + i))) {
			errstr = "too many results";
			goto errout;
		}
		if ((r2 = realloc(results, z * sizeof(char *))) == NULL) {
 oom:
			errstr = "not enough memory";
			goto errout;
		}
		results = r2;
		while (j < i) {
			cp = glob_block.gl_pathv[j++];
			if (strlen(cp) >= pathlen)
				cp += pathlen;
			results[nresults++] = strdup(cp);
		}
	}

	/* next round */
	globfree(&glob_block);
	if (*pp)
		goto glob_repeatedly;

	/* operate on the postprocessed results */
	switch ((i = (int)nresults)) {
	case 0:
		goto ok_out;
	default:
		z = globit_pfxlen(results, i);
		if (z == 0) {
			i = 0;
			goto ok_out;
		}
		results[0][z] = '\0';
		/* FALLTHROUGH */
	case 1:
		*result = globit_escape(results[0]);
		break;
	}

	while (nresults--)
		free(results[nresults]);
	free(results);
	goto ok_out;

 errout:
	if (results) {
		while (nresults--)
			free(results[nresults]);
		free(results);
	}
	free(pf);
	free(pathpfx);
	free(pathstr);
	free(pattern);
	*result = errstr ? strdup(errstr) : NULL;
	return (-1);
}
