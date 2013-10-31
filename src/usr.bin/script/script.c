/*	$OpenBSD: script.c,v 1.24 2005/12/12 20:10:53 deraadt Exp $	*/
/*	$NetBSD: script.c,v 1.3 1994/12/21 08:55:43 jtc Exp $	*/

/*-
 * Copyright © 2007, 2008, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
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

/*
 * Copyright (c) 2001 Theo de Raadt
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 1980, 1992, 1993
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

#include <sys/param.h>
__COPYRIGHT("@(#) Copyright (c) 1980, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n");
__SCCSID("@(#)script.c	8.1 (Berkeley) 6/6/93");
__RCSID("$MirOS: src/usr.bin/script/script.c,v 1.14 2008/02/24 15:16:10 tg Exp $");

#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#ifndef NO_CONV
#include <wchar.h>
#endif

#include <util.h>
#include <err.h>

FILE *fscript;
int master, slave;
volatile sig_atomic_t child;
pid_t subchild;
const char *fname;
bool do_loginshell = false;
const char *shcmd = NULL;

#ifndef NO_CONV
bool l1mode = false;
bool lumode = false;
const char *l1rep = "?";
size_t l1rlen = 1;
#else
#define l1mode	0
#define lumode	0
#endif

volatile sig_atomic_t dead;
volatile sig_atomic_t sigdeadstatus;
volatile sig_atomic_t flush;

struct termios tt;

void done(int) __attribute__((__noreturn__));
void dooutput(void) __attribute__((__noreturn__));
void doinput(void) __attribute__((__noreturn__));
void doshell(void) __attribute__((__noreturn__));
void fail(void) __attribute__((__noreturn__));
void finish(int);
void scriptflush(int);
void handlesigwinch(int);
void usage(void) __attribute__((__noreturn__));

#ifdef SMALL
#undef DEBUG
#else
bool qflg = false;
#endif

#ifdef DEBUG
#define dump(buf, len)	__dump(#buf, __func__, buf, len)
static void __dump(const char *, const char *, const uint8_t *, size_t);
#else
#define dump(buf, len)	/* nothing */
#endif

int
main(int argc, char *argv[])
{
	struct sigaction sa;
	struct termios rtt;
	struct winsize win;
	int aflg, nflg, ch;

#ifndef NO_CONV
#if !defined(MirBSD) || (MirBSD < 0x09AB)
#if 0
	extern bool __locale_is_utf8;
	__locale_is_utf8 = true;
#else
#error Need at least MirOS #9uAB locale support!
#endif
#endif
#endif

	aflg = nflg = 0;
	while ((ch = getopt(argc, argv, "ac:L:lnqsU:u")) != -1)
		switch(ch) {
		case 'a':
			aflg = 1;
			break;
		case 'c':
			shcmd = optarg;
			break;
#ifndef NO_CONV
		case 'L':
			l1rep = optarg;
			l1rlen = strlen(l1rep);
			/* FALLTHRU */
		case 'l':
			l1mode = true;
			lumode = false;
			break;
#endif
		case 'n':
			nflg = 1;
			break;
		case 'q':
#ifndef SMALL
			qflg = true;
#endif
			break;
		case 's':
			do_loginshell = true;
			break;
#ifndef NO_CONV
		case 'U':
			l1rep = optarg;
			l1rlen = strlen(l1rep);
			/* FALLTHRU */
		case 'u':
			lumode = true;
			l1mode = false;
			break;
#endif
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (nflg) {
		if (argc > 0)
			usage();
		fscript = NULL;
		fname = "";
	} else {
		if (argc > 0)
			fname = argv[0];
		else
			fname = "typescript";

		if ((fscript = fopen(fname, aflg ? "a" : "w")) == NULL)
			err(1, "%s", fname);
	}

	tcgetattr(STDIN_FILENO, &tt);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	if (openpty(&master, &slave, NULL, &tt, &win) == -1)
		err(1, "openpty");

#ifndef SMALL
	if (!qflg)
		printf("Script started, %s%s%s\n",
#ifndef NO_CONV
		    l1mode ? "latin1 mode, " : lumode ? "luit mode, " :
#endif
		    "", fscript ? "output file is " : "no output file", fname);
#endif
	rtt = tt;
	cfmakeraw(&rtt);
	rtt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rtt);

	bzero(&sa, sizeof sa);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = finish;
	sigaction(SIGCHLD, &sa, NULL);

	sa.sa_handler = handlesigwinch;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGWINCH, &sa, NULL);

	child = fork();
	if (child < 0) {
		warn("fork");
		fail();
	}
	if (child == 0) {
		subchild = child = fork();
		if (child < 0) {
			warn("fork");
			fail();
		}
		if (child)
			dooutput();
		else
			doshell();
		/* NOTREACHED */
	}
	doinput();
	/* NOTREACHED */
}

void
doinput(void)
{
	ssize_t cc, off;
	unsigned char ibuf[BUFSIZ];
	unsigned char *ubuf = NULL;
#ifndef NO_CONV
	unsigned char cbuf[BUFSIZ * 2];
	mbstate_t state = { 0, 0 };
#else
	unsigned char *cbuf = NULL;	/* to quieten gcc */
#endif

#ifndef NO_CONV
	if (lumode) {
		/* this formula works because wcwidth(U+0000..U+00FF)<2 */
		cc = l1rlen < 1 ? 1 : l1rlen;
		if ((ubuf = calloc(BUFSIZ, cc)) == NULL)
			err(1, "cannot allocate %zd*%zd bytes for"
			    " conversion buffer", cc, (ssize_t)BUFSIZ);
	}
#endif
	if (fscript)
		fclose(fscript);
	for (;;) {
		if (dead)
			break;
		cc = read(STDIN_FILENO, ibuf, BUFSIZ);
		if (cc == -1 && errno == EINTR)
			continue;
		if (cc <= 0)
			break;
#ifndef NO_CONV
		if (l1mode) {
			unsigned char *cp = cbuf;

			for (off = 0; off < cc; ++off)
				cp += wcrtomb((char *)cp, ibuf[off], &state);
			dump(ibuf, cc);
			cc = cp - cbuf;
			dump(cbuf, cc);
		} else if (lumode) {
			unsigned char *cp = ibuf;
			unsigned char *lp = ubuf;
			size_t n;
			wchar_t wc;

			off = cc;
			dump(ibuf, cc);
			while (off) {
				n = mbrtowc(&wc, (char *)cp, off, &state);

				if (n == 0) {
					n = 1;
					wc = 0;
				} else if (n == (size_t)-1) {
					n = 1;
					wc = 0xFFFD;
					state.count = 0;
				} else if (n == (size_t)-2)
					break;
				off -= n;
				cp += n;
				if (wc < 0x0100)
					*lp++ = wc;
				else for (cc = 0; cc < wcwidth(wc); ++cc) {
					/* what about wcwidth==(-1) C0/C1? */
					memcpy(lp, l1rep, l1rlen);
					lp += l1rlen;
				}
			}
			cc = lp - ubuf;
			dump(ubuf, cc);
		}
#endif
		for (off = 0; off < cc; ) {
			ssize_t n = write(master,
			    (l1mode ? cbuf : lumode ? ubuf : ibuf) + off,
			    cc - off);
			if (n == -1 && errno != EAGAIN)
				break;
			if (n == 0)
				break;	/* skip writing */
			if (n > 0)
				off += n;
		}
	}
#ifndef NO_CONV
	if (lumode && state.count)
		/* incomplete multibyte char on exit */
		write(master, l1rep, l1rlen);
#endif
	done(sigdeadstatus);
}

/* ARGSUSED */
void
finish(int signo __attribute__((__unused__)))
{
	int save_errno = errno;
	int status, e = 1;
	pid_t pid;

	while ((pid = wait3(&status, WNOHANG, 0)) > 0) {
		if (pid == (pid_t)child) {
			if (WIFEXITED(status))
				e = WEXITSTATUS(status);
		}
	}
	dead = 1;
	sigdeadstatus = e;
	errno = save_errno;
}

/* ARGSUSED */
void
handlesigwinch(int signo __attribute__((__unused__)))
{
	int save_errno = errno;
	struct winsize win;
	pid_t pgrp;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) != -1) {
		ioctl(slave, TIOCSWINSZ, &win);
		if (ioctl(slave, TIOCGPGRP, &pgrp) != -1)
			killpg(pgrp, SIGWINCH);
	}
	errno = save_errno;
}

void
dooutput(void)
{
	struct sigaction sa;
	struct itimerval value;
	sigset_t blkalrm;
	unsigned char obuf[BUFSIZ];
	unsigned char *cbuf = NULL;
#ifndef SMALL
	time_t tvec;
#endif
#ifndef NO_CONV
	unsigned char ubuf[BUFSIZ * 2];
	mbstate_t state = { 0, 0 };
#else
	unsigned char *ubuf = NULL;	/* to quieten gcc */
#endif
	ssize_t outcc = 0, cc, fcc, off;

#ifndef NO_CONV
	if (l1mode) {
		/* this formula works because wcwidth(U+0000..U+00FF)<2 */
		cc = l1rlen < 1 ? 1 : l1rlen;
		if ((cbuf = calloc(BUFSIZ, cc)) == NULL)
			err(1, "cannot allocate %zd*%zd bytes for"
			    " conversion buffer", cc, (ssize_t)BUFSIZ);
	}
#endif
	close(STDIN_FILENO);
	close(slave);
	if (fscript) {
#ifndef SMALL
		tvec = time(NULL);
		if (!qflg)
			fprintf(fscript, "Script started on %s", ctime(&tvec));
#endif

		sigemptyset(&blkalrm);
		sigaddset(&blkalrm, SIGALRM);
		bzero(&sa, sizeof sa);
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = scriptflush;
		sigaction(SIGALRM, &sa, NULL);

		value.it_interval.tv_sec = 30;
		value.it_interval.tv_usec = 0;
		value.it_value = value.it_interval;
		setitimer(ITIMER_REAL, &value, NULL);
	}
	for (;;) {
		if (fscript && flush) {
			if (outcc) {
				fflush(fscript);
				outcc = 0;
			}
			flush = 0;
		}
		fcc = cc = read(master, obuf, sizeof (obuf));
		if (cc == -1 && errno == EINTR)
			continue;
		if (cc <= 0)
			break;
		if (fscript)
			sigprocmask(SIG_BLOCK, &blkalrm, NULL);
#ifndef NO_CONV
		if (l1mode) {
			unsigned char *cp = obuf;
			unsigned char *lp = cbuf;
			size_t n;
			wchar_t wc;

			off = cc;
			dump(obuf, cc);
			while (off) {
				n = mbrtowc(&wc, (char *)cp, off, &state);

				if (n == 0) {
					n = 1;
					wc = 0;
				} else if (n == (size_t)-1) {
					n = 1;
					wc = 0xFFFD;
					state.count = 0;
				} else if (n == (size_t)-2)
					break;
				off -= n;
				cp += n;
				if (wc < 0x0100)
					*lp++ = wc;
				else for (cc = 0; cc < wcwidth(wc); ++cc) {
					/* what about wcwidth==(-1) C0/C1? */
					memcpy(lp, l1rep, l1rlen);
					lp += l1rlen;
				}
			}
			cc = lp - cbuf;
			dump(cbuf, cc);
		} else if (lumode) {
			unsigned char *cp = ubuf;

			for (off = 0; off < cc; ++off)
				cp += wcrtomb((char *)cp, obuf[off], &state);
			dump(obuf, cc);
			cc = cp - ubuf;
			dump(ubuf, cc);
		}
#endif
		for (off = 0; off < cc; ) {
			ssize_t n = write(STDOUT_FILENO,
			    (l1mode ? cbuf : lumode ? ubuf : obuf) + off,
			    cc - off);
			if (n == -1 && errno != EAGAIN)
				break;
			if (n == 0)
				break;	/* skip writing */
			if (n > 0)
				off += n;
		}
		if (fscript) {
			fwrite(obuf, 1, fcc, fscript);
			outcc += cc;
			sigprocmask(SIG_UNBLOCK, &blkalrm, NULL);
		}
	}
#ifndef NO_CONV
	if (l1mode && state.count)
		/* incomplete multibyte char on exit */
		write(STDOUT_FILENO, l1rep, l1rlen);
#endif
	done(0);
}

/* ARGSUSED */
void
scriptflush(int signo __attribute__((__unused__)))
{
	flush = 1;
}

void
doshell(void)
{
	const char *shell, *shargv0;
	char *cp;

	shell = getenv("SHELL");
	if (shell == NULL)
		shell = _PATH_BSHELL;

	close(master);
	if (fscript)
		fclose(fscript);
	login_tty(slave);

	if (!do_loginshell)
		shargv0 = shell;
	else if ((shargv0 = cp = calloc(1, 1 + strlen(shell) + 1)) == NULL) {
		warn("out of memory");
		fail();
	} else {
		*cp++ = '-';
		memcpy(cp, shell, strlen(shell) + 1);
	}

	if (shcmd)
		execl(shell, shargv0, "-c", shcmd, NULL);
	else
		execl(shell, shargv0, "-i", NULL);
	warn("%s%s%s", shargv0, shcmd ? " -c " : " -i", shcmd ? shcmd : "");
	fail();
}

void
fail(void)
{
	kill(0, SIGTERM);
	done(1);
}

void
done(int eval)
{
	if (subchild) {
		if (fscript) {
#ifndef SMALL
			time_t tvec;

			tvec = time(NULL);
			if (!qflg)
				fprintf(fscript,"\nScript done on %s",
				    ctime(&tvec));
#endif
			fclose(fscript);
		}
		close(master);
	} else {
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &tt);
#ifndef SMALL
		if (!qflg)
			printf("Script done, %s%s\n",
			    fscript ? "output file is " : "no output file",
			    fname);
#endif
	}
	exit(eval);
}

void
usage(void)
{
#ifdef SMALL
	const char usage_str[] = "usage: script"
#else
	extern const char *__progname;
	fprintf(stderr, "usage: %s"
#endif
#ifdef NO_CONV
	    " [-as] [-c cmd] [-n | file]\n"
#else
	    " [-als] [-c cmd] [-L replstr] [-n | file]\n"
#endif
#ifdef SMALL
	    ;
	fwrite(usage_str, 1, sizeof (usage_str) - 1, stderr);
#else
	    , __progname);
#endif
	exit(1);
}

#ifdef DEBUG
static void
__dump(const char *name, const char *func, const uint8_t *buf, size_t len)
{
	size_t n = 0;

	fflush(NULL);
#if 0
	fprintf(stderr, "  dumping buffer <%s> in %s()", name, func);
	while (n < len)
		fprintf(stderr, "%s%02X",
		    n++ & 15 ? " " : "\r\n  ",
		    *buf++);
	fprintf(stderr, "\r\n");
#else
	fprintf(stderr, "{%s():%s[] =", func, name);
	while (n++ < len)
		fprintf(stderr, " %02X", *buf++);
	fprintf(stderr, "}");
#endif
	fflush(NULL);
}
#endif
