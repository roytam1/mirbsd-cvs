/*	$OpenBSD: dhclient.c,v 1.109 2007/02/13 21:54:22 stevesk Exp $	*/

/*
 * Copyright 2004 Henning Brauer <henning@openbsd.org>
 * Copyright (c) 1995, 1996, 1997, 1998, 1999
 * The Internet Software Consortium.    All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of The Internet Software Consortium nor the names
 *    of its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INTERNET SOFTWARE CONSORTIUM AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE INTERNET SOFTWARE CONSORTIUM OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This software has been written for the Internet Software Consortium
 * by Ted Lemon <mellon@fugue.com> in cooperation with Vixie
 * Enterprises.  To learn more about the Internet Software Consortium,
 * see ``http://www.vix.com/isc''.  To learn more about Vixie
 * Enterprises, see ``http://www.vix.com''.
 *
 * This client was substantially modified and enhanced by Elliot Poger
 * for use on Linux while he was working on the MosquitoNet project at
 * Stanford.
 *
 * The current version owes much to Elliot's Linux enhancements, but
 * was substantially reorganized and partially rewritten by Ted Lemon
 * so as to use the same networking framework that the Internet Software
 * Consortium DHCP server uses.   Much system-specific configuration code
 * was moved into a shell script so that as support for more operating
 * systems is added, it will not be necessary to port and maintain
 * system-specific configuration code to these operating systems - instead,
 * the shell script can invoke the native tools to accomplish the same
 * purpose.
 */

#include <ctype.h>
#include <poll.h>
#include <pwd.h>
#include <stdbool.h>

#include "dhcpd.h"
#include "privsep.h"

__RCSID("$MirOS: src/sbin/dhclient/dhclient.c,v 1.7 2007/02/17 03:23:43 tg Exp $");

#define	CLIENT_PATH "PATH=/usr/bin:/usr/sbin:/bin:/sbin"

time_t cur_time;
time_t default_lease_time = 43200; /* 12 hours... */

char *path_dhclient_conf = _PATH_DHCLIENT_CONF;
char *path_dhclient_db = NULL;

int log_perror = 1;
int privfd;
int nullfd = -1;
int no_daemon;
int unknown_ok = 1;
int routefd = -1;

struct iaddr iaddr_broadcast = { 4, { 255, 255, 255, 255 } };
struct in_addr inaddr_any;
struct sockaddr_in sockaddr_broadcast;

#define TIME_MAX 2147483647

struct interface_info *ifi;
struct client_state *client;
struct client_config *config;

int		 findproto(char *, int);
struct sockaddr	*get_ifa(char *, int);
void		 usage(void);
int		 check_option(struct client_lease *l, int option);
int		 ipv4addrs(char * buf);
int		 res_hnok(const char *dn, bool wsp_ok);
char		*option_as_string(unsigned int code, unsigned char *data, int len);
int		 fork_privchld(int, int);

#define	ROUNDUP(a) \
	    ((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define	ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

time_t	scripttime;

int
findproto(char *cp, int n)
{
	struct sockaddr *sa;
	int i;

	if (n == 0)
		return -1;
	for (i = 1; i; i <<= 1) {
		if (i & n) {
			sa = (struct sockaddr *)cp;
			switch (i) {
			case RTA_IFA:
			case RTA_DST:
			case RTA_GATEWAY:
			case RTA_NETMASK:
				if (sa->sa_family == AF_INET)
					return AF_INET;
				if (sa->sa_family == AF_INET6)
					return AF_INET6;
				break;
			case RTA_IFP:
				break;
			}
			ADVANCE(cp, sa);
		}
	}
	return (-1);
}

struct sockaddr *
get_ifa(char *cp, int n)
{
	struct sockaddr *sa;
	int i;

	if (n == 0)
		return (NULL);
	for (i = 1; i; i <<= 1)
		if (i & n) {
			sa = (struct sockaddr *)cp;
			if (i == RTA_IFA)
				return (sa);
			ADVANCE(cp, sa);
		}

	return (NULL);
}
struct iaddr defaddr = { 4 };

/* ARGSUSED */
void
routehandler(void)
{
	char msg[2048];
	struct rt_msghdr *rtm;
	struct if_msghdr *ifm;
	struct ifa_msghdr *ifam;
	struct if_announcemsghdr *ifan;
	struct client_lease *l;
	time_t t = time(NULL);
	struct sockaddr *sa;
	struct iaddr a;
	ssize_t n;

	do {
		n = read(routefd, &msg, sizeof(msg));
	} while (n == -1 && errno == EINTR);

	rtm = (struct rt_msghdr *)msg;
	if (n < sizeof(rtm->rtm_msglen) || n < rtm->rtm_msglen ||
	    rtm->rtm_version != RTM_VERSION)
		return;

	switch (rtm->rtm_type) {
	case RTM_NEWADDR:
		ifam = (struct ifa_msghdr *)rtm;
		if (ifam->ifam_index != ifi->index)
			break;
		if (findproto((char *)(ifam + 1), ifam->ifam_addrs) != AF_INET)
			break;
		sa = get_ifa((char *)(ifam + 1), ifam->ifam_addrs);
		if (sa == NULL)
			goto die;

		if ((a.len = sizeof(struct in_addr)) > sizeof(a.iabuf))
			error("king bula sez: len mismatch");
		memcpy(a.iabuf, &((struct sockaddr_in *)sa)->sin_addr, a.len);
		if (addr_eq(a, defaddr))
			break;

		for (l = client->active; l != NULL; l = l->next)
			if (addr_eq(a, l->address))
				break;

		if (l != NULL || (client->alias &&
		    addr_eq(a, client->alias->address)))
			/* new addr is the one we set */
			break;

		goto die;
	case RTM_DELADDR:
		ifam = (struct ifa_msghdr *)rtm;
		if (ifam->ifam_index != ifi->index)
			break;
		if (findproto((char *)(ifam + 1), ifam->ifam_addrs) != AF_INET)
			break;
		if (scripttime == 0 || t < scripttime + 10)
			break;
		goto die;
	case RTM_IFINFO:
		ifm = (struct if_msghdr *)rtm;
		if (ifm->ifm_index != ifi->index)
			break;
		if ((rtm->rtm_flags & RTF_UP) == 0)
			goto die;
		break;
	case RTM_IFANNOUNCE:
		ifan = (struct if_announcemsghdr *)rtm;
		if (ifan->ifan_what == IFAN_DEPARTURE &&
		    ifan->ifan_index == ifi->index)
			goto die;
		break;
	default:
		break;
	}
	return;

die:
	script_init("FAIL", NULL);
	if (client->alias)
		script_write_params("alias_", client->alias);
	script_go();
	exit(1);
}

int
main(int argc, char *argv[])
{
	int	 ch, fd, quiet = 0, i = 0, pipe_fd[2];
	extern char *__progname;
	struct passwd *pw;

	/* Initially, log errors to stderr as well as to syslogd. */
	openlog(__progname, LOG_PID | LOG_NDELAY, DHCPD_LOG_FACILITY);
	setlogmask(LOG_UPTO(LOG_INFO));

	while ((ch = getopt(argc, argv, "c:dl:qu")) != -1)
		switch (ch) {
		case 'c':
			path_dhclient_conf = optarg;
			break;
		case 'd':
			no_daemon = 1;
			break;
		case 'l':
			path_dhclient_db = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		case 'u':
			unknown_ok = 0;
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	ifi = calloc(1, sizeof(*ifi));
	if (ifi == NULL)
		error("ifi calloc");
	client = calloc(1, sizeof(*client));
	if (client == NULL)
		error("client calloc");
	config = calloc(1, sizeof(*config));
	if (config == NULL)
		error("config calloc");

	if (strlcpy(ifi->name, argv[0], IFNAMSIZ) >= IFNAMSIZ)
		error("Interface name too long");
	if (path_dhclient_db == NULL && asprintf(&path_dhclient_db, "%s.%s",
	    _PATH_DHCLIENT_DB, ifi->name) == -1)
		error("asprintf");

	if (quiet)
		log_perror = 0;

	tzset();
	time(&cur_time);

	memset(&sockaddr_broadcast, 0, sizeof(sockaddr_broadcast));
	sockaddr_broadcast.sin_family = AF_INET;
	sockaddr_broadcast.sin_port = htons(REMOTE_PORT);
	sockaddr_broadcast.sin_addr.s_addr = INADDR_BROADCAST;
	sockaddr_broadcast.sin_len = sizeof(sockaddr_broadcast);
	inaddr_any.s_addr = INADDR_ANY;

	read_client_conf();

	if (!interface_link_status(ifi->name)) {
		int linkstat = interface_link_forceup(ifi->name);

		fprintf(stderr, "%s: no link ...", ifi->name);
		if (config->link_timeout == 0) {
			fprintf(stderr, " giving up\n");
			if (linkstat == 0)
				interface_link_forcedown(ifi->name);
			exit(1);
		}
		fflush(stderr);
		sleep(1);
		while (!interface_link_status(ifi->name)) {
			fprintf(stderr, ".");
			fflush(stderr);
			if (++i > config->link_timeout) {
				fprintf(stderr, " giving up\n");
				if (linkstat == 0)
					interface_link_forcedown(ifi->name);
				exit(1);
			}
			sleep(1);
		}
		fprintf(stderr, " got link\n");
	}

	if ((nullfd = open(_PATH_DEVNULL, O_RDWR, 0)) == -1)
		error("cannot open %s: %m", _PATH_DEVNULL);

	if ((pw = getpwnam("_dhcp")) == NULL) {
		warning("no such user: _dhcp, falling back to \"nobody\"");
		if ((pw = getpwnam("nobody")) == NULL)
			error("no such user: nobody");
	}

	if (pipe(pipe_fd) == -1)
		error("pipe");

	fork_privchld(pipe_fd[0], pipe_fd[1]);

	close(pipe_fd[0]);
	privfd = pipe_fd[1];

	if ((fd = open(path_dhclient_db, O_RDONLY|O_EXLOCK|O_CREAT, 0)) == -1)
		error("can't open and lock %s: %m", path_dhclient_db);
	read_client_leases();
	rewrite_client_leases();
	close(fd);

	priv_script_init("PREINIT", NULL);
	if (client->alias)
		priv_script_write_params("alias_", client->alias);
	priv_script_go();

	if ((routefd = socket(PF_ROUTE, SOCK_RAW, 0)) == -1)
		error("socket(PF_ROUTE, SOCK_RAW): %m");

	/* set up the interface */
	discover_interface();

	if (chroot(_PATH_VAREMPTY) == -1)
		error("chroot");
	if (chdir("/") == -1)
		error("chdir(\"/\")");

	if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) == -1)
		error("setresgid");
	if (setgroups(1, &pw->pw_gid) == -1)
		error("setgroups");
	if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) == -1)
		error("setresuid");

	endpwent();

	setproctitle("%s", ifi->name);

	client->state = S_INIT;
	state_reboot();

	dispatch();

	/* not reached */
	return (0);
}

void
usage(void)
{
	extern char	*__progname;

	fprintf(stderr, "usage: %s [-dqu] ", __progname);
	fprintf(stderr, "[-c conffile] [-l leasefile] interface\n");
	exit(1);
}

/*
 * Individual States:
 *
 * Each routine is called from the dhclient_state_machine() in one of
 * these conditions:
 * -> entering INIT state
 * -> recvpacket_flag == 0: timeout in this state
 * -> otherwise: received a packet in this state
 *
 * Return conditions as handled by dhclient_state_machine():
 * Returns 1, sendpacket_flag = 1: send packet, reset timer.
 * Returns 1, sendpacket_flag = 0: just reset the timer (wait for a milestone).
 * Returns 0: finish the nap which was interrupted for no good reason.
 *
 * Several per-interface variables are used to keep track of the process:
 *   active_lease: the lease that is being used on the interface
 *                 (null pointer if not configured yet).
 *   offered_leases: leases corresponding to DHCPOFFER messages that have
 *                   been sent to us by DHCP servers.
 *   acked_leases: leases corresponding to DHCPACK messages that have been
 *                 sent to us by DHCP servers.
 *   sendpacket: DHCP packet we're trying to send.
 *   destination: IP address to send sendpacket to
 * In addition, there are several relevant per-lease variables.
 *   T1_expiry, T2_expiry, lease_expiry: lease milestones
 * In the active lease, these control the process of renewing the lease;
 * In leases on the acked_leases list, this simply determines when we
 * can no longer legitimately use the lease.
 */
void
state_reboot(void)
{
	/* If we don't remember an active lease, go straight to INIT. */
	if (!client->active || client->active->is_bootp) {
		state_init();
		return;
	}

	/* We are in the rebooting state. */
	client->state = S_REBOOTING;

	/* make_request doesn't initialize xid because it normally comes
	   from the DHCPDISCOVER, but we haven't sent a DHCPDISCOVER,
	   so pick an xid now. */
	client->xid = arc4random();

	/* Make a DHCPREQUEST packet, and set appropriate per-interface
	   flags. */
	make_request(client->active);
	client->destination = iaddr_broadcast;
	client->first_sending = cur_time;
	client->interval = config->initial_interval;

	/* Zap the medium list... */
	client->medium = NULL;

	/* Send out the first DHCPREQUEST packet. */
	send_request();
}

/*
 * Called when a lease has completely expired and we've
 * been unable to renew it.
 */
void
state_init(void)
{
	/* Make a DHCPDISCOVER packet, and set appropriate per-interface
	   flags. */
	make_discover(client->active);
	client->xid = client->packet.xid;
	client->destination = iaddr_broadcast;
	client->state = S_SELECTING;
	client->first_sending = cur_time;
	client->interval = config->initial_interval;

	/* Add an immediate timeout to cause the first DHCPDISCOVER packet
	   to go out. */
	send_discover();
}

/*
 * state_selecting is called when one or more DHCPOFFER packets
 * have been received and a configurable period of time has passed.
 */
void
state_selecting(void)
{
	struct client_lease *lp, *next, *picked;

	/* Cancel state_selecting and send_discover timeouts, since either
	   one could have got us here. */
	cancel_timeout(state_selecting);
	cancel_timeout(send_discover);

	/* We have received one or more DHCPOFFER packets.   Currently,
	   the only criterion by which we judge leases is whether or
	   not we get a response when we arp for them. */
	picked = NULL;
	for (lp = client->offered_leases; lp; lp = next) {
		next = lp->next;

		/* Check to see if we got an ARPREPLY for the address
		   in this particular lease. */
		if (!picked) {
			script_init("ARPCHECK", lp->medium);
			script_write_params("check_", lp);

			/* If the ARPCHECK code detects another
			   machine using the offered address, it exits
			   nonzero.  We need to send a DHCPDECLINE and
			   toss the lease. */
			if (script_go()) {
				make_decline(lp);
				send_decline();
				goto freeit;
			}
			picked = lp;
			picked->next = NULL;
		} else {
freeit:
			free_client_lease(lp);
		}
	}
	client->offered_leases = NULL;

	/* If we just tossed all the leases we were offered, go back
	   to square one. */
	if (!picked) {
		client->state = S_INIT;
		state_init();
		return;
	}

	/* If it was a BOOTREPLY, we can just take the address right now. */
	if (!picked->options[DHO_DHCP_MESSAGE_TYPE].len) {
		client->new = picked;

		/* Make up some lease expiry times
		   XXX these should be configurable. */
		client->new->expiry = cur_time + 12000;
		client->new->renewal += cur_time + 8000;
		client->new->rebind += cur_time + 10000;

		client->state = S_REQUESTING;

		/* Bind to the address we received. */
		bind_lease();
		return;
	}

	/* Go to the REQUESTING state. */
	client->destination = iaddr_broadcast;
	client->state = S_REQUESTING;
	client->first_sending = cur_time;
	client->interval = config->initial_interval;

	/* Make a DHCPREQUEST packet from the lease we picked. */
	make_request(picked);
	client->xid = client->packet.xid;

	/* Toss the lease we picked - we'll get it back in a DHCPACK. */
	free_client_lease(picked);

	/* Add an immediate timeout to send the first DHCPREQUEST packet. */
	send_request();
}

/*
 * state_requesting is called when we receive a DHCPACK message after
 * having sent out one or more DHCPREQUEST packets.
 */
void
dhcpack(struct iaddr client_addr, struct option_data *options)
{
	struct client_lease *lease;

	if (client->xid != client->packet.xid)
		return;

	if (client->state != S_REBOOTING &&
	    client->state != S_REQUESTING &&
	    client->state != S_RENEWING &&
	    client->state != S_REBINDING)
		return;

	note("DHCPACK from %s", piaddr(client_addr));

	lease = packet_to_lease(client_addr, options);
	if (!lease) {
		note("packet_to_lease failed.");
		return;
	}

	client->new = lease;

	/* Stop resending DHCPREQUEST. */
	cancel_timeout(send_request);

	/* Figure out the lease time. */
	if (client->new->options[DHO_DHCP_LEASE_TIME].data)
		client->new->expiry =
		    getULong(client->new->options[DHO_DHCP_LEASE_TIME].data);
	else
		client->new->expiry = default_lease_time;
	/* A number that looks negative here is really just very large,
	   because the lease expiry offset is unsigned. */
	if (client->new->expiry < 0)
		client->new->expiry = TIME_MAX;
	/* XXX should be fixed by resetting the client state */
	if (client->new->expiry < 60)
		client->new->expiry = 60;

	/* Take the server-provided renewal time if there is one;
	   otherwise figure it out according to the spec. */
	if (client->new->options[DHO_DHCP_RENEWAL_TIME].len)
		client->new->renewal =
		    getULong(client->new->options[DHO_DHCP_RENEWAL_TIME].data);
	else
		client->new->renewal = client->new->expiry / 2;

	/* Same deal with the rebind time. */
	if (client->new->options[DHO_DHCP_REBINDING_TIME].len)
		client->new->rebind =
		    getULong(client->new->options[DHO_DHCP_REBINDING_TIME].data);
	else
		client->new->rebind = client->new->renewal +
		    client->new->renewal / 2 + client->new->renewal / 4;

	client->new->expiry += cur_time;
	/* Lease lengths can never be negative. */
	if (client->new->expiry < cur_time)
		client->new->expiry = TIME_MAX;
	client->new->renewal += cur_time;
	if (client->new->renewal < cur_time)
		client->new->renewal = TIME_MAX;
	client->new->rebind += cur_time;
	if (client->new->rebind < cur_time)
		client->new->rebind = TIME_MAX;

	bind_lease();
}

void
bind_lease(void)
{
	/* Remember the medium. */
	client->new->medium = client->medium;

	/* Write out the new lease. */
	write_client_lease(client->new, 0);

	/* Run the client script with the new parameters. */
	script_init((client->state == S_REQUESTING ? "BOUND" :
	    (client->state == S_RENEWING ? "RENEW" :
	    (client->state == S_REBOOTING ? "REBOOT" : "REBIND"))),
	    client->new->medium);
	if (client->active && client->state != S_REBOOTING)
		script_write_params("old_", client->active);
	script_write_params("new_", client->new);
	if (client->alias)
		script_write_params("alias_", client->alias);
	script_go();

	/* Replace the old active lease with the new one. */
	if (client->active)
		free_client_lease(client->active);
	client->active = client->new;
	client->new = NULL;

	/* Set up a timeout to start the renewal process. */
	add_timeout(client->active->renewal, state_bound);

	note("bound to %s -- renewal in %ld seconds.",
	    piaddr(client->active->address),
	    (long)(client->active->renewal - cur_time));
	client->state = S_BOUND;
	reinitialize_interface();
	go_daemon();
}

/*
 * state_bound is called when we've successfully bound to a particular
 * lease, but the renewal time on that lease has expired.   We are
 * expected to unicast a DHCPREQUEST to the server that gave us our
 * original lease.
 */
void
state_bound(void)
{
	/* T1 has expired. */
	make_request(client->active);
	client->xid = client->packet.xid;

	if (client->active->options[DHO_DHCP_SERVER_IDENTIFIER].len == 4) {
		memcpy(client->destination.iabuf,
		    client->active->options[DHO_DHCP_SERVER_IDENTIFIER].data,
		    4);
		client->destination.len = 4;
	} else
		client->destination = iaddr_broadcast;

	client->first_sending = cur_time;
	client->interval = config->initial_interval;
	client->state = S_RENEWING;

	/* Send the first packet immediately. */
	send_request();
}

void
dhcpoffer(struct iaddr client_addr, struct option_data *options)
{
	struct client_lease *lease, *lp;
	int i;
	int arp_timeout_needed, stop_selecting;
	char *name = options[DHO_DHCP_MESSAGE_TYPE].len ? "DHCPOFFER" :
	    "BOOTREPLY";

	if (client->xid != client->packet.xid)
		return;

	if (client->state != S_SELECTING)
		return;

	note("%s from %s", name, piaddr(client_addr));

	/* If this lease doesn't supply the minimum required parameters,
	   blow it off. */
	for (i = 0; config->required_options[i]; i++) {
		if (!options[config->required_options[i]].len) {
			note("%s isn't satisfactory.", name);
			return;
		}
	}

	/* If we've already seen this lease, don't record it again. */
	for (lease = client->offered_leases;
	    lease; lease = lease->next) {
		if (lease->address.len == sizeof(client->packet.yiaddr) &&
		    !memcmp(lease->address.iabuf,
		    &client->packet.yiaddr, lease->address.len)) {
			debug("%s already seen.", name);
			return;
		}
	}

	lease = packet_to_lease(client_addr, options);
	if (!lease) {
		note("packet_to_lease failed.");
		return;
	}

	/* If this lease was acquired through a BOOTREPLY, record that
	   fact. */
	if (!options[DHO_DHCP_MESSAGE_TYPE].len)
		lease->is_bootp = 1;

	/* Record the medium under which this lease was offered. */
	lease->medium = client->medium;

	/* Send out an ARP Request for the offered IP address. */
	script_init("ARPSEND", lease->medium);
	script_write_params("check_", lease);
	/* If the script can't send an ARP request without waiting,
	   we'll be waiting when we do the ARPCHECK, so don't wait now. */
	if (script_go())
		arp_timeout_needed = 0;
	else
		arp_timeout_needed = 2;

	/* Figure out when we're supposed to stop selecting. */
	stop_selecting = client->first_sending + config->select_interval;

	/* If this is the lease we asked for, put it at the head of the
	   list, and don't mess with the arp request timeout. */
	if (lease->address.len == client->requested_address.len &&
	    !memcmp(lease->address.iabuf,
	    client->requested_address.iabuf,
	    client->requested_address.len)) {
		lease->next = client->offered_leases;
		client->offered_leases = lease;
	} else {
		/* If we already have an offer, and arping for this
		   offer would take us past the selection timeout,
		   then don't extend the timeout - just hope for the
		   best. */
		if (client->offered_leases &&
		    (cur_time + arp_timeout_needed) > stop_selecting)
			arp_timeout_needed = 0;

		/* Put the lease at the end of the list. */
		lease->next = NULL;
		if (!client->offered_leases)
			client->offered_leases = lease;
		else {
			for (lp = client->offered_leases; lp->next;
			    lp = lp->next)
				;	/* nothing */
			lp->next = lease;
		}
	}

	/* If we're supposed to stop selecting before we've had time
	   to wait for the ARPREPLY, add some delay to wait for
	   the ARPREPLY. */
	if (stop_selecting - cur_time < arp_timeout_needed)
		stop_selecting = cur_time + arp_timeout_needed;

	/* If the selecting interval has expired, go immediately to
	   state_selecting().  Otherwise, time out into
	   state_selecting at the select interval. */
	if (stop_selecting <= 0)
		state_selecting();
	else {
		add_timeout(stop_selecting, state_selecting);
		cancel_timeout(send_discover);
	}
}

/*
 * Allocate a client_lease structure and initialize it from the
 * parameters in the specified packet.
 */
struct client_lease *
packet_to_lease(struct iaddr client_addr, struct option_data *options)
{
	struct client_lease *lease;
	int i;

	lease = malloc(sizeof(struct client_lease));

	if (!lease) {
		warning("dhcpoffer: no memory to record lease.");
		return (NULL);
	}

	memset(lease, 0, sizeof(*lease));

	/* Copy the lease options. */
	for (i = 0; i < 256; i++) {
		if (options[i].len) {
			lease->options[i] = options[i];
			options[i].data = NULL;
			options[i].len = 0;
			if (!check_option(lease, i)) {
				warning("Invalid lease option - ignoring offer");
				free_client_lease(lease);
				return (NULL);
			}
		}
	}

	lease->address.len = sizeof(client->packet.yiaddr);
	memcpy(lease->address.iabuf, &client->packet.yiaddr,
	    lease->address.len);

	/* If the server name was filled out, copy it. */
	if ((!options[DHO_DHCP_OPTION_OVERLOAD].len ||
	    !(options[DHO_DHCP_OPTION_OVERLOAD].data[0] & 2)) &&
	    client->packet.sname[0]) {
		lease->server_name = malloc(DHCP_SNAME_LEN + 1);
		if (!lease->server_name) {
			warning("dhcpoffer: no memory for server name.");
			free_client_lease(lease);
			return (NULL);
		}
		memcpy(lease->server_name, client->packet.sname,
		    DHCP_SNAME_LEN);
		lease->server_name[DHCP_SNAME_LEN] = '\0';
		if (!res_hnok(lease->server_name, false)) {
			warning("Bogus server name %s", lease->server_name);
			free(lease->server_name);
			lease->server_name = NULL;
		}
	}

	/* Ditto for the filename. */
	if ((!options[DHO_DHCP_OPTION_OVERLOAD].len ||
	    !(options[DHO_DHCP_OPTION_OVERLOAD].data[0] & 1)) &&
	    client->packet.file[0]) {
		/* Don't count on the NUL terminator. */
		lease->filename = malloc(DHCP_FILE_LEN + 1);
		if (!lease->filename) {
			warning("dhcpoffer: no memory for filename.");
			free_client_lease(lease);
			return (NULL);
		}
		memcpy(lease->filename, client->packet.file, DHCP_FILE_LEN);
		lease->filename[DHCP_FILE_LEN] = '\0';
	}
	return lease;
}

void
dhcpnak(struct iaddr client_addr, struct option_data *options)
{
	if (client->xid != client->packet.xid)
		return;

	if (client->state != S_REBOOTING &&
	    client->state != S_REQUESTING &&
	    client->state != S_RENEWING &&
	    client->state != S_REBINDING)
		return;

	note("DHCPNAK from %s", piaddr(client_addr));

	if (!client->active) {
		note("DHCPNAK with no active lease.");
		return;
	}

	free_client_lease(client->active);
	client->active = NULL;

	/* Stop sending DHCPREQUEST packets... */
	cancel_timeout(send_request);

	client->state = S_INIT;
	state_init();
}

/*
 * Send out a DHCPDISCOVER packet, and set a timeout to send out another
 * one after the right interval has expired.  If we don't get an offer by
 * the time we reach the panic interval, call the panic function.
 */
void
send_discover(void)
{
	int interval, increase = 1;

	/* Figure out how long it's been since we started transmitting. */
	interval = cur_time - client->first_sending;

	/* If we're past the panic timeout, call the script and tell it
	   we haven't found anything for this interface yet. */
	if (interval > config->timeout) {
		state_panic();
		return;
	}

	/* If we're selecting media, try the whole list before doing
	   the exponential backoff, but if we've already received an
	   offer, stop looping, because we obviously have it right. */
	if (!client->offered_leases && config->media) {
		int fail = 0;
again:
		if (client->medium) {
			client->medium = client->medium->next;
			increase = 0;
		}
		if (!client->medium) {
			if (fail)
				error("No valid media types for %s!", ifi->name);
			client->medium = config->media;
			increase = 1;
		}

		note("Trying medium \"%s\" %d", client->medium->string,
		    increase);
		script_init("MEDIUM", client->medium);
		if (script_go())
			goto again;
	}

	/*
	 * If we're supposed to increase the interval, do so.  If it's
	 * currently zero (i.e., we haven't sent any packets yet), set
	 * it to initial_interval; otherwise, add to it a random
	 * number between zero and two times itself.  On average, this
	 * means that it will double with every transmission.
	 */
	if (increase) {
		if (!client->interval)
			client->interval = config->initial_interval;
		else {
			client->interval += (arc4random() >> 2) %
			    (2 * client->interval);
		}

		/* Don't backoff past cutoff. */
		if (client->interval > config->backoff_cutoff)
			client->interval = ((config->backoff_cutoff / 2)
				 + ((arc4random() >> 2) %
				    config->backoff_cutoff));
	} else if (!client->interval)
		client->interval = config->initial_interval;

	/* If the backoff would take us to the panic timeout, just use that
	   as the interval. */
	if (cur_time + client->interval >
	    client->first_sending + config->timeout)
		client->interval = (client->first_sending +
			 config->timeout) - cur_time + 1;

	/* Record the number of seconds since we started sending. */
	if (interval < 65536)
		client->packet.secs = htons(interval);
	else
		client->packet.secs = htons(65535);
	client->secs = client->packet.secs;

	note("DHCPDISCOVER on %s to %s port %d interval %ld",
	    ifi->name, inet_ntoa(sockaddr_broadcast.sin_addr),
	    ntohs(sockaddr_broadcast.sin_port), (long)client->interval);

	/* Send out a packet. */
	send_packet(inaddr_any, &sockaddr_broadcast, NULL);

	add_timeout(cur_time + client->interval, send_discover);
}

/*
 * state_panic gets called if we haven't received any offers in a preset
 * amount of time.   When this happens, we try to use existing leases
 * that haven't yet expired, and failing that, we call the client script
 * and hope it can do something.
 */
void
state_panic(void)
{
	struct client_lease *loop = client->active;
	struct client_lease *lp;

	note("No DHCPOFFERS received.");

	/* We may not have an active lease, but we may have some
	   predefined leases that we can try. */
	if (!client->active && client->leases)
		goto activate_next;

	/* Run through the list of leases and see if one can be used. */
	while (client->active) {
		if (client->active->expiry > cur_time) {
			note("Trying recorded lease %s",
			    piaddr(client->active->address));
			/* Run the client script with the existing
			   parameters. */
			script_init("TIMEOUT",
			    client->active->medium);
			script_write_params("new_", client->active);
			if (client->alias)
				script_write_params("alias_",
				    client->alias);

			/* If the old lease is still good and doesn't
			   yet need renewal, go into BOUND state and
			   timeout at the renewal time. */
			if (!script_go()) {
				if (cur_time <
				    client->active->renewal) {
					client->state = S_BOUND;
					note("bound: renewal in %ld seconds.",
					    (long)(client->active->renewal -
					    cur_time));
					add_timeout(client->active->renewal,
					    state_bound);
				} else {
					client->state = S_BOUND;
					note("bound: immediate renewal.");
					state_bound();
				}
				reinitialize_interface();
				go_daemon();
				return;
			}
		}

		/* If there are no other leases, give up. */
		if (!client->leases) {
			client->leases = client->active;
			client->active = NULL;
			break;
		}

activate_next:
		/* Otherwise, put the active lease at the end of the
		   lease list, and try another lease.. */
		for (lp = client->leases; lp->next; lp = lp->next)
			;
		lp->next = client->active;
		if (lp->next)
			lp->next->next = NULL;
		client->active = client->leases;
		client->leases = client->leases->next;

		/* If we already tried this lease, we've exhausted the
		   set of leases, so we might as well give up for
		   now. */
		if (client->active == loop)
			break;
		else if (!loop)
			loop = client->active;
	}

	/* No leases were available, or what was available didn't work, so
	   tell the shell script that we failed to allocate an address,
	   and try again later. */
	note("No working leases in persistent database - sleeping.");
	script_init("FAIL", NULL);
	if (client->alias)
		script_write_params("alias_", client->alias);
	script_go();
	client->state = S_INIT;
	add_timeout(cur_time + config->retry_interval, state_init);
	go_daemon();
}

void
send_request(void)
{
	struct sockaddr_in destination;
	struct in_addr from;
	int interval;

	/* Figure out how long it's been since we started transmitting. */
	interval = cur_time - client->first_sending;

	/* If we're in the INIT-REBOOT or REQUESTING state and we're
	   past the reboot timeout, go to INIT and see if we can
	   DISCOVER an address... */
	/* XXX In the INIT-REBOOT state, if we don't get an ACK, it
	   means either that we're on a network with no DHCP server,
	   or that our server is down.  In the latter case, assuming
	   that there is a backup DHCP server, DHCPDISCOVER will get
	   us a new address, but we could also have successfully
	   reused our old address.  In the former case, we're hosed
	   anyway.  This is not a win-prone situation. */
	if ((client->state == S_REBOOTING ||
	    client->state == S_REQUESTING) &&
	    interval > config->reboot_timeout) {
cancel:
		client->state = S_INIT;
		cancel_timeout(send_request);
		state_init();
		return;
	}

	/* If we're in the reboot state, make sure the media is set up
	   correctly. */
	if (client->state == S_REBOOTING &&
	    !client->medium &&
	    client->active->medium) {
		script_init("MEDIUM", client->active->medium);

		/* If the medium we chose won't fly, go to INIT state. */
		if (script_go())
			goto cancel;

		/* Record the medium. */
		client->medium = client->active->medium;
	}

	/* If the lease has expired, relinquish the address and go back
	   to the INIT state. */
	if (client->state != S_REQUESTING &&
	    cur_time > client->active->expiry) {
		/* Run the client script with the new parameters. */
		script_init("EXPIRE", NULL);
		script_write_params("old_", client->active);
		if (client->alias)
			script_write_params("alias_", client->alias);
		script_go();

		/* Now do a preinit on the interface so that we can
		   discover a new address. */
		script_init("PREINIT", NULL);
		if (client->alias)
			script_write_params("alias_", client->alias);
		script_go();

		client->state = S_INIT;
		state_init();
		return;
	}

	/* Do the exponential backoff... */
	if (!client->interval)
		client->interval = config->initial_interval;
	else
		client->interval += ((arc4random() >> 2) %
		    (2 * client->interval));

	/* Don't backoff past cutoff. */
	if (client->interval > config->backoff_cutoff)
		client->interval = ((config->backoff_cutoff / 2) +
		    ((arc4random() >> 2) % client->interval));

	/* If the backoff would take us to the expiry time, just set the
	   timeout to the expiry time. */
	if (client->state != S_REQUESTING && cur_time + client->interval >
	    client->active->expiry)
		client->interval = client->active->expiry - cur_time + 1;

	/* If the lease T2 time has elapsed, or if we're not yet bound,
	   broadcast the DHCPREQUEST rather than unicasting. */
	memset(&destination, 0, sizeof(destination));
	if (client->state == S_REQUESTING ||
	    client->state == S_REBOOTING ||
	    cur_time > client->active->rebind)
		destination.sin_addr.s_addr = INADDR_BROADCAST;
	else
		memcpy(&destination.sin_addr.s_addr, client->destination.iabuf,
		    sizeof(destination.sin_addr.s_addr));
	destination.sin_port = htons(REMOTE_PORT);
	destination.sin_family = AF_INET;
	destination.sin_len = sizeof(destination);

	if (client->state != S_REQUESTING)
		memcpy(&from, client->active->address.iabuf, sizeof(from));
	else
		from.s_addr = INADDR_ANY;

	/* Record the number of seconds since we started sending. */
	if (client->state == S_REQUESTING)
		client->packet.secs = client->secs;
	else {
		if (interval < 65536)
			client->packet.secs = htons(interval);
		else
			client->packet.secs = htons(65535);
	}

	note("DHCPREQUEST on %s to %s port %d", ifi->name,
	    inet_ntoa(destination.sin_addr), ntohs(destination.sin_port));

	/* Send out a packet. */
	send_packet(from, &destination, NULL);

	add_timeout(cur_time + client->interval, send_request);
}

void
send_decline(void)
{
	note("DHCPDECLINE on %s to %s port %d", ifi->name,
	    inet_ntoa(sockaddr_broadcast.sin_addr),
	    ntohs(sockaddr_broadcast.sin_port));

	/* Send out a packet. */
	send_packet(inaddr_any, &sockaddr_broadcast, NULL);
}

void
make_discover(struct client_lease *lease)
{
	unsigned char discover = DHCPDISCOVER;
	struct option_data options[256];
	int i;

	memset(options, 0, sizeof(options));
	memset(&client->packet, 0, sizeof(client->packet));

	/* Set DHCP_MESSAGE_TYPE to DHCPDISCOVER */
	i = DHO_DHCP_MESSAGE_TYPE;
	options[i].data = &discover;
	options[i].len = sizeof(discover);

	/* Request the options we want */
	i  = DHO_DHCP_PARAMETER_REQUEST_LIST;
	options[i].data = config->requested_options;
	options[i].len = config->requested_option_count;

	/* If we had an address, try to get it again. */
	if (lease) {
		client->requested_address = lease->address;
		i = DHO_DHCP_REQUESTED_ADDRESS;
		options[i].data = lease->address.iabuf;
		options[i].len = lease->address.len;
	} else
		client->requested_address.len = 0;

	/* Send any options requested in the config file. */
	for (i = 0; i < 256; i++)
		if (!options[i].data &&
		    config->send_options[i].data) {
			options[i].data = config->send_options[i].data;
			options[i].len = config->send_options[i].len;
		}

	/* Set up the option buffer to fit in a minimal UDP packet. */
	i = cons_options(client->packet.options, 576 - DHCP_FIXED_LEN,
	    options);
	if (i == -1 || client->packet.options[i] != DHO_END)
		error("options do not fit in DHCPDISCOVER packet.");
	client->packet_length = DHCP_FIXED_NON_UDP+i+1;
	if (client->packet_length < BOOTP_MIN_LEN)
		client->packet_length = BOOTP_MIN_LEN;

	client->packet.op = BOOTREQUEST;
	client->packet.htype = ifi->hw_address.htype;
	client->packet.hlen = ifi->hw_address.hlen;
	client->packet.hops = 0;
	client->packet.xid = arc4random();
	client->packet.secs = 0; /* filled in by send_discover. */
	client->packet.flags = 0;

	memset(&client->packet.ciaddr, 0, sizeof(client->packet.ciaddr));
	memset(&client->packet.yiaddr, 0, sizeof(client->packet.yiaddr));
	memset(&client->packet.siaddr, 0, sizeof(client->packet.siaddr));
	memset(&client->packet.giaddr, 0, sizeof(client->packet.giaddr));
	memcpy(client->packet.chaddr, ifi->hw_address.haddr,
	    ifi->hw_address.hlen);
}

void
make_request(struct client_lease * lease)
{
	unsigned char request = DHCPREQUEST;
	struct option_data options[256];
	int i;

	memset(options, 0, sizeof(options));
	memset(&client->packet, 0, sizeof(client->packet));

	/* Set DHCP_MESSAGE_TYPE to DHCPREQUEST */
	i = DHO_DHCP_MESSAGE_TYPE;
	options[i].data = &request;
	options[i].len = sizeof(request);

	/* Request the options we want */
	i = DHO_DHCP_PARAMETER_REQUEST_LIST;
	options[i].data = config->requested_options;
	options[i].len = config->requested_option_count;

	/* If we are requesting an address that hasn't yet been assigned
	   to us, use the DHCP Requested Address option. */
	if (client->state == S_REQUESTING) {
		/* Send back the server identifier... */
		i = DHO_DHCP_SERVER_IDENTIFIER;
		options[i].data = lease->options[i].data;
		options[i].len = lease->options[i].len;
	}
	if (client->state == S_REQUESTING ||
	    client->state == S_REBOOTING) {
		client->requested_address = lease->address;
		i = DHO_DHCP_REQUESTED_ADDRESS;
		options[i].data = lease->address.iabuf;
		options[i].len = lease->address.len;
	} else
		client->requested_address.len = 0;

	/* Send any options requested in the config file. */
	for (i = 0; i < 256; i++)
		if (!options[i].data && config->send_options[i].data) {
			options[i].data = config->send_options[i].data;
			options[i].len = config->send_options[i].len;
		}

	/* Set up the option buffer to fit in a minimal UDP packet. */
	i = cons_options(client->packet.options, 576 - DHCP_FIXED_LEN,
	    options);
	if (i == -1 || client->packet.options[i] != DHO_END)
		error("options do not fit in DHCPREQUEST packet.");
	client->packet_length = DHCP_FIXED_NON_UDP+i+1;
	if (client->packet_length < BOOTP_MIN_LEN)
		client->packet_length = BOOTP_MIN_LEN;

	client->packet.op = BOOTREQUEST;
	client->packet.htype = ifi->hw_address.htype;
	client->packet.hlen = ifi->hw_address.hlen;
	client->packet.hops = 0;
	client->packet.xid = client->xid;
	client->packet.secs = 0; /* Filled in by send_request. */
	client->packet.flags = 0;

	/* If we own the address we're requesting, put it in ciaddr;
	   otherwise set ciaddr to zero. */
	if (client->state == S_BOUND ||
	    client->state == S_RENEWING ||
	    client->state == S_REBINDING) {
		memcpy(&client->packet.ciaddr,
		    lease->address.iabuf, lease->address.len);
	} else {
		memset(&client->packet.ciaddr, 0,
		    sizeof(client->packet.ciaddr));
	}

	memset(&client->packet.yiaddr, 0, sizeof(client->packet.yiaddr));
	memset(&client->packet.siaddr, 0, sizeof(client->packet.siaddr));
	memset(&client->packet.giaddr, 0, sizeof(client->packet.giaddr));
	memcpy(client->packet.chaddr, ifi->hw_address.haddr,
	    ifi->hw_address.hlen);
}

void
make_decline(struct client_lease *lease)
{
	struct option_data options[256];
	unsigned char decline = DHCPDECLINE;
	int i;

	memset(options, 0, sizeof(options));
	memset(&client->packet, 0, sizeof(client->packet));

	/* Set DHCP_MESSAGE_TYPE to DHCPDECLINE */
	i = DHO_DHCP_MESSAGE_TYPE;
	options[i].data = &decline;
	options[i].len = sizeof(decline);

	/* Send back the server identifier... */
	i = DHO_DHCP_SERVER_IDENTIFIER;
	options[i].data = lease->options[i].data;
	options[i].len = lease->options[i].len;

	/* Send back the address we're declining. */
	i = DHO_DHCP_REQUESTED_ADDRESS;
	options[i].data = lease->address.iabuf;
	options[i].len = lease->address.len;

	/* Send the uid if the user supplied one. */
	i = DHO_DHCP_CLIENT_IDENTIFIER;
	if (config->send_options[i].len) {
		options[i].data = config->send_options[i].data;
		options[i].len = config->send_options[i].len;
	}

	/* Set up the option buffer to fit in a minimal UDP packet. */
	i = cons_options(client->packet.options, 576 - DHCP_FIXED_LEN,
	    options);
	if (i == -1 || client->packet.options[i] != DHO_END)
		error("options do not fit in DHCPDECLINE packet.");
	client->packet_length = DHCP_FIXED_NON_UDP+i+1;
	if (client->packet_length < BOOTP_MIN_LEN)
		client->packet_length = BOOTP_MIN_LEN;

	client->packet.op = BOOTREQUEST;
	client->packet.htype = ifi->hw_address.htype;
	client->packet.hlen = ifi->hw_address.hlen;
	client->packet.hops = 0;
	client->packet.xid = client->xid;
	client->packet.secs = 0; /* Filled in by send_request. */
	client->packet.flags = 0;

	/* ciaddr must always be zero. */
	memset(&client->packet.ciaddr, 0, sizeof(client->packet.ciaddr));
	memset(&client->packet.yiaddr, 0, sizeof(client->packet.yiaddr));
	memset(&client->packet.siaddr, 0, sizeof(client->packet.siaddr));
	memset(&client->packet.giaddr, 0, sizeof(client->packet.giaddr));
	memcpy(client->packet.chaddr, ifi->hw_address.haddr,
	    ifi->hw_address.hlen);
}

void
free_client_lease(struct client_lease *lease)
{
	int i;

	if (lease->server_name)
		free(lease->server_name);
	if (lease->filename)
		free(lease->filename);
	for (i = 0; i < 256; i++) {
		if (lease->options[i].len)
			free(lease->options[i].data);
	}
	free(lease);
}

FILE *leaseFile;

void
rewrite_client_leases(void)
{
	struct client_lease *lp;

	if (!leaseFile) {
		leaseFile = fopen(path_dhclient_db, "w");
		if (!leaseFile)
			error("can't create %s: %m", path_dhclient_db);
	} else {
		fflush(leaseFile);
		rewind(leaseFile);
	}

	for (lp = client->leases; lp; lp = lp->next)
		write_client_lease(lp, 1);
	if (client->active)
		write_client_lease(client->active, 1);

	fflush(leaseFile);
	ftruncate(fileno(leaseFile), ftello(leaseFile));
	fsync(fileno(leaseFile));
}

void
write_client_lease(struct client_lease *lease, int rewrite)
{
	static int leases_written;
	struct tm *t;
	int i;

	if (!rewrite) {
		if (leases_written++ > 20) {
			rewrite_client_leases();
			leases_written = 0;
		}
	}

	/* If the lease came from the config file, we don't need to stash
	   a copy in the lease database. */
	if (lease->is_static)
		return;

	if (!leaseFile) {	/* XXX */
		leaseFile = fopen(path_dhclient_db, "w");
		if (!leaseFile)
			error("can't create %s: %m", path_dhclient_db);
	}

	fprintf(leaseFile, "lease {\n");
	if (lease->is_bootp)
		fprintf(leaseFile, "  bootp;\n");
	fprintf(leaseFile, "  interface \"%s\";\n", ifi->name);
	fprintf(leaseFile, "  fixed-address %s;\n", piaddr(lease->address));
	if (lease->filename)
		fprintf(leaseFile, "  filename \"%s\";\n", lease->filename);
	if (lease->server_name)
		fprintf(leaseFile, "  server-name \"%s\";\n",
		    lease->server_name);
	if (lease->medium)
		fprintf(leaseFile, "  medium \"%s\";\n", lease->medium->string);
	for (i = 0; i < 256; i++)
		if (lease->options[i].len)
			fprintf(leaseFile, "  option %s %s;\n",
			    dhcp_options[i].name,
			    pretty_print_option(i, lease->options[i].data,
			    lease->options[i].len, 1, 1));

	t = gmtime(&lease->renewal);
	fprintf(leaseFile, "  renew %d %d/%d/%d %02d:%02d:%02d;\n",
	    t->tm_wday, (int)t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	    t->tm_hour, t->tm_min, t->tm_sec);
	t = gmtime(&lease->rebind);
	fprintf(leaseFile, "  rebind %d %d/%d/%d %02d:%02d:%02d;\n",
	    t->tm_wday, (int)t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	    t->tm_hour, t->tm_min, t->tm_sec);
	t = gmtime(&lease->expiry);
	fprintf(leaseFile, "  expire %d %d/%d/%d %02d:%02d:%02d;\n",
	    t->tm_wday, (int)t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	    t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(leaseFile, "}\n");
	fflush(leaseFile);
}

void
script_init(char *reason, struct string_list *medium)
{
	size_t		 len, mediumlen = 0;
	struct imsg_hdr	 hdr;
	struct buf	*buf;

	if (medium != NULL && medium->string != NULL)
		mediumlen = strlen(medium->string);

	hdr.code = IMSG_SCRIPT_INIT;
	hdr.len = sizeof(struct imsg_hdr) +
	    sizeof(size_t) + mediumlen +
	    sizeof(size_t) + strlen(reason);

	buf = buf_open(hdr.len);

	buf_add(buf, &hdr, sizeof(hdr));
	buf_add(buf, &mediumlen, sizeof(mediumlen));
	if (mediumlen > 0)
		buf_add(buf, medium->string, mediumlen);
	len = strlen(reason);
	buf_add(buf, &len, sizeof(len));
	buf_add(buf, reason, len);

	buf_close(privfd, buf);
}

void
priv_script_init(char *reason, char *medium)
{
	client->scriptEnvsize = 100;
	if (client->scriptEnv == NULL)
		client->scriptEnv =
		    malloc(client->scriptEnvsize * sizeof(char *));
	if (client->scriptEnv == NULL)
		error("script_init: no memory for environment");

	client->scriptEnv[0] = strdup(CLIENT_PATH);
	if (client->scriptEnv[0] == NULL)
		error("script_init: no memory for environment");

	client->scriptEnv[1] = NULL;

	script_set_env("", "interface", ifi->name);

	if (medium)
		script_set_env("", "medium", medium);

	script_set_env("", "reason", reason);
}

void
priv_script_write_params(char *prefix, struct client_lease *lease)
{
	u_int8_t dbuf[1500];
	int i, len = 0;
	char tbuf[128];

	script_set_env(prefix, "ip_address", piaddr(lease->address));

	if (lease->options[DHO_SUBNET_MASK].len &&
	    (lease->options[DHO_SUBNET_MASK].len <
	    sizeof(lease->address.iabuf))) {
		struct iaddr netmask, subnet, broadcast;

		memcpy(netmask.iabuf, lease->options[DHO_SUBNET_MASK].data,
		    lease->options[DHO_SUBNET_MASK].len);
		netmask.len = lease->options[DHO_SUBNET_MASK].len;

		subnet = subnet_number(lease->address, netmask);
		if (subnet.len) {
			script_set_env(prefix, "network_number",
			    piaddr(subnet));
			if (!lease->options[DHO_BROADCAST_ADDRESS].len) {
				broadcast = broadcast_addr(subnet, netmask);
				if (broadcast.len)
					script_set_env(prefix,
					    "broadcast_address",
					    piaddr(broadcast));
			}
		}
	}

	if (lease->filename)
		script_set_env(prefix, "filename", lease->filename);
	if (lease->server_name)
		script_set_env(prefix, "server_name",
		    lease->server_name);
	for (i = 0; i < 256; i++) {
		u_int8_t *dp = NULL;

		if (config->defaults[i].len) {
			if (lease->options[i].len) {
				switch (config->default_actions[i]) {
				case ACTION_DEFAULT:
					dp = lease->options[i].data;
					len = lease->options[i].len;
					break;
				case ACTION_SUPERSEDE:
supersede:
					dp = config->defaults[i].data;
					len = config->defaults[i].len;
					break;
				case ACTION_PREPEND:
					len = config->defaults[i].len +
					    lease->options[i].len;
					if (len > sizeof(dbuf)) {
						warning("no space to %s %s",
						    "prepend option",
						    dhcp_options[i].name);
						goto supersede;
					}
					dp = dbuf;
					memcpy(dp,
					    config->defaults[i].data,
					    config->defaults[i].len);
					memcpy(dp +
					    config->defaults[i].len,
					    lease->options[i].data,
					    lease->options[i].len);
					dp[len] = '\0';
					break;
				case ACTION_APPEND:
					len = config->defaults[i].len +
					    lease->options[i].len;
					if (len > sizeof(dbuf)) {
						warning("no space to %s %s",
						    "append option",
						    dhcp_options[i].name);
						goto supersede;
					}
					dp = dbuf;
					memcpy(dp, lease->options[i].data,
					    lease->options[i].len);
					memcpy(dp + lease->options[i].len,
					    config->defaults[i].data,
					    config->defaults[i].len);
					dp[len] = '\0';
				}
			} else {
				dp = config->defaults[i].data;
				len = config->defaults[i].len;
			}
		} else if (lease->options[i].len) {
			len = lease->options[i].len;
			dp = lease->options[i].data;
		} else {
			len = 0;
		}
		if (len) {
			char name[256];

			if (dhcp_option_ev_name(name, sizeof(name),
			    &dhcp_options[i]))
				script_set_env(prefix, name,
				    pretty_print_option(i, dp, len, 0, 0));
		}
	}
	snprintf(tbuf, sizeof(tbuf), "%d", (int)lease->expiry);
	script_set_env(prefix, "expiry", tbuf);
}

void
script_write_params(char *prefix, struct client_lease *lease)
{
	size_t		 fn_len = 0, sn_len = 0, pr_len = 0;
	struct imsg_hdr	 hdr;
	struct buf	*buf;
	int		 i;

	if (lease->filename != NULL)
		fn_len = strlen(lease->filename);
	if (lease->server_name != NULL)
		sn_len = strlen(lease->server_name);
	if (prefix != NULL)
		pr_len = strlen(prefix);

	hdr.code = IMSG_SCRIPT_WRITE_PARAMS;
	hdr.len = sizeof(hdr) + sizeof(struct client_lease) +
	    sizeof(size_t) + fn_len + sizeof(size_t) + sn_len +
	    sizeof(size_t) + pr_len;

	for (i = 0; i < 256; i++)
		hdr.len += sizeof(int) + lease->options[i].len;

	scripttime = time(NULL);

	buf = buf_open(hdr.len);

	buf_add(buf, &hdr, sizeof(hdr));
	buf_add(buf, lease, sizeof(struct client_lease));
	buf_add(buf, &fn_len, sizeof(fn_len));
	buf_add(buf, lease->filename, fn_len);
	buf_add(buf, &sn_len, sizeof(sn_len));
	buf_add(buf, lease->server_name, sn_len);
	buf_add(buf, &pr_len, sizeof(pr_len));
	buf_add(buf, prefix, pr_len);

	for (i = 0; i < 256; i++) {
		buf_add(buf, &lease->options[i].len,
		    sizeof(lease->options[i].len));
		buf_add(buf, lease->options[i].data,
		    lease->options[i].len);
	}

	buf_close(privfd, buf);
}

int
script_go(void)
{
	struct imsg_hdr	 hdr;
	struct buf	*buf;
	int		 ret;

	scripttime = time(NULL);

	hdr.code = IMSG_SCRIPT_GO;
	hdr.len = sizeof(struct imsg_hdr);

	buf = buf_open(hdr.len);

	buf_add(buf, &hdr, sizeof(hdr));
	buf_close(privfd, buf);

	bzero(&hdr, sizeof(hdr));
	buf_read(privfd, &hdr, sizeof(hdr));
	if (hdr.code != IMSG_SCRIPT_GO_RET)
		error("unexpected msg type %u", hdr.code);
	if (hdr.len != sizeof(hdr) + sizeof(int))
		error("received corrupted message");
	buf_read(privfd, &ret, sizeof(ret));

	return (ret);
}

int
priv_script_go(void)
{
	char *scriptName, *argv[2], **envp;
	int pid, wpid, wstatus;

	scripttime = time(NULL);

	scriptName = config->script_name;
	envp = client->scriptEnv;

	argv[0] = scriptName;
	argv[1] = NULL;

	pid = fork();
	if (pid < 0) {
		error("fork: %m");
		wstatus = 0;
	} else if (pid) {
		do {
			wpid = wait(&wstatus);
		} while (wpid != pid && wpid > 0);
		if (wpid < 0) {
			error("wait: %m");
			wstatus = 0;
		}
	} else {
		execve(scriptName, argv, envp);
		error("execve (%s, ...): %m", scriptName);
	}

	script_flush_env();

	return (wstatus & 0xff);
}

void
script_set_env(const char *prefix, const char *name, const char *value)
{
	int i, j, namelen;

	namelen = strlen(name);

	for (i = 0; client->scriptEnv[i]; i++)
		if (strncmp(client->scriptEnv[i], name, namelen) == 0 &&
		    client->scriptEnv[i][namelen] == '=')
			break;

	if (client->scriptEnv[i])
		/* Reuse the slot. */
		free(client->scriptEnv[i]);
	else {
		/* New variable.  Expand if necessary. */
		if (i >= client->scriptEnvsize - 1) {
			char **newscriptEnv;
			int newscriptEnvsize = client->scriptEnvsize + 50;

			newscriptEnv = realloc(client->scriptEnv,
			    newscriptEnvsize);
			if (newscriptEnv == NULL) {
				free(client->scriptEnv);
				client->scriptEnv = NULL;
				client->scriptEnvsize = 0;
				error("script_set_env: no memory for variable");
			}
			client->scriptEnv = newscriptEnv;
			client->scriptEnvsize = newscriptEnvsize;
		}
		/* need to set the NULL pointer at end of array beyond
		   the new slot. */
		client->scriptEnv[i + 1] = NULL;
	}
	/* Allocate space and format the variable in the appropriate slot. */
	client->scriptEnv[i] = malloc(strlen(prefix) + strlen(name) + 1 +
	    strlen(value) + 1);
	if (client->scriptEnv[i] == NULL)
		error("script_set_env: no memory for variable assignment");

	/* No `` or $() command substitution allowed in environment values! */
	for (j = 0; j < strlen(value); j++)
		switch (value[j]) {
		case '`':
		case '$':
			error("illegal character (%c) in value '%s'", value[j],
			    value);
			/* not reached */
		}
	snprintf(client->scriptEnv[i], strlen(prefix) + strlen(name) +
	    1 + strlen(value) + 1, "%s%s=%s", prefix, name, value);
}

void
script_flush_env(void)
{
	int i;

	for (i = 0; client->scriptEnv[i]; i++) {
		free(client->scriptEnv[i]);
		client->scriptEnv[i] = NULL;
	}
	client->scriptEnvsize = 0;
}

int
dhcp_option_ev_name(char *buf, size_t buflen, const struct option *option)
{
	int i;

	for (i = 0; option->name[i]; i++) {
		if (i + 1 == buflen)
			return 0;
		if (option->name[i] == '-')
			buf[i] = '_';
		else
			buf[i] = option->name[i];
	}

	buf[i] = 0;
	return 1;
}

void
go_daemon(void)
{
	static int state = 0;

	if (no_daemon || state)
		return;

	state = 1;

	/* Stop logging to stderr... */
	log_perror = 0;

	if (daemon(1, 0) == -1)
		error("daemon");

	/* we are chrooted, daemon(3) fails to open /dev/null */
	if (nullfd != -1) {
		dup2(nullfd, STDIN_FILENO);
		dup2(nullfd, STDOUT_FILENO);
		dup2(nullfd, STDERR_FILENO);
		close(nullfd);
		nullfd = -1;
	}
}

int
check_option(struct client_lease *l, int option)
{
	char *opbuf;
	char *sbuf;

	/* we use this, since this is what gets passed to dhclient-script */

	opbuf = pretty_print_option(option, l->options[option].data,
	    l->options[option].len, 0, 0);

	sbuf = option_as_string(option, l->options[option].data,
	    l->options[option].len);

	switch (option) {
	case DHO_SUBNET_MASK:
	case DHO_TIME_SERVERS:
	case DHO_NAME_SERVERS:
	case DHO_ROUTERS:
	case DHO_DOMAIN_NAME_SERVERS:
	case DHO_LOG_SERVERS:
	case DHO_COOKIE_SERVERS:
	case DHO_LPR_SERVERS:
	case DHO_IMPRESS_SERVERS:
	case DHO_RESOURCE_LOCATION_SERVERS:
	case DHO_SWAP_SERVER:
	case DHO_BROADCAST_ADDRESS:
	case DHO_NIS_SERVERS:
	case DHO_NTP_SERVERS:
	case DHO_NETBIOS_NAME_SERVERS:
	case DHO_NETBIOS_DD_SERVER:
	case DHO_FONT_SERVERS:
	case DHO_DHCP_SERVER_IDENTIFIER:
		if (!ipv4addrs(opbuf)) {
			warning("Invalid IP address in option: %s", opbuf);
			return (0);
		}
		return (1);
	case DHO_HOST_NAME:
	case DHO_DOMAIN_NAME:
	case DHO_NIS_DOMAIN:
		if (!res_hnok(sbuf, option == DHO_DOMAIN_NAME)) {
			warning("Bogus Host Name option %d: %s (%s)", option,
			    sbuf, opbuf);
			l->options[option].len = 0;
			free(l->options[option].data);
		}
		return (1);
	case DHO_PAD:
	case DHO_TIME_OFFSET:
	case DHO_BOOT_SIZE:
	case DHO_MERIT_DUMP:
	case DHO_ROOT_PATH:
	case DHO_EXTENSIONS_PATH:
	case DHO_IP_FORWARDING:
	case DHO_NON_LOCAL_SOURCE_ROUTING:
	case DHO_POLICY_FILTER:
	case DHO_MAX_DGRAM_REASSEMBLY:
	case DHO_DEFAULT_IP_TTL:
	case DHO_PATH_MTU_AGING_TIMEOUT:
	case DHO_PATH_MTU_PLATEAU_TABLE:
	case DHO_INTERFACE_MTU:
	case DHO_ALL_SUBNETS_LOCAL:
	case DHO_PERFORM_MASK_DISCOVERY:
	case DHO_MASK_SUPPLIER:
	case DHO_ROUTER_DISCOVERY:
	case DHO_ROUTER_SOLICITATION_ADDRESS:
	case DHO_STATIC_ROUTES:
	case DHO_TRAILER_ENCAPSULATION:
	case DHO_ARP_CACHE_TIMEOUT:
	case DHO_IEEE802_3_ENCAPSULATION:
	case DHO_DEFAULT_TCP_TTL:
	case DHO_TCP_KEEPALIVE_INTERVAL:
	case DHO_TCP_KEEPALIVE_GARBAGE:
	case DHO_VENDOR_ENCAPSULATED_OPTIONS:
	case DHO_NETBIOS_NODE_TYPE:
	case DHO_NETBIOS_SCOPE:
	case DHO_X_DISPLAY_MANAGER:
	case DHO_DHCP_REQUESTED_ADDRESS:
	case DHO_DHCP_LEASE_TIME:
	case DHO_DHCP_OPTION_OVERLOAD:
	case DHO_DHCP_MESSAGE_TYPE:
	case DHO_DHCP_PARAMETER_REQUEST_LIST:
	case DHO_DHCP_MESSAGE:
	case DHO_DHCP_MAX_MESSAGE_SIZE:
	case DHO_DHCP_RENEWAL_TIME:
	case DHO_DHCP_REBINDING_TIME:
	case DHO_DHCP_CLASS_IDENTIFIER:
	case DHO_DHCP_CLIENT_IDENTIFIER:
	case DHO_DHCP_USER_CLASS_ID:
	case DHO_END:
		return (1);
	default:
		warning("unknown dhcp option value 0x%x", option);
		return (unknown_ok);
	}
}

int
res_hnok(const char *name, bool wsp_ok)
{
	const char *dn = name;
	int pch = '.', ch = *dn++;
	bool warn_us = false, warn_sp = false;
	const char *warntext = NULL;

	while (ch != '\0') {
		int nch = *dn++;

		if (ch == ' ' || ch == '\t') {
			ch = '.';	/* reset to initial state */
			if (!warn_sp) {
				warntext = "whitespace";
				warn_sp = true;
			}
		} else if (ch == '.') {
			;
		} else if (pch == '.' || nch == '.' || nch == '\0') {
			if (!isalnum(ch))
				return (0);
		} else if (!isalnum(ch) && ch != '-' && ch != '_')
				return (0);
		else if (ch == '_' && !warn_us) {
			warn_us = true;
			warntext = "an underscore";
		}
		if (warntext) {
			warning("warning: hostname %s contains %s "
			    "which violates RFC 952", name, warntext);
			warntext = NULL;
		}
		pch = ch, ch = nch;
	}
	return (1);
}

/* Does buf consist only of dotted decimal ipv4 addrs?
 * return how many if so,
 * otherwise, return 0
 */
int
ipv4addrs(char * buf)
{
	struct in_addr jnk;
	int count = 0;

	while (inet_aton(buf, &jnk) == 1){
		count++;
		while (*buf == '.' || isdigit(*buf))
			buf++;
		if (*buf == '\0')
			return (count);
		while (*buf ==  ' ')
			buf++;
	}
	return (0);
}

char *
option_as_string(unsigned int code, unsigned char *data, int len)
{
	static char optbuf[32768]; /* XXX */
	char *op = optbuf;
	int opleft = sizeof(optbuf);
	unsigned char *dp = data;

	if (code > 255)
		error("option_as_string: bad code %d", code);

	for (; dp < data + len; dp++) {
		if (!isascii(*dp) || !isprint(*dp)) {
			if (dp + 1 != data + len || *dp != 0) {
				snprintf(op, opleft, "\\%03o", *dp);
				op += 4;
				opleft -= 4;
			}
		} else if (*dp == '"' || *dp == '\'' || *dp == '$' ||
		    *dp == '`' || *dp == '\\') {
			*op++ = '\\';
			*op++ = *dp;
			opleft -= 2;
		} else {
			*op++ = *dp;
			opleft--;
		}
	}
	if (opleft < 1)
		goto toobig;
	*op = 0;
	return optbuf;
toobig:
	warning("dhcp option too large");
	return "<error>";
}

int
fork_privchld(int fd, int fd2)
{
	struct pollfd pfd[1];
	int nfds;

	switch (fork()) {
	case -1:
		error("cannot fork");
		break;
	case 0:
		break;
	default:
		return (0);
	}

	if (chdir("/") == -1)
		error("chdir(\"/\")");

	setproctitle("%s [priv]", ifi->name);

	dup2(nullfd, STDIN_FILENO);
	dup2(nullfd, STDOUT_FILENO);
	dup2(nullfd, STDERR_FILENO);
	close(nullfd);
	close(fd2);

	for (;;) {
		pfd[0].fd = fd;
		pfd[0].events = POLLIN;
		if ((nfds = poll(pfd, 1, INFTIM)) == -1)
			if (errno != EINTR)
				error("poll error");

		if (nfds == 0 || !(pfd[0].revents & POLLIN))
			continue;

		dispatch_imsg(fd);
	}
}
