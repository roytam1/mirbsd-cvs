/**	$MirOS: ports/infrastructure/pkgtools/add/futil.c,v 1.5 2008/11/02 18:19:51 tg Exp $ */
/*	$OpenBSD: futil.c,v 1.7 2003/07/04 17:31:19 avsm Exp $	*/

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
 * Miscellaneous file access utilities.
 */

#include <err.h>
#include "lib.h"
#include "add.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/add/futil.c,v 1.5 2008/11/02 18:19:51 tg Exp $");

/*
 * Assuming dir is a desired directory name, make it and all intervening
 * directories necessary.
 */

int
make_hierarchy(char *dir)
{
    char *cp1, *cp2;

    if (dir[0] == '/')
	cp1 = cp2 = dir + 1;
    else
	cp1 = cp2 = dir;
    while (cp2) {
	if ((cp2 = strchr(cp1, '/')) !=NULL )
	    *cp2 = '\0';
	if (fexists(dir)) {
	    if (!(isdir(dir) || islinktodir(dir)))
		return -1;
	}
	else {
	    if (xsystem(false, "mkdir %s", dir))
		return -1;
	    apply_perms(NULL, dir);
	}
	/* Put it back */
	if (cp2) {
	    *cp2 = '/';
	    cp1 = cp2 + 1;
	}
    }
    return 0;
}

/* Using permission defaults, apply them as necessary */
void
apply_perms(const char *dir, char *arg)
{
    const char *cd_to;

    if (!dir || *arg == '/')	/* absolute path? */
	cd_to = "/";
    else
	cd_to = dir;

#ifndef __INTERIX
    if (Owner || Group) {
	const char *real_owner = Owner ? Owner : "";
	const char *real_group = Group ? Group : "";

	if (xsystem(false, "cd %s && chown -R %s:%s %s", cd_to, real_owner ,
		real_group, arg))
	    pwarnx("couldn't change owner/group of '%s' to '%s:%s'",
		   arg, real_owner, real_group);
    }
#endif
    if (Mode) {
	if (xsystem(false, "cd %s && chmod -R %s %s", cd_to, Mode, arg))
	    pwarnx("couldn't change modes of '%s' to '%s'", arg, Mode);
#ifdef AS_USER
	if (xsystem(false, "cd %s && chmod -R a-st %s", cd_to, arg))
	    pwarnx("SECURITY WARNING: could not reset sugid/itxt bits on '%s'", arg);
#endif
    }
}
