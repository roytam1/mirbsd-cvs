/* $MirOS: src/libexec/anoncvssh/anoncvssh.c,v 1.9 2008/06/07 20:25:43 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2006, 2008
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
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
 *-
 * user shell to be used for chrooted access (anonymous or personali-
 * sed, read-only or read-write) to cvs and possibly rsync.
 * This program requires ANSI C.
 */

/*
 * Copyright (c) 2002 Todd C. Miller <Todd.Miller@courtesan.com>
 * Copyright (c) 1997 Bob Beck <beck@obtuse.com>
 * Copyright (c) 1996 Thorsten Lockert <tholo@sigmasoft.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__)
#include <paths.h>
#endif
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

/*
 * You may need to change this path to ensure that RCS, CVS and diff
 * can be found
 */
#ifndef _PATH_DEFPATH
#define _PATH_DEFPATH	"/bin"
#endif

/*
 * This should not normally have to be changed
 */
#ifndef _PATH_BSHELL
#define _PATH_BSHELL	"/bin/sh"
#endif

/*
 * Location of CVS tree, relative to the anonymous CVS user's
 * home directory
 */
#ifndef LOCALROOT
#define LOCALROOT	"/cvs"
#endif

/*
 * Account and host name to be used when accessing the
 * CVS repository remotely
 */
#ifndef HOSTNAME
#if !defined(FQDN) || !defined(ANONCVS_USER)
#undef FQDN
#undef ANONCVS_USER
#define ANONCVS_USER	"_anoncvs"
#define FQDN		"mirbsd.org"
#endif
#define HOSTNAME	ANONCVS_USER "@" FQDN
#endif /* ndef HOSTNAME */

/*
 * This is our own program name
 */
#ifndef ANONCVSSH_NAME
#define ANONCVSSH_NAME	"anoncvssh"
#endif

/*
 * This is the rsync server to invoke
 */
#define FULL_RSYNC	"rsync --server "

/*
 * Niceness increase
 */
#ifndef NICE_INC
#define NICE_INC	5
#endif
#if NICE_INC < 0
#error "may not decrease niceness"
#endif


/****************************************************************/

static const char progID[] = "@(#) " HOSTNAME ":" LOCALROOT
    "\n@(#) $MirOS: src/libexec/anoncvssh/anoncvssh.c,v 1.9 2008/06/07 20:25:43 tg Exp $";

#ifdef USE_SYSLOG
#include <string.h>
#include <syslog.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define LOG_FACILITY	LOG_DAEMON
#define LOG_PRIO	LOG_INFO
#define DO_LOG(x, ...)	syslog(LOG_NOTICE, x, ## __VA_ARGS__)
#define DO_LOG0(x)	syslog(LOG_NOTICE, x)
#else /* def USE_SYSLOG */
#define DO_LOG(x, ...)	/* nothing */
#define DO_LOG0(x)	/* nothing */
#endif /* ! def USE_SYSLOG */

int main(int, char *[]);

const char * const env[] = {
	"PATH=" _PATH_DEFPATH,
	"SHELL=" _PATH_BSHELL,
	"CVSROOT=" LOCALROOT,
	"HOME=/",
#ifndef ACCESS_READWRITE
	"CVSREADONLYFS=1",
#endif
	NULL
};

#ifdef ANONUSERLIST
const char * const anonusers[] = {
#ifdef ANONCVS_USER
	ANONCVS_USER,
#endif
	ANONUSERLIST,
	NULL
};
#endif

int
main(int argc, char *argv[])
{
	struct passwd *pw;
	int niceness;
	char *chrootdir, *pgm;
#ifdef ANONUSERLIST
	const char * const *ccpp;
#endif
#ifdef CHROOT_PARENT_DIR
	char *s;
#endif
#ifdef DEBUG
	int i;
#endif

	pw = getpwuid(getuid());
	if (pw == NULL) {
		fprintf(stderr, "no user for uid %d\n", getuid());
		exit(1);
	}
	if (pw->pw_dir == NULL) {
		fprintf(stderr, "no home directory\n");
		exit(1);
	}

#ifdef USE_SYSLOG
	openlog(ANONCVSSH_NAME, LOG_PID | LOG_NDELAY, LOG_FACILITY);
#endif

	/* drop priority by NICE_INC; anoncvs is a background process */
	errno = 0;
	niceness = NICE_INC + getpriority(PRIO_PROCESS, 0);
	if ((niceness == (NICE_INC - 1)) && errno) {
		DO_LOG0("Can't get process priority!");
	} else if (setpriority(PRIO_PROCESS, 0, niceness)) {
		DO_LOG0("Can't set process priority!");
	}

#if defined(ANONCVS_USER) || defined(ANONUSERLIST)
	/*
	 * I love lusers who have to test every setuid binary on my machine.
	 */
	if (getuid() == 0)
		goto user_ok;

#ifdef ANONUSERLIST
	for (ccpp = anonusers; *ccpp; ++ccpp)
		if (!strcmp(pw->pw_name, *ccpp))
			goto user_ok;
#else
	if (!strcmp(pw->pw_name, ANONCVS_USER))
		goto user_ok;
#endif

	fprintf(stderr, "You're not supposed to be running me!\n");
#ifdef USE_SYSLOG
	syslog(LOG_NOTICE, "User %s(%d) invoked %s - Possible twink?",
	    pw->pw_name, pw->pw_uid, ANONCVSSH_NAME);
#endif /* def USE_SYSLOG */
	exit(1);

 user_ok:
#endif /* def ANONCVS_USER || def ANONUSERLIST */

	setuid(0);
	if ((chrootdir = strdup(pw->pw_dir)) == NULL) {
		perror("strdup");
		exit(1);
	}
#ifdef CHROOT_PARENT_DIR
	if ((s = strrchr(chrootdir, '/')) == NULL) {
		DO_LOG0("No slash in user's home directory!\n");
		exit(1);
	}
	*s = '\0';
	if (strrchr(chrootdir, '/') == NULL) {
		DO_LOG0("No slash in user's parent directory!\n");
		exit(1);
	}
#endif
	if (chroot(chrootdir) == -1) {
		perror("chroot");
		exit(1);
	}
	chdir("/");
	setuid(pw->pw_uid);
	free(chrootdir);

	/*
	 * program now "safe"
	 */


#ifdef ACCESS_PSERVER
	/* If we want pserver functionality (NOT! It's braindead!) */
	if ((argc == 2) && (strcmp("pserver", argv[1]) == 0)) {
#ifdef USE_SYSLOG
 	        int slen;
		struct sockaddr_in my_sa, peer_sa;
		char *us, *them;

		slen = sizeof(my_sa);
		if (getsockname(0, (struct sockaddr *) &my_sa, &slen) != 0) {
			perror("getsockname");
			exit(1);
		}
		us = strdup(inet_ntoa(my_sa.sin_addr));
		if (us == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		slen = sizeof(peer_sa);
		if (getpeername(0, (struct sockaddr *) &peer_sa, &slen) != 0) {
			perror("getpeername");
			exit(1);
		}
		them = strdup(inet_ntoa(peer_sa.sin_addr));
		if (them == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
	        syslog(LOG_PRIO,
		    "pserver connection from %s:%d to %s:%d\n",
		    them, ntohs(peer_sa.sin_port),
		    us, ntohs(my_sa.sin_port));
#endif /* def USE_SYSLOG */
		execle("/bin/cvs", "cvs",
		    "--allow-root=" LOCALROOT, "pserver", NULL, env);
		perror("execle: cvs");
		fprintf(stderr, "unable to exec CVS pserver!\n");
		exit(1);
		/* NOTREACHED */
	}
#endif /* def ACCESS_PSERVER */

	if ((argc == 3) && (!strcmp(ANONCVSSH_NAME, argv[0])) &&
	    (!strcmp("-c", argv[1]))) {
		pgm = argv[2];
		if (!strncmp("/usr/bin/", pgm, strlen("/usr/bin/")))
			pgm += strlen("/usr/bin/");
		if (!strncmp("/bin/", pgm, strlen("/bin/")))
			pgm += strlen("/bin/");
		if ((!strcmp("cvs server", pgm)) ||
		    (!strcmp("cvs -R server", pgm)) ||
		    (!strcmp("cvs -d " LOCALROOT " server", pgm))) {
			execle("/bin/cvs", "cvs", "server", NULL, env);
			perror("execle: cvs");
			DO_LOG0("chaining to CVS failed!");
			fprintf(stderr, "unable to exec CVS server!\n");
			exit(1);
			/* NOTREACHED */
		} else if (!strncmp(FULL_RSYNC, pgm, strlen(FULL_RSYNC))) {
#ifdef ACCESS_RSYNC
			int i = -1;
			char *newarg[256];
			char *p = pgm;

		lp:
			newarg[++i] = strsep(&p, " ");
			if ((newarg[i] != NULL) && (i < 255))
				goto lp;
#ifdef DEBUG
			argc = i;
			DO_LOG("calling rsync; argc = %d\n", argc);
			for (i = 0; i < argc; i++)
				DO_LOG("newarg[%d] = \"%s\"\n", i, newarg[i]);
#endif
			execve("/bin/rsync", newarg, (char **)env);
			perror("execve: rsync");
			DO_LOG0("chaining to rsync failed!");
			fprintf(stderr, "unable to exec RSYNC!\n");
			exit(1);
			/* NOTREACHED */
#else
			DO_LOG0("access to RSYNC prohibited!");
#endif
		}
	}

	DO_LOG0("parameter failure, printing help message");
	fprintf(stderr, "\n"
	    "To use anonymous CVS or RSYNC, install the latest version of the\n"
	    "client access software, as well as OpenSSH, on your computer.\n"
	    "Then, set your CVSROOT environment variable to the following\n"
	    "value for CVS access:\n\t%s:%s\n"
	    "For RSYNC, use SSH instead of RSH.\n",
	    HOSTNAME, LOCALROOT);
#ifdef DEBUG
	DO_LOG("argc = %d\n", argc);
	for (i = 0; i < argc; i++)
		DO_LOG("argv[%d] = \"%s\"\n", i, argv[i]);
#endif
	sleep(10);
	exit(0);
}
