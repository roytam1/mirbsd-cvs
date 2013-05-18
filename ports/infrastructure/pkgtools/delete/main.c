/**	$MirOS: ports/infrastructure/pkgtools/delete/main.c,v 1.6 2007/01/19 23:11:19 bsiegert Exp $ */
/*	$OpenBSD: main.c,v 1.12 2003/08/21 20:24:56 espie Exp $	*/

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
 * This is the delete module.
 */

#include <err.h>
#include "lib.h"
#include "delete.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/delete/main.c,v 1.6 2007/01/19 23:11:19 bsiegert Exp $");

static char Options[] = "CcDdFfhnp:qUv";

char	*Prefix		= NULL;
bool	NoDeInstall	= false;
bool	CleanDirs	= false;
rm_cfg_t CleanConf	= RMCFG_NONE;
bool	CheckMD5	= true;
bool	KeepFiles	= false;
bool	ForceUser	= false;

static __dead void usage(void);

int
main(int argc, char **argv)
{
    int ch, error;
    char **pkgs, **start;

    pkgs = start = argv;
    while ((ch = getopt(argc, argv, Options)) != -1)
	switch(ch) {
	case 'v':
	    Verbose = true;
	    break;

	case 'F':
	    ForceUser = true;
	    break;

	case 'f':
	    Force = true;
	    break;

	case 'p':
	    Prefix = optarg;
	    break;

	case 'D':
	    NoDeInstall = true;
	    break;

	case 'd':
	    CleanDirs = true;
	    break;

	case 'n':
	    Fake = true;
	    Verbose = true;
	    break;

	case 'q':
	    CheckMD5 = false;
	    break;

	case 'C':
	    CleanConf = RMCFG_UNCHANGED;
	    break;

	case 'c':
	    CleanConf = RMCFG_ALL;
	    break;

	case 'U':
	    KeepFiles = true;
	    break;

	case 'h':
	case '?':
	default:
	    usage();
	    break;
	}

    argc -= optind;
    argv += optind;

    /* Get all the remaining package names, if any */
    /* Get all the remaining package names, if any */
    while (*argv)
	*pkgs++ = *argv++;

    /* If no packages, yelp */
    if (pkgs == start)
	pwarnx("missing package name(s)"), usage();
    *pkgs = NULL;
#ifndef AS_USER
    if (!Fake && getuid() != 0) {
	if (ForceUser)
	    pwarnx("packages must be deleted as root -- trying anyway");
	else 
	    errx(1, "you must be root to delete packages");
    }
#endif
    if ((error = pkg_perform(start)) != 0) {
	if (Verbose)
	    pwarnx("%d package deletion(s) failed", error);
	return error;
    }
    else
	return 0;
}

static __dead void
usage(void)
{
    fprintf(stderr, "usage: pkg_delete [-CcvDdhnfq] [-p prefix] pkg-name ...\n");
    exit(1);
}
