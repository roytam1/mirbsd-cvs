/* $MirOS$ */

#ifndef	_COMPAT_KERN_GEN_H
#define	_COMPAT_KERN_GEN_H

#define	__BOUNDLONG(x)	__BOUNDINT(LONG_MIN, LONG_MAX, (x))

struct timeval_compat {
	long tv_sec;
	long tv_usec;
};

struct itimerval_compat {
	struct timeval_compat it_interval;
	struct timeval_compat it_value;
};

struct timespec_compat {
	long tv_sec;
	long tv_nsec;
};


#ifdef	syscallarg
struct compat_time_sys_gettimeofday_args {
	syscallarg(struct timeval_compat *) tp;
	syscallarg(struct timezone *) tzp;
};

struct compat_time_sys_settimeofday_args {
	syscallarg(const struct timeval_compat *) tv;
	syscallarg(const struct timezone *) tzp;
};

struct compat_time_sys_setitimer_args {
	syscallarg(int) which;
	syscallarg(const struct itimerval_compat *) itv;
	syscallarg(struct itimerval_compat *) oitv;
};

struct compat_time_sys_getitimer_args {
	syscallarg(int) which;
	syscallarg(struct itimerval_compat *) itv;
};

struct compat_time_sys_clock_gettime_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(struct timespec_compat *) tp;
};

struct compat_time_sys_clock_settime_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(const struct timespec_compat *) tp;
};

struct compat_time_sys_clock_getres_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(struct timespec_compat *) tp;
};

struct compat_time_sys_nanosleep_args {
	syscallarg(const struct timespec_compat *) rqtp;
	syscallarg(struct timespec_compat *) rmtp;
};

struct compat_time_sys_kevent_args {
	syscallarg(int) fd;
	syscallarg(const struct kevent *) changelist;
	syscallarg(int) nchanges;
	syscallarg(struct kevent *) eventlist;
	syscallarg(int) nevents;
	syscallarg(const struct timespec_compat *) timeout;
};
#endif	/* def syscallarg */

#endif	/* ndef _COMPAT_KERN_GEN_H */
