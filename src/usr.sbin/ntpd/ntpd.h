/**	$MirOS: src/usr.sbin/ntpd/ntpd.h,v 1.20 2011/01/30 03:06:04 tg Exp $ */
/*	$OpenBSD: ntpd.h,v 1.70 2006/06/04 18:58:13 otto Exp $ */

/*
 * Copyright (c) 2007, 2008, 2009, 2011 Thorsten Glaser <tg@mirbsd.org>
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
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/queue.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdbool.h>

#include "ntp.h"

#define	NTPD_USER	"_ntp"
#define	CONFFILE	"/etc/ntpd.conf"

#define	READ_BUF_SIZE		4096

#define	NTPD_OPT_VERBOSE	0x0001
#define	NTPD_OPT_VERBOSE2	0x0002

#define	INTERVAL_QUERY_NORMAL		30	/* sync to peers every n secs */
#define	INTERVAL_QUERY_PATHETIC		60
#define	INTERVAL_QUERY_AGRESSIVE	5

#define	TRUSTLEVEL_BADPEER		6
#define	TRUSTLEVEL_PATHETIC		2
#define	TRUSTLEVEL_AGRESSIVE		8
#define	TRUSTLEVEL_MAX			10
#define	TRUSTLEVEL_RESET		(TRUSTLEVEL_AGRESSIVE - 1)

#define	MAX_SERVERS_DNS			8

#define	QSCALE_OFF_MIN			0.05
#define	QSCALE_OFF_MAX			0.50

#define	QUERYTIME_MAX		15	/* single query might take n secs max */
#define	OFFSET_ARRAY_SIZE	4	/* min. 3, recommended 6, max. 8 */
#define	SETTIME_MIN_OFFSET	180	/* min offset for settime at start */
#define	SETTIME_TIMEOUT		15	/* max seconds to wait with -s */
#define	LOG_NEGLIGEE		125	/* negligible drift to not log (ms) */

/**
 * While various sources state that the delay can never be negative,
 * here is an example where it actually can be, with good reason:
 *
 * Assume an NTP server with a low- to medium precision clock (for
 * purposes of this example, we assume 10 ms), and an NTP client
 * with a high-precision clock. Assume they sit on a LAN which has
 * a transaction time of 1 ms. They are 100 ms apart initially. We
 * can observe the following sample values over two requests with
 * no adjustment applied in between:
 *
 *		Request 1	Request 2	Comment
 * T1		1000		2000
 * T2		1101		2101		In Req2, a tick increasement
 * T3		1101		2111		happens between T2 and T3
 * T4		1002		2002
 *
 * This leaves us with the following results:
 * Req1:	d =  2		t = 100		v =  2
 * Req2:	d = -8		t = 105		v = -8
 *
 * According to Mark Martinec, the true delay can only be observed
 * by averaging delays, including negative ones. However, if one end
 * is a VM or another low-resolution device, and the other end has
 * a HPET or similar, chances are that most replies have negative
 * delays. For this reason, MirBSD OpenNTPD 2009-12-24 ignores delays
 * below DELAY_NEGLIGEE which defaults to 10 ms (keep it over 1 ms to
 * accomodate systems without sub-millisecond precision), as most sy-
 * stems use 100 Hz ticks; set to 0 to revert to the previous behaviour.
 */
#define DELAY_NEGLIGEE	(-0.010)	/* minimum xfer delay accepted */


enum client_state {
	STATE_NONE,
	STATE_DNS_INPROGRESS,
	STATE_DNS_TEMPFAIL,
	STATE_DNS_DONE,
	STATE_QUERY_SENT,
	STATE_REPLY_RECEIVED
};

struct listen_addr {
	TAILQ_ENTRY(listen_addr)	 entry;
	struct sockaddr_storage		 sa;
	int				 fd;
};

struct ntp_addr {
	struct ntp_addr		*next;
	struct sockaddr_storage	 ss;
};

struct ntp_addr_wrap {
	char			*name;
	struct ntp_addr		*a;
	u_int8_t		 pool;
};

struct ntp_status {
	double		rootdelay;
	double		rootdispersion;
	double		reftime;
	u_int32_t	refid;
	u_int32_t	refid4;
	u_int8_t	synced;
	u_int8_t	leap;
	int8_t		precision;
	u_int8_t	poll;
	u_int8_t	stratum;
};

struct ntp_offset {
	struct ntp_status	status;
	double			offset;
	double			delay;
	double			error;
	time_t			rcvd;
	int			good;
};

struct ntp_peer {
	TAILQ_ENTRY(ntp_peer)		 entry;
	struct ntp_addr_wrap		 addr_head;
	struct ntp_addr			*addr;
	struct ntp_query		*query;
	struct ntp_offset		 reply[OFFSET_ARRAY_SIZE];
	struct ntp_offset		 update;
	time_t				 next;
	time_t				 deadline;
	int				 lasterror;
	enum client_state		 state;
	u_int32_t			 id;
	u_int8_t			 shift;
	u_int8_t			 trustlevel;
	u_int8_t			 stratum_offset;
};

struct ntpd_conf {
	TAILQ_HEAD(listen_addrs, listen_addr)	listen_addrs;
	TAILQ_HEAD(ntp_peers, ntp_peer)		ntp_peers;
	struct ntp_status			status;
	u_int32_t				scale;
	u_int8_t				listen_all;
	u_int8_t				settime;
	u_int8_t				debug;
	u_int8_t				trace;
};

struct buf {
	TAILQ_ENTRY(buf)	 entry;
	u_char			*buf;
	size_t			 size;
	size_t			 wpos;
	size_t			 rpos;
};

struct msgbuf {
	TAILQ_HEAD(, buf)	 bufs;
	u_int32_t		 queued;
	int			 fd;
};

struct buf_read {
	size_t			 wpos;
	u_char			 buf[READ_BUF_SIZE];
	u_char			*rptr;
};

/* ipc messages */

#define	IMSG_HEADER_SIZE	sizeof(struct imsg_hdr)
#define	MAX_IMSGSIZE		8192

struct imsgbuf {
	int			fd;
	pid_t			pid;
	struct buf_read		r;
	struct msgbuf		w;
};

enum imsg_type {
	IMSG_NONE,
	IMSG_RESET,
	IMSG_ADJTIME,
	IMSG_SETTIME,
	IMSG_HOST_DNS
};

struct imsg_hdr {
	enum imsg_type	type;
	u_int32_t	peerid;
	pid_t		pid;
	u_int16_t	len;
};

struct imsg {
	struct imsg_hdr	 hdr;
	void		*data;
};

/* prototypes */
/* log.c */
void		 log_init(int);
void		 vlog(int, const char *, va_list)
    __attribute__((format (syslog, 2, 0)))
    __attribute__((format (printf, 2, 0)))
    __attribute__((nonnull (2)));
void		 log_warn(const char *, ...)
    __attribute__((format (syslog, 1, 2)))
    __attribute__((format (printf, 1, 2)))
    __attribute__((nonnull (1)));
void		 log_warnx(const char *, ...)
    __attribute__((format (syslog, 1, 2)))
    __attribute__((format (printf, 1, 2)))
    __attribute__((nonnull (1)));
void		 log_info(const char *, ...)
    __attribute__((format (syslog, 1, 2)))
    __attribute__((format (printf, 1, 2)))
    __attribute__((nonnull (1)));
void		 log_debug(const char *, ...)
    __attribute__((format (syslog, 1, 2)))
    __attribute__((format (printf, 1, 2)))
    __attribute__((nonnull (1)));
__dead void	 fatal(const char *);
__dead void	 fatalx(const char *);

/* buffer.c */
struct buf	*buf_open(size_t);
int		 buf_add(struct buf *, void *, size_t);
int		 buf_close(struct msgbuf *, struct buf *);
void		 buf_free(struct buf *);
void		 msgbuf_init(struct msgbuf *);
void		 msgbuf_clear(struct msgbuf *);
int		 msgbuf_write(struct msgbuf *);

/* imsg.c */
void	 imsg_init(struct imsgbuf *, int);
int	 imsg_read(struct imsgbuf *);
int	 imsg_get(struct imsgbuf *, struct imsg *);
int	 imsg_compose(struct imsgbuf *, enum imsg_type, u_int32_t, pid_t,
	    void *, u_int16_t);
struct buf	*imsg_create(struct imsgbuf *, enum imsg_type, u_int32_t, pid_t,
		    u_int16_t);
int	 imsg_add(struct buf *, void *, u_int16_t);
int	 imsg_close(struct imsgbuf *, struct buf *);
void	 imsg_free(struct imsg *);

/* ntp.c */
pid_t	 ntp_main(int[2], struct ntpd_conf *);
int	 priv_adjtime(void);
void	 priv_settime(double);
void	 priv_host_dns(char *, u_int32_t);
void	 chpeertrust(struct ntp_peer *, bool);

/* parse.y */
int	 parse_config(const char *, struct ntpd_conf *);

/* config.c */
int		 host(const char *, struct ntp_addr **);
int		 host_dns(const char *, struct ntp_addr **);
struct ntp_peer	*new_peer(void);

/* ntp_msg.c */
int	ntp_getmsg(struct sockaddr *, char *, ssize_t, struct ntp_msg *);
int	ntp_sendmsg(int, struct sockaddr *, struct ntp_msg *, ssize_t, int);

/* server.c */
int	setup_listeners(struct servent *, struct ntpd_conf *, u_int *);
int	ntp_reply(int, struct sockaddr *, struct ntp_msg *, int);
int	server_dispatch(int, struct ntpd_conf *);

/* client.c */
int	client_peer_init(struct ntp_peer *);
int	client_addr_init(struct ntp_peer *);
int	client_nextaddr(struct ntp_peer *);
int	client_query(struct ntp_peer *);
int	client_dispatch(struct ntp_peer *, u_int8_t, uint8_t);
void	client_log_error(struct ntp_peer *, const char *, int);
void	update_scale(double);
time_t	scale_interval(time_t);
time_t	error_interval(void);
void	set_next(struct ntp_peer *, time_t);

/* util.c */
void			d_to_tv(double, struct timeval *);
double			lfp_to_d(struct l_fixedpt);
struct l_fixedpt	d_to_lfp(double);
double			sfp_to_d(struct s_fixedpt);
struct s_fixedpt	d_to_sfp(double);

/* ../rdate/cutil.c */
const char *log_sockaddr(struct sockaddr *);
double gettime(void);
