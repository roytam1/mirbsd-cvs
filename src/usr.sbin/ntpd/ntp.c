/*	$OpenBSD: ntp.c,v 1.92 2006/10/21 07:30:58 henning Exp $ */

/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 2003, 2004 Henning Brauer <henning@openbsd.org>
 * Copyright (c) 2004 Alexander Guy <alexander.guy@andern.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * The following disclaimer must also be retained:
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
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <poll.h>
#include <pwd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ntpd.h"
#include "ntp.h"

__RCSID("$MirOS: src/usr.sbin/ntpd/ntp.c,v 1.25 2010/09/21 21:24:46 tg Exp $");

#define	PFD_PIPE_MAIN	0
#define	PFD_MAX		1

volatile sig_atomic_t	 ntp_quit = 0;
struct imsgbuf		*ibuf_main;
struct ntpd_conf	*conf;
u_int			 peer_cnt;

void	ntp_sighdlr(int);
int	ntp_dispatch_imsg(void);
void	peer_add(struct ntp_peer *);
void	peer_remove(struct ntp_peer *);
int	offset_compare(const void *, const void *);

void
ntp_sighdlr(int sig)
{
	switch (sig) {
	case SIGINT:
	case SIGTERM:
		ntp_quit = 1;
		break;
	}
}

pid_t
ntp_main(int pipe_prnt[2], struct ntpd_conf *nconf)
{
	int			 a, b, nfds, i, j, idx_peers, timeout, nullfd;
	u_int			 pfd_elms = 0, idx2peer_elms = 0;
	u_int			 listener_cnt, new_cnt, sent_cnt, trial_cnt;
	pid_t			 pid;
	struct pollfd		*pfd = NULL;
	struct passwd		*pw;
	struct servent		*se;
	struct listen_addr	*la;
	struct ntp_peer		*p;
	struct ntp_peer		**idx2peer = NULL;
	struct timespec		 tp;
	struct stat		 stb;
	time_t			 nextaction;
	void			*newp;
	time_t			 nextstir, now;

	switch (pid = fork()) {
	case -1:
		fatal("cannot fork");
		break;
	case 0:
		break;
	default:
		return (pid);
	}

	/* force re-stir directly after fork, before chroot */
	arc4random_stir();
	(void)arc4random();
	nextstir = time(NULL) + 5400;

	if ((se = getservbyname("ntp", "udp")) == NULL)
		fatal("getservbyname");

	if ((pw = getpwnam(NTPD_USER)) == NULL)
		fatal("getpwnam");

	if ((nullfd = open(_PATH_DEVNULL, O_RDWR, 0)) == -1)
		fatal(NULL);

	if (stat(pw->pw_dir, &stb) == -1)
		fatal("stat");
	if (stb.st_uid != 0 || (stb.st_mode & (S_IWGRP|S_IWOTH)) != 0)
		fatal("bad privsep dir permissions");
	if (chroot(pw->pw_dir) == -1)
		fatal("chroot");
	if (chdir("/") == -1)
		fatal("chdir(\"/\")");

	if (!nconf->debug) {
		dup2(nullfd, STDIN_FILENO);
		dup2(nullfd, STDOUT_FILENO);
		dup2(nullfd, STDERR_FILENO);
	}
	close(nullfd);

	setproctitle("ntp engine");

	conf = nconf;
	setup_listeners(se, conf, &listener_cnt);

	if (setgroups(1, &pw->pw_gid) ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		fatal("can't drop privileges");

	endservent();

	signal(SIGTERM, ntp_sighdlr);
	signal(SIGINT, ntp_sighdlr);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	close(pipe_prnt[0]);
	if ((ibuf_main = malloc(sizeof(struct imsgbuf))) == NULL)
		fatal(NULL);
	imsg_init(ibuf_main, pipe_prnt[1]);

	TAILQ_FOREACH(p, &conf->ntp_peers, entry)
		client_peer_init(p);

	bzero(&conf->status, sizeof(conf->status));
	conf->status.synced = 0;
	clock_getres(CLOCK_REALTIME, &tp);
	b = 1000000000 / tp.tv_nsec;	/* convert to Hz */
	for (a = 0; b > 1; a--, b >>= 1)
		;
	conf->status.precision = a;
	conf->scale = 1;

	log_info("ntp engine ready");

	peer_cnt = 0;
	TAILQ_FOREACH(p, &conf->ntp_peers, entry)
		peer_cnt++;

	while (ntp_quit == 0) {
		if (nextstir < (now = time(NULL))) {
			/* 1.5 hours after start, then every 2 hrs */
			arc4random_stir();
			nextstir = now + 7200;
		}

		if (peer_cnt > idx2peer_elms) {
			if ((newp = realloc(idx2peer, sizeof(void *) *
			    peer_cnt)) == NULL) {
				/* panic for now */
				log_warn("could not resize idx2peer from %u -> "
				    "%u entries", idx2peer_elms, peer_cnt);
				fatalx("exiting");
			}
			idx2peer = newp;
			idx2peer_elms = peer_cnt;
		}

		new_cnt = PFD_MAX + peer_cnt + listener_cnt;
		if (new_cnt > pfd_elms) {
			if ((newp = realloc(pfd, sizeof(struct pollfd) *
			    new_cnt)) == NULL) {
				/* panic for now */
				log_warn("could not resize pfd from %u -> "
				    "%u entries", pfd_elms, new_cnt);
				fatalx("exiting");
			}
			pfd = newp;
			pfd_elms = new_cnt;
		}

		bzero(pfd, sizeof(struct pollfd) * pfd_elms);
		bzero(idx2peer, sizeof(void *) * idx2peer_elms);
		nextaction = now + 3600;
		pfd[PFD_PIPE_MAIN].fd = ibuf_main->fd;
		pfd[PFD_PIPE_MAIN].events = POLLIN;

		i = 1;
		TAILQ_FOREACH(la, &conf->listen_addrs, entry) {
			pfd[i].fd = la->fd;
			pfd[i].events = POLLIN;
			i++;
		}

		idx_peers = i;
		sent_cnt = trial_cnt = 0;
		TAILQ_FOREACH(p, &conf->ntp_peers, entry) {
			if (p->next > 0 && p->next <= now) {
				if (p->state > STATE_DNS_INPROGRESS)
					trial_cnt++;
				if (client_query(p) == 0)
					sent_cnt++;
			}
			if (p->next > 0 && p->next < nextaction)
				nextaction = p->next;

			if (p->deadline > 0 && p->deadline < nextaction)
				nextaction = p->deadline;
			if (p->deadline > 0 && p->deadline <= now) {
				timeout = error_interval();
				log_debug("no reply from %s received in time, "
				    "next query %ds", log_sockaddr(
				    (struct sockaddr *)&p->addr->ss), timeout);
				if (p->trustlevel >= TRUSTLEVEL_BADPEER &&
				    (p->trustlevel /= 2) < TRUSTLEVEL_BADPEER)
					chpeertrust(p, false);
				client_nextaddr(p);
				set_next(p, timeout);
			}

			if (p->state == STATE_QUERY_SENT &&
			    p->query->fd != -1) {
				pfd[i].fd = p->query->fd;
				pfd[i].events = POLLIN;
				idx2peer[i - idx_peers] = p;
				i++;
			}
		}

		if (conf->settime &&
		    ((trial_cnt > 0 && sent_cnt == 0) || peer_cnt == 0))
			priv_settime(0);	/* no good peers, don't wait */

		if (ibuf_main->w.queued > 0)
			pfd[PFD_PIPE_MAIN].events |= POLLOUT;

		timeout = nextaction - now;
		if (timeout < 0)
			timeout = 0;

		if ((nfds = poll(pfd, i, timeout * 1000)) == -1)
			if (errno != EINTR) {
				log_warn("poll error");
				ntp_quit = 1;
			}

		if (nfds > 0 && (pfd[PFD_PIPE_MAIN].revents & POLLOUT))
			if (msgbuf_write(&ibuf_main->w) < 0) {
				log_warn("pipe write error (to parent)");
				ntp_quit = 1;
			}

		if (nfds > 0 && pfd[PFD_PIPE_MAIN].revents & (POLLIN|POLLERR)) {
			nfds--;
			if (ntp_dispatch_imsg() == -1)
				ntp_quit = 1;
		}

		for (j = 1; nfds > 0 && j < idx_peers; j++)
			if (pfd[j].revents & (POLLIN|POLLERR)) {
				nfds--;
				if (server_dispatch(pfd[j].fd, conf) == -1)
					ntp_quit = 1;
			}

		for (; nfds > 0 && j < i; j++)
			if (pfd[j].revents & (POLLIN|POLLERR)) {
				nfds--;
				if (client_dispatch(idx2peer[j - idx_peers],
				    conf->settime, conf->trace) == -1)
					ntp_quit = 1;
			}
	}

	msgbuf_write(&ibuf_main->w);
	msgbuf_clear(&ibuf_main->w);
	free(ibuf_main);

	log_info("ntp engine exiting");
	_exit(0);
}

int
ntp_dispatch_imsg(void)
{
	struct imsg		 imsg;
	int			 n;
	struct ntp_peer		*peer, *npeer;
	u_int16_t		 dlen;
	u_char			*p;
	struct ntp_addr		*h;

	if ((n = imsg_read(ibuf_main)) == -1)
		return (-1);

	if (n == 0) {	/* connection closed */
		log_warnx("ntp_dispatch_imsg in ntp engine: pipe closed");
		return (-1);
	}

	for (;;) {
		if ((n = imsg_get(ibuf_main, &imsg)) == -1)
			return (-1);

		if (n == 0)
			break;

		switch (imsg.hdr.type) {
		case IMSG_ADJTIME:
			memcpy(&n, imsg.data, sizeof(n));
			if (n == 1 && !conf->status.synced) {
				log_info("clock is now synced");
				conf->status.synced = 1;
			} else if (n == 0 && conf->status.synced) {
				log_info("clock is now unsynced");
				conf->status.synced = 0;
			}
			break;
		case IMSG_HOST_DNS:
			TAILQ_FOREACH(peer, &conf->ntp_peers, entry)
				if (peer->id == imsg.hdr.peerid)
					break;
			if (peer == NULL) {
				log_warnx("IMSG_HOST_DNS with invalid peerID");
				break;
			}
			if (peer->addr != NULL) {
				log_warnx("IMSG_HOST_DNS but addr != NULL!");
				break;
			}

			dlen = imsg.hdr.len - IMSG_HEADER_SIZE;
			if (dlen == 0) {	/* no data -> temp error */
				peer->state = STATE_DNS_TEMPFAIL;
				break;
			}

			p = (u_char *)imsg.data;
			while (dlen >= sizeof(struct sockaddr_storage)) {
				if ((h = calloc(1, sizeof(struct ntp_addr))) ==
				    NULL)
					fatal(NULL);
				memcpy(&h->ss, p, sizeof(h->ss));
				p += sizeof(h->ss);
				dlen -= sizeof(h->ss);
				if (peer->addr_head.pool) {
					npeer = new_peer();
					h->next = NULL;
					npeer->addr = h;
					npeer->addr_head.a = h;
					client_peer_init(npeer);
					npeer->state = STATE_DNS_DONE;
					peer_add(npeer);
				} else {
					h->next = peer->addr;
					peer->addr = h;
					peer->addr_head.a = peer->addr;
					peer->state = STATE_DNS_DONE;
				}
			}
			if (dlen != 0)
				fatalx("IMSG_HOST_DNS: dlen != 0");
			if (peer->addr_head.pool)
				peer_remove(peer);
			else
				client_addr_init(peer);
			break;
		case IMSG_RESET:
#if 0	/* XXX maybe use type 1 (n == 1) for SIGHUP? */
			memcpy(&n, imsg.data, sizeof(n));
			if (n) {
				log_warn("invalid IMSG_RESET(%u) received", n);
				break;
			}
#endif
			conf->scale = 1;
			TAILQ_FOREACH(peer, &conf->ntp_peers, entry) {
				bzero(peer->reply, sizeof (peer->reply));
				peer->shift = 0;
				if (peer->trustlevel > TRUSTLEVEL_RESET)
					peer->trustlevel = TRUSTLEVEL_RESET;
				set_next(peer, -1);
			}
			break;
		default:
			break;
		}
		imsg_free(&imsg);
	}
	return (0);
}

void
peer_add(struct ntp_peer *p)
{
	TAILQ_INSERT_TAIL(&conf->ntp_peers, p, entry);
	peer_cnt++;
}

void
peer_remove(struct ntp_peer *p)
{
	TAILQ_REMOVE(&conf->ntp_peers, p, entry);
	free(p);
	peer_cnt--;
}

int
priv_adjtime(void)
{
	struct ntp_peer	 *p;
	int		  offset_cnt = 0, i = 0;
	struct ntp_peer	**peers;
	double		  offset_median;
	int		  weight_cnt, weight_half;

	TAILQ_FOREACH(p, &conf->ntp_peers, entry) {
		if (conf->trace > 5)
			log_info("priv_adjtime, #%02d %s peer, trust %d %s,"
			    " st %2d dst %3dms ofs %6.1fms addr %s",
			    offset_cnt,
			    p->update.good ? "good" : "bad ",
			    p->trustlevel,
			    p->trustlevel < TRUSTLEVEL_BADPEER ? "bad" : "ok",
			    p->update.status.stratum,
			    (int)((p->update.delay + .0005) * 1000.),
			    p->update.offset * 1000.,
			    log_sockaddr((struct sockaddr *)&p->addr->ss));
		else if (conf->trace > 3)
			log_info("priv_adjtime, #%02d, peer"
			    " trustlevel %d %s, %sgood",
			    offset_cnt,
			    p->trustlevel,
			    p->trustlevel < TRUSTLEVEL_BADPEER ? "bad" : "ok",
			    p->update.good ? "" : "not ");

		if (p->trustlevel < TRUSTLEVEL_BADPEER)
			continue;
		if (!p->update.good)
			return (1);
		offset_cnt++;
	}

	if (offset_cnt == 0) {
		if (conf->trace > 2)
			log_info("priv_adjtime, no peers");
		return (1);
	}

	if ((peers = calloc(offset_cnt, sizeof(struct ntp_peer *))) == NULL)
		fatal("calloc priv_adjtime");

	TAILQ_FOREACH(p, &conf->ntp_peers, entry) {
		if (p->trustlevel < TRUSTLEVEL_BADPEER)
			continue;
		peers[i++] = p;
	}

	qsort(peers, offset_cnt, sizeof(struct ntp_peer *), offset_compare);

	if (conf->trace > 2)
		log_info("priv_adjtime, %d peers", offset_cnt);

	weight_cnt = 0;
	weight_half = 0;
	offset_median = peers[offset_cnt / 2]->update.offset;
	for (i = 0; i < offset_cnt; ++i) {
		int peer_weight = (i + 1) * (offset_cnt - i);
		double peer_delta;

		if (weight_half) {
			/* even number of samples, II. median sample */
			peer_weight += weight_half;
			weight_half = 0;
		} else if ((i + 1) * 2 == offset_cnt) {
			/* even number of samples, I. median sample */
			weight_half = weight_cnt;
			peer_weight += weight_half;
		} else if (i * 2 + 1 == offset_cnt) {
			/* uneven number of samples, median sample */
			peer_weight += 2 * weight_cnt;
		}

		/* ignore false-tickers (off by a second from median) */
		peer_delta = offset_median - peers[i]->update.offset;
		if (peer_delta > 1. || peer_delta < -1.)
			peer_weight = 0;

		/* this is safe here despite shallow copy */
		peers[i]->update.good = peer_weight;
		weight_cnt += peer_weight;
	}
	offset_median = 0.0;
	for (i = 0; i < offset_cnt; ++i)
		if (peers[i]->update.good)
			offset_median += peers[i]->update.offset *
			    ((double)(peers[i]->update.good) / weight_cnt);

	if (conf->trace > 4 || (conf->trace && conf->debug))
		for (i = 0; i < offset_cnt; ++i)
			log_info("peer %2d: trust %s (%d) st %2d dst %3dms"
			    " ofs %6.1fms weight %4d addr %s", i,
			    peers[i]->trustlevel < TRUSTLEVEL_BADPEER ?
			    "bad" : "good", peers[i]->trustlevel,
			    peers[i]->update.status.stratum,
			    (int)((peers[i]->update.delay + .0005) * 1000.),
			    peers[i]->update.offset * 1000.,
			    peers[i]->update.good,
			    log_sockaddr((struct sockaddr *)&peers[i]->addr->ss));

	if (offset_cnt > 1 && offset_cnt % 2 == 0) {
		conf->status.rootdelay =
		    (peers[offset_cnt / 2 - 1]->update.delay +
		    peers[offset_cnt / 2]->update.delay) / 2;
		conf->status.stratum = MAX(
		    peers[offset_cnt / 2 - 1]->update.status.stratum,
		    peers[offset_cnt / 2]->update.status.stratum);
		if (conf->trace)
			log_info("adj%c stc %d dst %3d ofs %6.1f srv %s", '1',
			    peers[offset_cnt / 2 - 1]->update.status.stratum,
			    (int)((peers[offset_cnt / 2 - 1]->update.delay + .0005) * 1000.),
			    peers[offset_cnt / 2 - 1]->update.offset * 1000.,
			    log_sockaddr((struct sockaddr *)&peers[offset_cnt / 2 - 1]->addr->ss));
	} else {
		conf->status.rootdelay =
		    peers[offset_cnt / 2]->update.delay;
		conf->status.stratum =
		    peers[offset_cnt / 2]->update.status.stratum;
	}
	if (conf->trace)
		log_info("adj%c stc %d dst %3d ofs %6.1f srv %s",
		    (offset_cnt > 1 && offset_cnt % 2 == 0) ? '2' : 'x',
		    peers[offset_cnt / 2]->update.status.stratum,
		    (int)((peers[offset_cnt / 2]->update.delay + .0005) * 1000.),
		    peers[offset_cnt / 2]->update.offset * 1000.,
		    log_sockaddr((struct sockaddr *)&peers[offset_cnt / 2]->addr->ss));
	conf->status.leap = peers[offset_cnt / 2]->update.status.leap;

	imsg_compose(ibuf_main, IMSG_ADJTIME, 0, 0,
	    &offset_median, sizeof(offset_median));

	conf->status.reftime = gettime();
	/* one more than selected peer, but cap */
	conf->status.stratum = MIN(conf->status.stratum, 254) + 1;
	update_scale(offset_median);

	conf->status.refid4 =
	    peers[offset_cnt / 2]->update.status.refid4;
	if (peers[offset_cnt / 2]->addr->ss.ss_family == AF_INET)
		conf->status.refid = ((struct sockaddr_in *)
		    &peers[offset_cnt / 2]->addr->ss)->sin_addr.s_addr;
	else
		conf->status.refid = conf->status.refid4;
	if (peers[offset_cnt / 2]->update.status.stratum < 1)
		conf->status.refid =
		    peers[offset_cnt / 2]->update.status.refid;

	free(peers);

	TAILQ_FOREACH(p, &conf->ntp_peers, entry)
		p->update.good = 0;

	return (0);
}

int
offset_compare(const void *aa, const void *bb)
{
	const struct ntp_peer * const *a;
	const struct ntp_peer * const *b;

	a = aa;
	b = bb;

	if ((*a)->update.offset < (*b)->update.offset)
		return (-1);
	else if ((*a)->update.offset > (*b)->update.offset)
		return (1);
	else
		return (0);
}

void
priv_settime(double offset)
{
	struct ntp_peer *p;

	imsg_compose(ibuf_main, IMSG_SETTIME, 0, 0, &offset, sizeof(offset));
	conf->settime = 0;

	TAILQ_FOREACH(p, &conf->ntp_peers, entry) {
		if (p->next)
			p->next -= offset;
		if (p->deadline)
			p->deadline -= offset;
	}
}

void
priv_host_dns(char *name, u_int32_t peerid)
{
	u_int16_t	dlen;

	dlen = strlen(name) + 1;
	imsg_compose(ibuf_main, IMSG_HOST_DNS, peerid, 0, name, dlen);
}

void
update_scale(double offset)
{
	if (offset < 0)
		offset = -offset;

	if (offset > QSCALE_OFF_MAX)
		conf->scale = 1;
	else if (offset < QSCALE_OFF_MIN)
		conf->scale = QSCALE_OFF_MAX / QSCALE_OFF_MIN;
	else
		conf->scale = QSCALE_OFF_MAX / offset;
}

time_t
scale_interval(time_t requested)
{
	double interval = requested, r;

	r = (interval *= conf->scale) / 10.;
	if (r > 7.)
		r = 7.;
	return (interval + arc4random_uniform((int)(r + .5)) - (r / 2.));
}

time_t
error_interval(void)
{
	double interval = INTERVAL_QUERY_PATHETIC, r;

	r = (interval *= QSCALE_OFF_MAX / QSCALE_OFF_MIN) / 10.;
	return (interval + arc4random_uniform((int)(r + .5)) - (r / 2.));
}

void
chpeertrust(struct ntp_peer *p, bool nowvalid)
{
	static u_int nvpeers;
	const char *s = "";

	if (nowvalid)
		++nvpeers;
	else {
		if (nvpeers)
			--nvpeers;
		else
			log_warn("trying to decrease nvpeers below 0");
		s = "in";
	}

	log_info("peer %s now %svalid, %u valid peers total",
	    log_sockaddr((struct sockaddr *)&p->addr->ss),
	    s, nvpeers);
}
