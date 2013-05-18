/*-
 * Copyright (c) 2008
 *	Thorsten Glaser <tg@mirbsd.org>
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

#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <err.h>
#include <signal.h>
#include <stddef.h>
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/proc.c,v 1.1 2008/11/02 18:56:30 tg Exp $");

extern char **environ;

static size_t argmax;

/* helper macro for string operations */
#define STORE(c) do {					\
	if ((size_t)(cp - buf) >= bufsz) {		\
		ptrdiff_t pos = (cp - buf);		\
		buf = xrealloc(buf, 1, bufsz <<= 1);	\
		cp = buf + pos;				\
	}						\
	*cp++ = (c);					\
} while (/* CONSTCOND */ 0)

/* escape a string for passing to the shell */
char *
format_arg(const char *s)
{
	char *buf, *cp;
	bool inescape;
	size_t bufsz;
	char c;

	if (s == NULL)
		errx(1, "format_arg: NULL pointer given");

	cp = buf = xcalloc(1, bufsz = 128);
	inescape = false;
	while ((c = *s++)) {
		if (c == '\'') {
			if (inescape) {
				STORE('\'');
				inescape = false;
			}
			STORE('\\');
			STORE('\'');
		} else {
			if (!inescape) {
				STORE('\'');
				inescape = true;
			}
			STORE(c);
		}
	}
	if (inescape)
		STORE('\'');
	STORE('\0');
	return (xrealloc(buf, 1, cp - buf));
}

/* prepare a command for being run by the shell */
char *
format_comm_(const char * const *args)
{
	char *rv, *cp;
	size_t argptr = 1, ssz, asz;

	rv = xstrdup(args[0]);
	while (args[argptr] != NULL) {
		ssz = strlen(rv);
		asz = strlen(cp = format_arg(args[argptr++]));
		rv = xrealloc(rv, 1, ssz + 1 + asz + 1);
		rv[ssz] = ' ';
		memcpy(rv + ssz + 1, cp, asz + 1);
		xfree(cp);
	}
	return (rv);
}

/* unlimit datasize, with help from mksh */
void
unlimit(void)
{
	struct rlimit limit;

	if (getrlimit(RLIMIT_DATA, &limit) < 0) {
		/* some cannot be read, e.g. Linux RLIMIT_LOCKS */
		limit.rlim_cur = RLIM_INFINITY;
		limit.rlim_max = RLIM_INFINITY;
	}

	limit.rlim_cur = limit.rlim_max;
	setrlimit(RLIMIT_DATA, &limit);
}

/* run an mksh command, optionally unlimit datasize, with help from libc */
int
mirsystem(const char *cmd, bool flag_unlimit)
{
	pid_t pid;
	sig_t intsave, quitsave;
	sigset_t mask, omask;
	int pstat;

	if (cmd == NULL)
		return (-1);

	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &mask, &omask);
	switch (pid = vfork()) {
	case -1:
		sigprocmask(SIG_SETMASK, &omask, NULL);
		return (-1);
	case 0: {
		union {
			char *rw[5];
			const char *ro[5];
		} argp;

		argp.ro[0] = "env";
		argp.ro[1] = "mksh";
		argp.ro[2] = "-c";
		argp.ro[3] = cmd;
		argp.ro[4] = NULL;

		if (flag_unlimit)
			unlimit();

		sigprocmask(SIG_SETMASK, &omask, NULL);
		execve("/usr/bin/env", argp.rw, environ);
		_exit(127);
	    }
	}

	intsave = signal(SIGINT, SIG_IGN);
	quitsave = signal(SIGQUIT, SIG_IGN);
	pid = waitpid(pid, &pstat, 0);
	sigprocmask(SIG_SETMASK, &omask, NULL);
	signal(SIGINT, intsave);
	signal(SIGQUIT, quitsave);
	return (pid == -1 ? -1 : pstat);
}

/* run a shell command, optionally unlimit datasize first */
int
xsystem(bool flag_unlimit, const char *fmt, ...)
{
	va_list ap;
	int rv;

	va_start(ap, fmt);
	rv = vxsystem(flag_unlimit, fmt, ap);
	va_end(ap);

	return (rv);
}

int
vxsystem(bool flag_unlimit, const char *fmt, va_list ap)
{
	char *cmd;
	int rv;

	xvasprintf(&cmd, fmt, ap);
	rv = sxsystem(flag_unlimit, cmd);
	xfree(cmd);
	return (rv);
}

int
sxsystem(bool flag_unlimit, const char *cmd)
{
	if (cmd == NULL)
		errx(1, "sxsystem: NULL pointer given");

	if (argmax == 0) {
		if ((argmax = sysconf(_SC_ARG_MAX)) == (size_t)-1) {
			warn("cannot retrieve maximum argument size");
			argmax = 262144;
		}
		argmax -= 32;		/* some space for sh -c */
	}

	if (strlen(cmd) > argmax)
		errx(1, "vxsystem arguments too big: %s", cmd);

#ifdef DEBUG
	fprintf(stderr, "Executing 「%s」\n", cmd);
	fflush(stderr);
#endif
	return (mirsystem(cmd, flag_unlimit));
}
