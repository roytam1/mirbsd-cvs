/*	$OpenBSD: reboot.c,v 1.26 2004/07/09 18:49:57 deraadt Exp $	*/
/*	$NetBSD: reboot.c,v 1.8 1995/10/05 05:36:22 mycroft Exp $	*/

/*
 * Copyright (c) 2011, 2014
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/reboot.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <dev/rndioctl.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <termios.h>
#include <syslog.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include "pathnames.h"

__COPYRIGHT("@(#) Copyright (c) 1980, 1986, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
__SCCSID("@(#)reboot.c	8.1 (Berkeley) 6/5/93");
__RCSID("$MirOS: src/sbin/reboot/reboot.c,v 1.6 2014/03/12 23:16:52 tg Exp $");

extern const char *__progname;
extern void arc4random_atexit(void);

static void
pull_console(bool do_setsid)
{
	int fd;
	struct termios t;

	if (revoke(_PATH_CONSOLE) == -1)
		warn("revoke");
	if (do_setsid) {
		if (setsid() == -1)
			warn("setsid");
	}
	fd = open(_PATH_CONSOLE, O_RDWR);
	if (fd == -1)
		warn("open");
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	/* At a minimum... */
	tcgetattr(0, &t);
	t.c_oflag |= (ONLCR | OPOST);
	tcsetattr(0, TCSANOW, &t);
}

int
main(int argc, char *argv[])
{
	int i, ch, howto, rnd_fd, arnd_fd;
	struct passwd *pw;
	bool dohalt, lflag, nflag, pflag, qflag;
	const char *p, *user;
	char rnd_buf[512];
	static const int death_sigs[7] = {
		SIGHUP, SIGTERM, SIGKILL, SIGKILL, SIGKILL, SIGKILL, SIGKILL
	};

	if (chdir("/"))
		warn("chdir(\"/\")");

	p = __progname;

	/* Nuke login shell */
	if (*p == '-')
		p++;

	howto = 0;
	dohalt = lflag = nflag = pflag = qflag = false;
	if (!strcmp(p, "halt")) {
		dohalt = true;
		howto = RB_HALT;
	}

	while ((ch = getopt(argc, argv, "dlnpq")) != -1)
		switch (ch) {
		case 'd':
			howto |= RB_DUMP;
			break;
		case 'l':	/* Undocumented; used by shutdown. */
			lflag = true;
			break;
		case 'n':
			nflag = true;
			howto |= RB_NOSYNC;
			break;
		case 'p':
			/* Only works if we're called as halt. */
			if (dohalt) {
				pflag = true;
				howto |= RB_POWERDOWN;
			}
			break;
		case 'q':
			qflag = true;
			break;
		default:
			goto usage;
		}
	argc -= optind;
	argv += optind;

	if (argc)
		goto usage;

	if (geteuid())
		errx(1, "%s", strerror(EPERM));

	if (qflag) {
		reboot(howto);
		err(1, "reboot");
	}

	/* Log the reboot. */
	if (!lflag)  {
		if ((user = getlogin()) == NULL)
			user = (pw = getpwuid(getuid())) ?
			    pw->pw_name : "???";
		if (dohalt) {
			openlog("halt", 0, LOG_AUTH | LOG_CONS);
			if (pflag) {
				syslog(LOG_CRIT,
					"halted (with powerdown) by %s", user);
			} else {
				syslog(LOG_CRIT, "halted by %s", user);
			}
		} else {
			openlog("reboot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "rebooted by %s", user);
		}
	}
	logwtmp("~", "shutdown", "");

	/*
	 * Do a sync early on, so disks start transfers while we're off
	 * killing processes.  Don't worry about writes done before the
	 * processes die, the reboot system call syncs the disks.
	 */
	if (!nflag)
		sync();

	/* Just stop init -- if we fail, we'll restart it. */
	if (kill(1, SIGTSTP) == -1)
		err(1, "SIGTSTP init");

	/* Ignore the SIGHUP we get when our parent shell dies. */
	(void)signal(SIGHUP, SIG_IGN);

	/*
	 * If we're running in a pipeline, we don't want to die
	 * after killing whatever we're writing to.
	 */
	(void)signal(SIGPIPE, SIG_IGN);

	if (access(_PATH_RUNCOM, R_OK) != -1) {
		pid_t pid;

		switch ((pid = fork())) {
		case -1:
			break;
		case 0:
			pull_console(true);
			execl(_PATH_BSHELL, "sh", "-p", _PATH_RUNCOM, "shutdown", (char *)NULL);
			_exit(1);
		default:
			waitpid(pid, NULL, 0);
		}
	}

	pull_console(false);
	arnd_fd = open(_PATH_ARANDOMDEV, O_RDWR);
	rnd_fd = open(_PATH_HOSTRANDOM, O_WRONLY | O_APPEND | O_SYNC);

	for (i = 0; i < 7; ++i) {
		warnx("Sending SIG%s to all processes...",
		    sys_signame[death_sigs[i]]);

		if (kill(-1, death_sigs[i]) == -1) {
			if (errno != ESRCH) {
				warn("signalling processes");
				goto restart;
			}
			if (i > 1)
				/* terminate loop after SIGKILL */
				i = 10;
		}

		if (i == 0) {
			sleep(2);
			if (!nflag)
				sync();
		} else if (i == 1) {
			sleep(3);
		} else if (i == 10) {
			sleep(1);
		} else {
			sleep(2 * (i - 2));
		}

		if (arnd_fd != -1)
			/* reset lopool, arandom */
			ioctl(arnd_fd, RNDSTIRARC4);
		if (rnd_fd != -1) {
			if (arnd_fd != -1)
				read(arnd_fd, rnd_buf, sizeof(rnd_buf));
			else
				arc4random_buf(rnd_buf, sizeof(rnd_buf));
			write(rnd_fd, rnd_buf, sizeof(rnd_buf));
		}
	}

	if (i == 7)
		warnx("WARNING: some process(es) wouldn't die");

	if (rnd_fd != -1)
		close(rnd_fd);
	arc4random_atexit();
	if (arnd_fd != -1) {
		ioctl(arnd_fd, RNDSTIRARC4);
		close(arnd_fd);
	}

	reboot(howto);
	/* FALLTHROUGH */

 restart:
	errx(1, kill(1, SIGHUP) == -1 ? "(can't restart init): " : "");
	/* NOTREACHED */

 usage:
	fprintf(stderr, "usage: %s [-dn%sq]\n", __progname,
	    dohalt ? "p" : "");
	return (1);
}
