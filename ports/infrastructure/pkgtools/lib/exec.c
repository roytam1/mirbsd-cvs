/*-
 * Copyright (c) 2006, 2007
 *	Benny Siegert <bsiegert@mirbsd.org>
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
 */

#include <err.h>
#include <fcntl.h>
#include <pwd.h>
#include "lib.h"
#include <sys/wait.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/exec.c,v 1.11 2008/11/02 19:28:43 tg Exp $");

#ifdef AS_USER
static bool PrivsDropped = false;
#endif

/*
 * Execute the command, read one line of output, and return it as a
 * pointer to a static internal buffer. Read errors, eof, and exit
 * status are ignored.
 */
char *
piperead(const char *command)
{
	static char buf[FILENAME_MAX]; /* XXX arbitrary size */
	int len;
	FILE *stream;

	stream = popen(command, "r");
	buf[0] = '\0';
	(void)fgets(buf, sizeof(buf), stream);
	if (ferror(stream)) {
		pwarn("Failed to read output from command '%s'", command);
		/* buffer contents are indeterminate if an error occurred */
		buf[0] = '\0';
	}
	len = strlen(buf);
	if (len > 0 && buf[len - 1] == '\n')
		buf[--len] = '\0';
	if (pclose(stream) == -1) {
		pwarn("Failed to close pipe to '%s'", command);
	}
	return buf;
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

/*
 * Determine whether the system has the given binary emulation layer.
 * In case of an error, return false.
 */
bool
have_emulation(char *emul)
{
	char *buf;
	bool rv = false;

	if (!emul || !emul[0])
		return true;

	/* first: are we already running the right OS? */
	if (!strcasecmp(emul, piperead("uname -s"))) {
		if (Verbose)
			printf("- natively running %s\n", emul);
		return true;
	}

	/* On BSD: is the emulation enabled? */
	/* calling sysctl via popen encapsulates platform-specific stuff */
	xasprintf(&buf, "sysctl -n kern.emul.%s 2>/dev/null", emul);
	if (!strcmp("1", piperead(buf))) {
		if (Verbose)
			printf("- %s emulation enabled\n", emul);
		rv = true;
	}
	xfree(buf);
	return (rv);
}
