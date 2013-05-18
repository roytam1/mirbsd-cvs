/**	$MirOS: ports/infrastructure/pkgtools/lib/exec.c,v 1.6 2008/10/12 14:35:17 tg Exp $ */
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
#include <fcntl.h>
#include <pwd.h>
#include "lib.h"
#include <sys/wait.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/exec.c,v 1.6 2008/10/12 14:35:17 tg Exp $");

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
 * Yet another way to run an external command *sigh*
 */
int
runcomm_(const char *whom, int nargs, const char * const *args,
    const char *outf)
{
	int i = 0;
	pid_t pid;

	if (Verbose) {
		fputs("Running \"", stdout);
		while (i < nargs)
			printf("%s ", args[i++]);
		if (outf)
			printf(">%s", outf);
		fputs("\"\n", stdout);
	}

	if ((pid = fork()) < 0)
		err(2, "failed to fork");
	else if (pid == 0) {
		union mksh_ccphack {
			char **rw;
			const char * const *ro;
		} argvec;

		if (outf) {
			int fd;

			if ((fd = open(outf, O_WRONLY | O_CREAT | O_TRUNC,
			    0666)) < 0) {
				warn("cannot open '%s' for writing", outf);
				return (-1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1) {
				warn("cannot dup2");
				return (-1);
			}
			if (fd != STDOUT_FILENO)
				/* do not care about errors here */
				close(fd);
		}
		/* stupid API */
		argvec.ro = args;
		execvp(whom, argvec.rw);
		warn("failed to execute %s command", whom);
		return (-1);
	}
	wait(&i);
	return (i);
}

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
	char buf[FILENAME_MAX]; /* XXX arbitrary size */

	if (!emul || !emul[0])
		return true;

	/* first: are we already running the right OS? */
	if (!strcasecmp(emul, piperead("uname -s"))) {
		if (Verbose)
			printf("- natively running %s\n", buf);
		return true;
	}

	/* On BSD: is the emulation enabled? */
	/* calling sysctl via popen encapsulates platform-specific stuff */
	snprintf(buf, sizeof(buf), "sysctl -n kern.emul.%s 2>/dev/null",
			emul);
	if (!strcmp("1", piperead(buf))) {
		if (Verbose)
			printf("- %s emulation enabled\n", emul);
		return true;
	}
	return false;
}
