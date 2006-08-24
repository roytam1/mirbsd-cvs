/**	$MirOS: ports/infrastructure/pkgtools/lib/exec.c,v 1.2 2006/02/25 15:49:55 bsiegert Exp $ */
/*	$OpenBSD: exec.c,v 1.8 2003/09/05 19:40:42 tedu Exp $	*/

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
 * Miscellaneous system routines.
 */

#include <err.h>
#include <pwd.h>
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/exec.c,v 1.2 2006/02/25 15:49:55 bsiegert Exp $");

#ifdef AS_USER
static bool PrivsDropped = false;
#endif

/*
 * Unusual system() substitute.  Accepts format string and args,
 * builds and executes command.  Returns exit code.
 */

int
vsystem(const char *fmt, ...)
{
	va_list	args;
	char	*cmd;
	ssize_t	maxargs;
	int	ret;

	if ((maxargs = sysconf(_SC_ARG_MAX)) == -1) {
		pwarnx("vsystem can't retrieve max args");
		return 1;
	}
	maxargs -= 32;			/* some slop for the sh -c */
	if ((cmd = (char *) malloc((size_t)maxargs)) == NULL) {
		pwarnx("vsystem can't alloc arg space");
		return 1;
	}

	va_start(args, fmt);
	if (vsnprintf(cmd, (size_t)maxargs, fmt, args) >= maxargs) {
		pwarnx("vsystem args are too long");
		free(cmd);
		return 1;
	}
#ifdef DEBUG
	printf("Executing %s\n", cmd);
#endif
	ret = system(cmd);
	va_end(args);
	free(cmd);
	return ret;
}

/*
 * If run under sudo, this drops privileges to those of the user calling
 * sudo.
 */

void
drop_privs(void)
{
#ifdef AS_USER
	char *login = getlogin();
	struct passwd *pwent;

	if (!geteuid() && strcmp(login, "root")) {
		pwent = getpwnam(login);
		if (!pwent) {
			pwarnx("drop_privs: Cannot get passwd entry for user %s\n", login);
			return;
		}
		if (Verbose)
			printf("Dropping privileges to %s (uid %d)\n",
					login, pwent->pw_uid);
		seteuid(pwent->pw_uid);
		PrivsDropped = true;
	}
#endif
}

/*
 * Raise privileges after they have been dropped.
 */

void
raise_privs(void)
{
#ifdef AS_USER
	if (PrivsDropped) {
		seteuid(0);
		PrivsDropped = false;
		if (Verbose)
			printf("Raising privileges to root\n");
	} else if (Verbose)
		pwarnx("raise_privs: incorrect attempt to raise privs\n");
#endif
}
