/*	$OpenBSD: read_bsd_terminfo.c,v 1.14 2003/06/17 21:56:24 millert Exp $	*/

/*
 * Copyright (c) 2006, 2009 Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1998, 1999, 2000 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * The following disclaimer must also be retained in all copies:
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <curses.priv.h>
#include <tic.h>
#include <term.h>	/* lines, columns, cur_term */
#include <term_entry.h>

__RCSID("$MirOS: src/lib/libncurses/src/ncurses/tinfo/read_bsd_terminfo.c,v 1.5 2006/10/31 02:52:39 tg Exp $");

#ifndef _PATH_TERMINFO
#define _PATH_TERMINFO	"/usr/share/misc/terminfo"
#endif /* ! _PATH_TERMINFO */

static char _path_terminfo[] = _PATH_TERMINFO;

/* Function prototypes for private functions, */
static int _nc_lookup_bsd_terminfo_entry(char *, char *, TERMTYPE * const);

/*
 * Look up ``tn'' in the BSD terminfo.db file and fill in ``tp''
 * with the info we find there.
 * Returns 1 on success, 0 on failure.
 */
int
_nc_read_bsd_terminfo_entry(const char * const tn_, char * const filename,
    TERMTYPE * const tp)
{
    char **fname, *p;
    char   envterm[PATH_MAX];		/* local copy of $TERMINFO */
    char   hometerm[PATH_MAX];		/* local copy of $HOME/.terminfo */
    char  *pathvec[4];			/* list of possible terminfo files */
    char  *tn;
    size_t len;

    if ((tn = strdup(tn_)) == NULL)
	return (0);

    fname = pathvec;
    /* $TERMINFO may hold a path to a terminfo file */
    if (use_terminfo_vars() && (p = getenv("TERMINFO")) != NULL) {
	len = strlcpy(envterm, p, sizeof(envterm));
	if (len < sizeof(envterm))
	    *fname++ = envterm;
    }

    /* Also check $HOME/.terminfo if it exists */
    if (use_terminfo_vars() && (p = getenv("HOME")) != NULL && *p != '\0') {
	len = snprintf(hometerm, sizeof(hometerm), "%s/.terminfo", p);
	if (len > 0 && len < sizeof(hometerm))
	    *fname++ = hometerm;
    }

    /* Finally we check the system terminfo file */
    *fname++ = _path_terminfo;
    *fname = NULL;

    /*
     * Lookup ``tn'' in each possible terminfo file until
     * we find it or reach the end.
     */
    for (fname = pathvec; *fname; fname++) {
	if (_nc_lookup_bsd_terminfo_entry(tn, *fname, tp) == 1) {
	    /* Set copyout parameter and return */
	    (void)strlcpy(filename, *fname, PATH_MAX);
	    free(tn);
	    return (1);
	}
    }
    free(tn);
    return (0);
}

/*
 * Given a path /path/to/terminfo/X/termname, look up termname
 * /path/to/terminfo.db and fill in ``tp'' with the info we find there.
 * Returns 1 on success, 0 on failure.
 */
int
_nc_read_bsd_terminfo_file(const char * const filename, TERMTYPE * const tp)
{
    char path[PATH_MAX];		/* path to terminfo.db */
    char *tname;			/* name of terminal to look up */
    char *p;

    (void)strlcpy(path, filename, sizeof(path));

    /* Split filename into path and term name components. */
    if ((tname = strrchr(path, '/')) == NULL)
	return (0);
    *tname++ = '\0';
    if ((p = strrchr(path, '/')) == NULL)
	return (0);
    *p = '\0';

    return (_nc_lookup_bsd_terminfo_entry(tname, path, tp));
}

/*
 * Look up ``tn'' in the BSD terminfo file ``filename'' and fill in
 * ``tp'' with the info we find there.
 * Returns 1 on success, 0 on failure.
 */
static int
_nc_lookup_bsd_terminfo_entry(char *tn, char *filename, TERMTYPE * const tp)
{
    char  *pathvec[2], *sfn;
    char  *capbuf, *cptr, *infobuf, *iptr;
    int    error;
    size_t len;
    ENTRY  thisentry;

    if (asprintf(&sfn, "getcap(%s)", filename) == -1)
	sfn = filename;

    pathvec[0] = filename;
    pathvec[1] = NULL;
    capbuf = NULL;
    infobuf = NULL;

    _nc_set_source(sfn);		/* For useful error messages */

    /* Don't prepend any hardcoded entries. */
    (void) cgetset(NULL);

    /* Lookup tn in 'filename' */
    error = cgetent(&capbuf, pathvec, tn);
    if (error == 0) {
	/*
	 * To make the terminfo parser happy we need to, as a minimum,
	 * 1) convert ':' separators to ','
	 * 2) add a newline after the name field
	 * 3) add a newline at the end of the entry
	 */

	/* Add space for 2 extra newlines and the final NUL */
	infobuf = malloc(strlen(capbuf) + 3);
	if (infobuf == NULL) {
	    error = TRUE;
	    goto done;
	}

	/* Copy name and aliases, adding a newline. */
	cptr = strchr(capbuf, ':');
	if (cptr == NULL) {
	    error = TRUE;
	    goto done;
	}
	len = cptr - capbuf;
	memcpy(infobuf, capbuf, len);
	iptr = infobuf + len;
	*iptr++ = ',';
	*iptr++ = '\n';

	/* Copy the rest of capbuf, converting ':' -> ',' */
	for (++cptr; *cptr; ++cptr)
		if ((*cptr == '\\') || (*cptr == '^')) {
			*iptr++ = *cptr++;
			if (!*cptr)
				break;
			*iptr++ = *cptr;
		} else if (*cptr == ':')
			*iptr++ = ',';
		else
			*iptr++ = *cptr;
	*iptr++ = '\n';
	*iptr = '\0';

	_nc_reset_input(NULL, infobuf);
	memset(&thisentry, 0, sizeof (thisentry));
	if (_nc_parse_entry(&thisentry, FALSE, FALSE) == ERR) {
		error = TRUE;
		goto done;
	}
	*tp = thisentry.tterm;
    }

done:
    if (capbuf)
	free(capbuf);
    if (infobuf)
	free(infobuf);
    cgetclose();

    _nc_set_source("");
    if (sfn != filename)
	free(sfn);

    return ((error == 0));
}
