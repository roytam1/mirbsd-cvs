/* $MirOS: src/usr.sbin/rdate/rdate.h,v 1.2 2007/08/16 10:38:29 tg Exp $ */

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

#ifdef __MirBSD__
#define tick2utc(tv)	tai2utc(timet2tai(tv))
#else
extern time_t tick2utc(time_t);		/* from ntpleaps.c */
#endif

void ntp_client(const char *, int, struct timeval *, struct timeval *,
    int, int);
void rfc868time_client (const char *, int, struct timeval *,
    struct timeval *);

extern int debug;

const char *log_sockaddr(struct sockaddr *);
