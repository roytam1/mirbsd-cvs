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

#include <stdio.h>
#include <stdlib.h>
#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__)
#include <paths.h>
#endif
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef __CONCAT
#if defined(__STDC__) || defined(__cplusplus)
#define __CONCAT(x,y)		x ## y
#else
#define __CONCAT(x,y)		x/**/y
#endif
#endif

#ifndef __CONCAT3
#if defined(__STDC__) || defined(__cplusplus)
#define __CONCAT3(x,y,z)	x ## y ## z
#else
#define __CONCAT3(x,y,z)	x/**/y/**/z
#endif
#endif

#ifndef __P
#if defined(__STDC__) || defined(__cplusplus)
#define	__P(protos)	protos		/* full-blown ANSI C */
#else
#define	__P(protos)	()		/* traditional C preprocessor */
#endif
#endif

/*
 * You may need to change this path to ensure that RCS, CVS and diff
 * can be found
 */
#ifndef _PATH_DEFPATH
#define	_PATH_DEFPATH	"/bin:/usr/bin"
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
#define	LOCALROOT	"/cvs"
#endif

/*
 * Account and host name to be used when accessing the
 * CVS repository remotely
 */
#ifndef HOSTNAME
#define	HOSTNAME	"anoncvs@anoncvs1.usa.openbsd.org"
#endif

/*
 * $CVSROOT is created based on HOSTNAME and LOCALROOT above
 */
#ifndef CVSROOT
#define	CVSROOT		__CONCAT3(HOSTNAME,":",LOCALROOT)
#endif

/*
 * We define PSERVER_SUPPORT to allow anoncvssh to spawn a "cvs pserver".
 * You may undefine this if you aren't going to be running pserver.
 */
#ifndef PSERVER_SUPPORT
#define PSERVER_SUPPORT
#endif

/*
 * Define USE_SYSLOG if you want anoncvssh to log pserver connections 
 * using syslog()
 */
#define USE_SYSLOG

#ifdef USE_SYSLOG
#include <string.h>
#include <syslog.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define LOG_FACILITY LOG_DAEMON
#define LOG_PRIO LOG_INFO
#endif

/* Define ANONCVS_USER if you want anoncvssh to complain if invoked by
 * anyone other than root or ANONCVS_USER.
 */
/* #define ANONCVS_USER "anoncvs" */

int main __P((int, char *[]));

char * const env[] = {
	__CONCAT("PATH=",_PATH_DEFPATH),
	__CONCAT("SHELL=",_PATH_BSHELL),
	__CONCAT("CVSROOT=",LOCALROOT),
	"HOME=/",
	"CVSREADONLYFS=1",
	NULL
};

int
main(argc, argv)
int argc;
char *argv[];
{
	struct passwd *pw;
#ifdef DEBUG
	int i;
#endif /* DEBUG */

	pw = getpwuid(getuid());
	if (pw == NULL) {
		fprintf(stderr, "no user for uid %d\n", getuid());
		exit(1);
	}
	if (pw->pw_dir == NULL) {
		fprintf(stderr, "no directory\n");
		exit(1);
	}

#ifdef USE_SYSLOG
	openlog("anoncvssh", LOG_PID | LOG_NDELAY, LOG_FACILITY);
#endif /* USE_SYSLOG */
	
#ifdef ANONCVS_USER
	/* 
	 * I love lusers who have to test every setuid binary on my machine.
	 */
	if (getuid() != 0 && (strcmp (pw->pw_name, ANONCVS_USER) != 0)) {
		fprintf(stderr, "You're not supposed to be running me!\n"); 
#ifdef USE_SYSLOG
		syslog(LOG_NOTICE,
		       "User %s(%d) invoked anoncvssh - Possible twink?",
		       pw->pw_name, pw->pw_uid); 
#endif /* USE_SYSLOG */
		exit(1);
	}
#endif /* ANONCVS_USER */


	setuid(0);
	if (chroot(pw->pw_dir) == -1) {
		perror("chroot");
		exit (1);
	}
	chdir("/");
	setuid(pw->pw_uid);

	/*
	 * program now "safe"
	 */

#ifdef PSERVER_SUPPORT
	/* If we want pserver functionality */
	if ((argc == 2) && (strcmp("pserver", argv[1]) == 0)) {
#ifdef USE_SYSLOG
 	        int slen;
		struct sockaddr_in my_sa, peer_sa;
		char *us, *them;
		
		slen = sizeof(my_sa);
		if (getsockname(0, (struct sockaddr *) &my_sa, &slen)
		    != 0) {
		  perror("getsockname");
		  exit(1);
		}
		us = strdup(inet_ntoa(my_sa.sin_addr));
		if (us == NULL) {
		  fprintf(stderr, "malloc failed\n");
		  exit(1);
		}
		slen = sizeof(peer_sa);
		if (getpeername(0, (struct sockaddr *) &peer_sa, &slen)
		    != 0) {
		  perror("getpeername");
		  exit(1);
		}
		them=strdup(inet_ntoa(peer_sa.sin_addr));
		if (them == NULL) {
		  fprintf(stderr, "malloc failed\n");
		  exit(1);
		}
	        syslog(LOG_PRIO, 
		       "pserver connection from %s:%d to %s:%d\n",
		       them, ntohs(peer_sa.sin_port),
		       us, ntohs(my_sa.sin_port));
#endif /* USE_SYSLOG */
		execle("/usr/bin/cvs", "cvs",
		    __CONCAT("--allow-root=",LOCALROOT), "pserver", (char *)NULL, env);
		perror("execle: cvs");
		fprintf(stderr, "unable to exec CVS pserver!\n");
		exit(1);
		/* NOTREACHED */
	}
#endif

	if (argc != 3 || 
		strcmp("anoncvssh",  argv[0]) != 0 ||
		strcmp("-c",         argv[1]) != 0 ||
		(strcmp("cvs server", argv[2]) != 0 &&
		 strcmp(__CONCAT3("cvs -d ",LOCALROOT," server"), argv[2]) != 0)) {
		fprintf(stderr, "\nTo use anonymous CVS install the latest ");
		fprintf(stderr,"version of CVS on your local machine.\n");
		fprintf(stderr,"Then set your CVSROOT environment variable ");
		fprintf(stderr,"to the following value:\n");
		fprintf(stderr,"\t%s\n\n", CVSROOT);
#ifdef DEBUG
		fprintf(stderr, "argc = %d\n", argc);
		for (i = 0 ; i < argc ; i++)
			fprintf(stderr, "argv[%d] = \"%s\"\n", i, argv[i]);
#endif /* DEBUG */
		sleep(10);
		exit(0);
	}
	execle("/usr/bin/cvs", "cvs", "server", (char *)NULL, env);
	perror("execle: cvs");
	fprintf(stderr, "unable to exec CVS server!\n");
	exit(1);
	/* NOTREACHED */
}

