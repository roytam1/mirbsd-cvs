/* $MirOS: ports/infrastructure/pkgtools/create/main.c,v 1.2 2007/03/30 23:20:10 bsiegert Exp $ */
/* $OpenBSD: main.c,v 1.13 2003/08/15 00:03:22 espie Exp $	*/

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Jordan K. Hubbard
 * 18 July 1993
 *
 * This is the create module.
 */

#include <err.h>
#include "lib.h"
#include "create.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/create/main.c,v 1.2 2007/03/30 23:20:10 bsiegert Exp $");

static char Options[] = "C:c:D:d:e:f:hi:k:m:OP:p:r:S:s:t:vX:Z";

char	*Prefix		= NULL;
char	*Comment	= NULL;
char	*Desc		= NULL;
char	*SrcDir		= NULL;
char	*Display	= NULL;
char	*Install	= NULL;
char	*DeInstall	= NULL;
char	*Contents	= NULL;
char	*Require	= NULL;
char	*ExcludeFrom	= NULL;
char	*Mtree		= NULL;
char	*Pkgdeps	= NULL;
char	*Emulations	= NULL;
char	*Pkgcfl		= NULL;
char	*BaseDir	= NULL;
char	PlayPen[FILENAME_MAX];
size_t	PlayPenSize	= sizeof(PlayPen);
int	Dereference	= 0;
bool	PlistOnly	= false;
int	WantUSTAR	= 0;

static __dead void usage(void);

int
main(int argc, char **argv)
{
    int ch;
    char **pkgs, **start;

    pkgs = start = argv;
    while ((ch = getopt(argc, argv, Options)) != -1)
	switch(ch) {
	case 'v':
	    Verbose = true;
	    break;

	case 'O':
	    PlistOnly = true;
	    break;

	case 'Z':
	    WantUSTAR = 1;
	    break;

	case 'p':
	    Prefix = optarg;
	    break;

	case 's':
	    SrcDir = optarg;
	    break;

	case 'S':
	    BaseDir = optarg;
	    break;

	case 'f':
	    Contents = optarg;
	    break;

	case 'c':
	    Comment = optarg;
	    break;

	case 'd':
	    Desc = optarg;
	    break;

	case 'i':
	    Install = optarg;
	    break;

	case 'k':
	    DeInstall = optarg;
	    break;

	case 'r':
	    Require = optarg;
	    break;

	case 't':
	    strlcpy(PlayPen, optarg, PlayPenSize);
	    break;

	case 'X':
	  /* XXX this won't work until someone adds the gtar -X option
	     (--exclude-from-file) to paxtar - so long it is disabled
	     in perform.c */
	    printf("WARNING: the -X option is not supported in OpenBSD\n");
	    ExcludeFrom = optarg;
	    break;

	case 'h':
	    Dereference = 1;
	    break;

	case 'D':
	    Display = optarg;
	    break;

	case 'm':
	    Mtree = optarg;
	    break;

	case 'P':
	    Pkgdeps = optarg;
	    break;

	case 'C':
	    Pkgcfl = optarg;
	    break;

	case 'e':
	    Emulations = optarg;
	    break;

	case '?':
	default:
	    usage();
	    break;
	}

    argc -= optind;
    argv += optind;

    /* Get all the remaining package names, if any */
    while (*argv)
	*pkgs++ = *argv++;

    /* If no packages, yelp */
    if (pkgs == start)
	pwarnx("missing package name"), usage();
    *pkgs = NULL;
    if (start[1])
	pwarnx("only one package name allowed ('%s' extraneous)", start[1]),
	usage();
    if (!pkg_perform(start)) {
	if (Verbose)
	    pwarnx("package creation failed");
	return 1;
    }
    else
	return 0;
}

static __dead void
usage(void)
{
    fprintf(stderr, "%s\n%s\n%s\n%s\n",
"usage: pkg_create [-OZhv] [-P dpkgs] [-C cpkgs] [-p prefix] [-f contents]",
"                  [-i iscript] [-k dscript] [-r rscript] [-t template]",
"                  [-X excludefile] [-D displayfile] [-m mtreefile]",
"                  -c comment -d description -f packlist -S basedir pkg-name");
    exit(1);
}
