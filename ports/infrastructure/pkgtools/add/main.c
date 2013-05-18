/* $MirOS: ports/infrastructure/pkgtools/add/main.c,v 1.5 2008/09/19 17:27:44 bsiegert Exp $ */
/* $OpenBSD: main.c,v 1.18 2003/08/06 20:46:36 millert Exp $	*/

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
 * This is the add module.
 */

#include <err.h>
#include <sys/param.h>
#include "lib.h"
#include "add.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/add/main.c,v 1.5 2008/09/19 17:27:44 bsiegert Exp $");

static char Options[] = "d:fhIMNnp:qRSt:v";

char	*Prefix		= NULL;
bool	NoInstall	= false;
bool	NoRecord	= false;
bool	NoBackups	= false;
bool	Quiet		= false;

char	*Mode		= NULL;
char	*Owner		= NULL;
char	*Group		= NULL;
char	*PkgName	= NULL;
const char *Directory	= NULL;
char	FirstPen[FILENAME_MAX];
add_mode_t AddMode	= NORMAL;
display_mode_t DisplayMode = CAT;

char **pkgs;
int pkg_count = 0;

static __dead void usage(void);

int
main(int argc, char **argv)
{
    int ch, error;
    char *cp;

    while ((ch = getopt(argc, argv, Options)) != -1) {
	switch(ch) {
	case 'd':
	    switch(optarg[0]) {
		case 'c':
		    DisplayMode = CAT;
		    break;
		case 'e':
		    DisplayMode = ENV;
		    break;
		case 'l':
		    DisplayMode = LESS;
		    break;
		case 'm':
		    DisplayMode = MORE;
		    break;
		default:
		    usage();
		    break;
	    }
	    break;
	case 'v':
	    Verbose = true;
	    break;

	case 'p':
	    Prefix = optarg;
	    break;

	case 'I':
	    NoInstall = true;
	    break;

	case 'R':
	    NoRecord = true;
	    break;

	case 'f':
	    Force = true;
	    break;

	case 'N':
	    NoBackups = true;
	    break;

	case 'n':
	    Fake = true;
	    Verbose = true;
	    break;

	case 'q':
	    Quiet = true;
	    break;

	case 't':
	    strlcpy(FirstPen, optarg, sizeof(FirstPen));
	    break;

	case 'S':
	    AddMode = SLAVE;
	    break;

	case 'M':
	    AddMode = MASTER;
	    break;

	case 'h':
	case '?':
	default:
	    usage();
	    break;
	}
    }
    argc -= optind;
    argv += optind;

    pkg_count = argc + 1;
    pkgs = (char **)calloc(pkg_count,  sizeof(char **));
    if (pkgs == NULL) {
    	fprintf(stderr, "malloc failed - abandoning package add.\n");
    	exit(1);
    }

    if (AddMode != SLAVE) {

	/* Get all the remaining package names, if any */
	for (ch = 0; *argv; ch++, argv++) {
	    /* Don't mangle stdin ("-") or URL arguments */
	    if ( (strcmp(*argv, "-") == 0)
		 || (isURL(*argv))) {
	         pkgs[ch] = strdup(*argv);
		 if (pkgs[ch] == NULL) {
		     fprintf(stderr,
			     "malloc failed - abandoning package add.\n");
		     exit(1);
		 }
	    }
	    else {			/* expand all pathnames to fullnames */
		char *s, *tmp;

		s=ensure_tgz(*argv);

		if (fexists(s)) { /* refers to a file directly */
		    pkgs[ch] = (char *) malloc(MAXPATHLEN * sizeof(char));
		    if (pkgs[ch] == NULL) {
		        fprintf(stderr,
				"malloc failed - abandoning package add.\n");
			exit(1);
		    }
		    tmp = realpath(s, pkgs[ch]);
		    if (tmp == NULL) {
		        perror("realpath failed");
			fprintf(stderr, "failing path was %s\n", pkgs[ch]);
			exit(1);
		    }
		}
		else if (ispkgpattern(*argv)
			 && (s=findbestmatchingname(dirname(*argv),
						    basename(*argv)))
			    != NULL) {
		    if (Verbose)
			printf("Using %s for %s\n",s, *argv);
		    pkgs[ch] = (char *) malloc(MAXPATHLEN * sizeof(char));
		    if (pkgs[ch] == NULL) {
		        fprintf(stderr,
				"malloc failed - abandoning package add.\n");
			exit(1);
		    }
		    tmp = realpath(s, pkgs[ch]);
		    if (tmp == NULL) {
		        perror("realpath failed");
			fprintf(stderr, "failing path was %s\n", pkgs[ch]);
			exit(1);
		    }
		    free(s);
		} else {
		    /* look for the file(pattern) in the expected places */
		    if (!(cp = fileFindByPath(NULL, *argv))) {
		        fprintf(stderr, "can't find package '%s'\n", s);
			exit(1);
		    }
		    else {
			pkgs[ch] = strdup(cp);
			if (pkgs[ch] == NULL) {
			    fprintf(stderr,
				  "malloc failed - abandoning package add.\n");
			    exit(1);
			}
		    }
		}
	    }
	}
	/* If no packages, yelp */
	if (!ch)
	    pwarnx("missing package name(s)"), usage();
	else if (ch > 1 && AddMode == MASTER)
	    pwarnx("only one package name may be specified with master mode"),
	    usage();
	else {
	    int fd;
	    char *dbdir;

	    /* create a test file to see if dbdir is writable.
	     * if the file already exists, O_EXCL does not touch it
	     * (possible security issue)
	     */
	    cp = toabs(".test", (dbdir = getenv(PKG_DBDIR)) ?
		    dbdir : DEF_LOG_DIR);
	    fd = open(cp, O_WRONLY|O_CREAT|O_EXCL, 0600);

	    if (fd == -1) {
		pwarn("the package database directory is not writable");
		pwarnx("the installation is likely to fail (%s)",
			Force ? "continuing anyway" : "aborting");
		if (!Force)
		    exit(1);
	    } else {
		unlink(cp);
		close(fd);
	    }
	}
    }
    if ((error = pkg_perform(pkgs)) != 0) {
	if (Verbose)
	    pwarnx("%d package addition(s) failed", error);
	return error;
    }
    else
	return 0;
}

static __dead void
usage(void)
{
    fprintf(stderr, "%s\n",
	"usage: pkg_add [-vInfRMS] [-d celm] [-t template] [-p prefix] pkg-name ...");
    exit(1);
}
