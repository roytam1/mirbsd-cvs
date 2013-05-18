/*
 * Copyright � 2002 Keith Packard, member of The XFree86 Project, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/* $XFree86: xc/extras/fontconfig/fc-list/fc-list.c,v 1.3 2003/09/13 21:33:00 dawes Exp $ */

#include <fontconfig/fontconfig.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#ifdef linux
#define HAVE_GETOPT_LONG 1
#endif
#define HAVE_GETOPT 1
#if defined(ISC) || defined(Lynx)
#define HAVE_OPTARG_IN_UNISTD 0
#endif
#endif

#ifndef HAVE_GETOPT
#define HAVE_GETOPT 0
#endif
#ifndef HAVE_GETOPT_LONG
#define HAVE_GETOPT_LONG 0
#endif
#ifndef HAVE_OPTARG_IN_UNISTD
#define HAVE_OPTARG_IN_UNISTD HAVE_GETOPT
#endif

#if HAVE_GETOPT_LONG
#undef  _GNU_SOURCE
#define _GNU_SOURCE
#include <getopt.h>
const struct option longopts[] = {
    {"version", 0, 0, 'V'},
    {"verbose", 0, 0, 'v'},
    {"help", 0, 0, '?'},
    {NULL,0,0,0},
};
#else
#if HAVE_GETOPT && !HAVE_OPTARG_IN_UNISTD
extern char *optarg;
extern int optind, opterr, optopt;
#endif
#endif

static void usage (char *program)
{
#if HAVE_GETOPT_LONG || HAVE_GETOPT
    fprintf (stderr,
	     "usage: %s [-V?] [--version] [--help] [pattern] {element ...} \n",
	     program);
    fprintf (stderr, "List fonts matching [pattern]\n");
    fprintf (stderr, "\n");
    fprintf (stderr,
	     "  -V, --version        display font config version and exit\n");
    fprintf (stderr, "  -?, --help           display this help and exit\n");
#else
    fprintf (stderr, "usage: %s [pattern] {element ...} \n", program);
    fprintf (stderr, "List fonts matching [pattern]\n");
#endif
    exit (1);
}

int
main (int argc, char **argv)
{
    int		i;
    FcObjectSet *os = 0;
    FcFontSet	*fs;
    FcPattern   *pat;
#if HAVE_GETOPT_LONG || HAVE_GETOPT
    int		c;

#if HAVE_GETOPT_LONG
    while ((c = getopt_long (argc, argv, "Vv?", longopts, NULL)) != -1)
#else
    while ((c = getopt (argc, argv, "Vv?")) != -1)
#endif
    {
	switch (c) {
	case 'V':
	    fprintf (stderr, "fontconfig version %d.%d.%d\n", 
		     FC_MAJOR, FC_MINOR, FC_REVISION);
	    exit (0);
	case 'v':
	    /* Ignore */
	    break;
	default:
	    usage (argv[0]);
	}
    }
    i = optind;
#else
    i = 1;
#endif

    if (!FcInit ())
    {
	fprintf (stderr, "Can't init font config library\n");
	return 1;
    }
    if (argv[i])
    {
	pat = FcNameParse ((FcChar8 *) argv[i]);
	while (argv[++i])
	{
	    if (!os)
		os = FcObjectSetCreate ();
	    FcObjectSetAdd (os, argv[i]);
	}
    }
    else
	pat = FcPatternCreate ();
    
    if (!os)
	os = FcObjectSetBuild (FC_FAMILY, FC_STYLE, 0);
    fs = FcFontList (0, pat, os);
    if (pat)
	FcPatternDestroy (pat);

    if (fs)
    {
	int	j;

	for (j = 0; j < fs->nfont; j++)
	{
	    FcChar8 *font;
	    FcChar8 *file;

	    font = FcNameUnparse (fs->fonts[j]);
	    if (FcPatternGetString (fs->fonts[j], FC_FILE, 0, &file) == FcResultMatch)
		printf ("%s: ", file);
	    printf ("%s\n", font);
	    free (font);
	}
	FcFontSetDestroy (fs);
    }
    return 0;
}
