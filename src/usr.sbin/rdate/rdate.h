/* $MirOS: src/usr.sbin/rdate/rdate.h,v 1.4 2011/11/20 22:02:43 tg Exp $ */

/* This macro is not implemented on all operating systems */
#ifndef	SA_LEN
#define	SA_LEN(x)	(((x)->sa_family == AF_INET6) ? \
			    sizeof(struct sockaddr_in6) : \
			    (((x)->sa_family == AF_INET) ? \
				sizeof(struct sockaddr_in) : \
				sizeof(struct sockaddr)))
#endif

#ifdef EXT_A4R
extern u_int32_t arc4random(void);
#endif

#ifndef SYSKERN_MIRTIME_H
time_t timet2posix(time_t);
#endif

void ntp_client(const char *, int, struct timeval *, struct timeval *,
    int, int);
void rfc868time_client (const char *, int, struct timeval *,
    struct timeval *);

extern int debug;

const char *log_sockaddr(struct sockaddr *);
double gettime(void);
