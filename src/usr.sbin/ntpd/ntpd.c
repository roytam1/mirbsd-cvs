/*	$OpenBSD: ntpd.c,v 1.40 2005/09/06 21:27:10 wvdputte Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2007, 2008, 2011
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * Copyright (c) 2003, 2004 Henning Brauer <henning@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>
#include <pwd.h>
#include <resolv.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ntpd.h"

__RCSID("$MirOS: src/usr.sbin/ntpd/ntpd.c,v 1.20 2011/02/19 00:23:46 tg Exp $");

void		sighdlr(int);
__dead void	usage(void);
int		main(int, char *[]);
int		check_child(pid_t, const char *);
int		dispatch_imsg(struct ntpd_conf *);
void		reset_adjtime(void);
int		ntpd_adjtime(double, int);
void		ntpd_settime(double);

volatile sig_atomic_t	 quit = 0;
volatile sig_atomic_t	 reconfig = 0;
volatile sig_atomic_t	 sigchld = 0;
volatile sig_atomic_t	 sigusr1 = 0;
volatile sig_atomic_t	 arc4push = 0;
struct imsgbuf		*ibuf;

void
sighdlr(int sig)
{
	switch (sig) {
	case SIGTERM:
	case SIGINT:
		quit = 1;
		break;
	case SIGCHLD:
		sigchld = 1;
		arc4push = 1;
		break;
	case SIGHUP:
		reconfig = 1;
		arc4push = 1;
		break;
	case SIGUSR1:
		sigusr1 = 1;
		arc4push = 1;
		break;
	}
}

void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s [-dSst] [-f file]\n", __progname);
	exit(1);
}

#define POLL_MAX		8
#define PFD_PIPE		0

int
main(int argc, char *argv[])
{
	struct ntpd_conf	 conf;
	struct pollfd		 pfd[POLL_MAX];
	pid_t			 chld_pid = 0, pid;
	const char		*conffile;
	int			 ch, nfds, timeout = INFTIM;
	int			 pipe_chld[2];

	conffile = CONFFILE;

	bzero(&conf, sizeof(conf));

	log_init(1);		/* log to stderr until daemonized */
	res_init();		/* XXX */

	while ((ch = getopt(argc, argv, "df:sSt")) != -1) {
		switch (ch) {
		case 'd':
			conf.debug = 1;
			break;
		case 'f':
			conffile = optarg;
			break;
		case 's':
			conf.settime = 1;
			break;
		case 'S':
			conf.settime = 0;
			break;
		case 't':
			conf.trace++;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}

	if (parse_config(conffile, &conf))
		exit(1);

	if (geteuid()) {
		fprintf(stderr, "ntpd: need root privileges\n");
		exit(1);
	}

	if (getpwnam(NTPD_USER) == NULL) {
		fprintf(stderr, "ntpd: unknown user %s\n", NTPD_USER);
		exit(1);
	}
	endpwent();

	reset_adjtime();
	if (!conf.settime) {
		log_init(conf.debug);
		if (!conf.debug)
			if (daemon(1, 0))
				fatal("daemon");
	} else
		timeout = SETTIME_TIMEOUT * 1000;

	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_chld) == -1)
		fatal("socketpair");

	signal(SIGCHLD, sighdlr);
	/* fork child process */
	chld_pid = ntp_main(pipe_chld, &conf);

	setproctitle("[priv]");

	signal(SIGUSR1, sighdlr);
	signal(SIGTERM, sighdlr);
	signal(SIGINT, sighdlr);
	signal(SIGHUP, sighdlr);

	close(pipe_chld[1]);

	if ((ibuf = malloc(sizeof(struct imsgbuf))) == NULL)
		fatal(NULL);
	imsg_init(ibuf, pipe_chld[0]);

	while (quit == 0) {
		pfd[PFD_PIPE].fd = ibuf->fd;
		pfd[PFD_PIPE].events = POLLIN;
		if (ibuf->w.queued)
			pfd[PFD_PIPE].events |= POLLOUT;

		if ((nfds = poll(pfd, 1, timeout)) == -1)
			if (errno != EINTR) {
				log_warn("poll error");
				quit = 1;
			}

		if (nfds == 0 && conf.settime) {
			conf.settime = 0;
			timeout = INFTIM;
			log_init(conf.debug);
			log_debug("no reply received in time, skipping initial "
			    "time setting");
			if (!conf.debug)
				if (daemon(1, 0))
					fatal("daemon");
		}

		if (nfds > 0 && (pfd[PFD_PIPE].revents & POLLOUT))
			if (msgbuf_write(&ibuf->w) < 0) {
				log_warn("pipe write error (to child)");
				quit = 1;
			}

		if (nfds > 0 && pfd[PFD_PIPE].revents & POLLIN) {
			nfds--;
			if (dispatch_imsg(&conf) == -1)
				quit = 1;
		}

		if (arc4push) {
			arc4random_stir();
			arc4push = 0;
		}

		if (sigchld) {
			if (check_child(chld_pid, "child")) {
				quit = 1;
				chld_pid = 0;
			}
			sigchld = 0;
		}

		if (sigusr1) {
			int n = 0;	/* maybe use 1 for SIGHUP? */

			log_info("throwing away all received deltas");
			imsg_compose(ibuf, IMSG_RESET, 0, 0, &n, sizeof (n));
			sigusr1 = 0;
		}
	}

	signal(SIGCHLD, SIG_DFL);

	if (chld_pid)
		kill(chld_pid, SIGTERM);

	do {
		if ((pid = wait(NULL)) == -1 &&
		    errno != EINTR && errno != ECHILD)
			fatal("wait");
	} while (pid != -1 || (pid == -1 && errno == EINTR));

	msgbuf_clear(&ibuf->w);
	free(ibuf);
	log_info("Terminating");
	return (0);
}

int
check_child(pid_t pid, const char *pname)
{
	int	 status, sig;
	const char *signame;

	if (waitpid(pid, &status, WNOHANG) > 0) {
		if (WIFEXITED(status)) {
			log_warnx("Lost child: %s exited", pname);
			return (1);
		}
		if (WIFSIGNALED(status)) {
			sig = WTERMSIG(status);
			signame = strsignal(sig) ? strsignal(sig) : "unknown";
			log_warnx("Lost child: %s terminated; signal %d (%s)",
			    pname, sig, signame);
			return (1);
		}
	}

	return (0);
}

int
dispatch_imsg(struct ntpd_conf *conf)
{
	struct imsg		 imsg;
	int			 n, cnt;
	double			 d;
	char			*name;
	struct ntp_addr		*h, *hn;
	struct buf		*buf;

	if ((n = imsg_read(ibuf)) == -1)
		return (-1);

	if (n == 0) {	/* connection closed */
		log_warnx("dispatch_imsg in main: pipe closed");
		return (-1);
	}

	for (;;) {
		if ((n = imsg_get(ibuf, &imsg)) == -1)
			return (-1);

		if (n == 0)
			break;

		switch (imsg.hdr.type) {
		case IMSG_ADJTIME:
			if (imsg.hdr.len != IMSG_HEADER_SIZE + sizeof(d))
				fatalx("invalid IMSG_ADJTIME received");
			memcpy(&d, imsg.data, sizeof(d));
			n = ntpd_adjtime(d, conf->trace);
			imsg_compose(ibuf, IMSG_ADJTIME, 0, 0, &n, sizeof(n));
			break;
		case IMSG_SETTIME:
			if (imsg.hdr.len != IMSG_HEADER_SIZE + sizeof(d))
				fatalx("invalid IMSG_SETTIME received");
			if (!conf->settime)
				break;
			log_init(conf->debug);
			memcpy(&d, imsg.data, sizeof(d));
			ntpd_settime(d);
			/* daemonize now */
			if (!conf->debug)
				if (daemon(1, 0))
					fatal("daemon");
			conf->settime = 0;
			break;
		case IMSG_HOST_DNS:
			name = imsg.data;
			if (imsg.hdr.len < 1 + IMSG_HEADER_SIZE)
				fatalx("invalid IMSG_HOST_DNS received");
			imsg.hdr.len -= 1 + IMSG_HEADER_SIZE;
			if (name[imsg.hdr.len] != '\0' ||
			    strlen(name) != imsg.hdr.len)
				fatalx("invalid IMSG_HOST_DNS received");
			if ((cnt = host_dns(name, &hn)) == -1)
				break;
			buf = imsg_create(ibuf, IMSG_HOST_DNS,
			    imsg.hdr.peerid, 0,
			    cnt * sizeof(struct sockaddr_storage));
			if (buf == NULL)
				break;
			if (cnt > 0)
				for (h = hn; h != NULL; h = h->next)
					imsg_add(buf, &h->ss, sizeof(h->ss));

			imsg_close(ibuf, buf);
			break;
		case IMSG_RESET:
			log_warn("invalid IMSG_RESET received");
			break;
		default:
			break;
		}
		imsg_free(&imsg);
	}
	return (0);
}

void
reset_adjtime(void)
{
	struct timeval	tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	if (adjtime(&tv, NULL) == -1)
		log_warn("reset adjtime failed");
}

int
ntpd_adjtime(double d, int trace)
{
	struct timeval	tv, olddelta;
	double		o;
	int		synced = 0, rv;
	static int	firstadj = 1;

	d_to_tv(d, &tv);
	rv = adjtime(&tv, &olddelta);
	o = (double)olddelta.tv_sec + (double)olddelta.tv_usec / 1000000.;
	if (trace || d >= LOG_NEGLIGEE / 1000. || d <= LOG_NEGLIGEE / -1000.)
		log_info("adjusting local clock by %fs, old drift %fs", d, o);
	else
		log_debug("adjusting local clock by %fs, old drift %fs", d, o);
	if (rv == -1)
		log_warn("adjtime failed");
	else if (!firstadj && olddelta.tv_sec == 0 && olddelta.tv_usec == 0)
		synced = 1;
	firstadj = 0;
	return (synced);
}

void
ntpd_settime(double d)
{
	struct timeval	curtime, tv;
	char		buf[80];

	/* if the offset is small, don't call settimeofday */
	if (d < SETTIME_MIN_OFFSET && d > -SETTIME_MIN_OFFSET)
		return;

	d_to_tv(d, &tv);
	gettimeofday(&curtime, NULL);
	curtime.tv_sec += tv.tv_sec;
	curtime.tv_usec += tv.tv_usec;
	while (curtime.tv_usec > 999999) {
		curtime.tv_sec++;
		curtime.tv_usec -= 1000000;
	}

	if (settimeofday(&curtime, NULL) == -1) {
		log_warn("settimeofday");
		return;
	}
	strftime(buf, sizeof (buf), "%a %b %e %H:%M:%S %Z %Y",
	    localtime(&curtime.tv_sec));
	log_info("set local clock to %s (offset %fs)", buf, d);
}
