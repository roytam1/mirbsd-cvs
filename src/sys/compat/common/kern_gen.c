/* $MirOS: src/sys/compat/common/kern_gen.c,v 1.2 2005/12/17 05:46:24 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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
 * Based upon code Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 */

#include <sys/param.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/signalvar.h>

#include <sys/mount.h>
#include <sys/syscallargs.h>

#include <machine/cpu.h>
#include <compat/common/compat_util.h>
#include <compat/common/kern_gen.h>

int	compat_time_sys_gettimeofday(struct proc *, void *, register_t *);
int	compat_time_sys_settimeofday(struct proc *, void *, register_t *);
int	compat_time_sys_setitimer(struct proc *, void *, register_t *);
int	compat_time_sys_getitimer(struct proc *, void *, register_t *);
int	compat_time_sys_clock_gettime(struct proc *, void *, register_t *);
int	compat_time_sys_clock_settime(struct proc *, void *, register_t *);
int	compat_time_sys_clock_getres(struct proc *, void *, register_t *);
int	compat_time_sys_nanosleep(struct proc *, void *, register_t *);
int	compat_time_sys_kevent(struct proc *, void *, register_t *);


#if defined(COMPAT_OPENBSD) || defined(COMPAT_LINUX)
int
compat_time_sys_gettimeofday(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_gettimeofday_args /* {
		syscallarg(struct timeval_compat *) tp;
		syscallarg(struct timezone *) tzp;
	} */ *uap = v;
	struct timeval atv;
	struct timeval_compat ctv;
	int error = 0;

	if (SCARG(uap, tp)) {
		microtime(&atv);
		ctv.tv_sec = atv.tv_sec;
		ctv.tv_usec = atv.tv_usec;
		if ((error = copyout((void *)&ctv, (void *)SCARG(uap, tp),
		    sizeof (ctv))))
			return (error);
	}
	if (SCARG(uap, tzp))
		error = copyout((void *)&tz, (void *)SCARG(uap, tzp),
		    sizeof (tz));
	return (error);
}

int
compat_time_sys_settimeofday(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_settimeofday_args /* {
		syscallarg(const struct timeval_compat *) tv;
		syscallarg(const struct timezone *) tzp;
	} */ *uap = v;
	struct timeval atv;
	struct timeval_compat ctv;
	struct timezone atz;
	int error;

	if ((error = suser(p, 0)))
		return (error);
	/* Verify all parameters before changing time. */
	if (SCARG(uap, tv) && (error = copyin((void *)SCARG(uap, tv),
	    (void *)&ctv, sizeof(ctv))))
		return (error);
	if (SCARG(uap, tzp) && (error = copyin((void *)SCARG(uap, tzp),
	    (void *)&atz, sizeof(atz))))
		return (error);
	if (SCARG(uap, tv)) {
		atv.tv_sec = ctv.tv_sec;
		atv.tv_usec = ctv.tv_usec;
		if ((error = settime(&atv)) != 0)
			return (error);
	}
	if (SCARG(uap, tzp))
		tz = atz;
	return (0);
}

int
compat_time_sys_setitimer(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_setitimer_args /* {
		syscallarg(int) which;
		syscallarg(const struct itimerval_compat *) itv;
		syscallarg(struct itimerval_compat *) oitv;
	} */ *uap = v;
	struct sys_setitimer_args {
		syscallarg(int) which;
		syscallarg(const struct itimerval *) itv;
		syscallarg(struct itimerval *) oitv;
	} bap;
	struct itimerval tv, *tvp1 = NULL, *tvp2 = NULL;
	struct itimerval_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, which) = SCARG(uap, which);
	if (SCARG(uap, oitv) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, oitv) = tvp2;

	if (SCARG(uap, itv) != NULL) {
		tvp1 = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, itv),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.it_interval.tv_sec = ctv.it_interval.tv_sec;
		tv.it_interval.tv_usec = ctv.it_interval.tv_usec;
		tv.it_value.tv_sec = ctv.it_value.tv_sec;
		tv.it_value.tv_usec = ctv.it_value.tv_usec;
		if ((error = copyout(&tv, tvp1, sizeof(tv))))
			return error;
	}
	SCARG(&bap, itv) = tvp1;

	if ((error = sys_setitimer(p, &bap, retval)))
		return error;

	if (SCARG(uap, oitv) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.it_interval.tv_sec = __BOUNDLONG(tv.it_interval.tv_sec);
		ctv.it_interval.tv_usec = tv.it_interval.tv_usec;
		ctv.it_value.tv_sec = __BOUNDLONG(tv.it_value.tv_sec);
		ctv.it_value.tv_usec = tv.it_value.tv_usec;
		if ((error = copyout(&ctv, SCARG(uap, oitv), sizeof(ctv))))
			return error;
	}

	return error;
}

int
compat_time_sys_getitimer(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_getitimer_args /* {
		syscallarg(int) which;
		syscallarg(struct itimerval_compat *) itv;
	} */ *uap = v;
	struct sys_getitimer_args {
		syscallarg(int) which;
		syscallarg(struct itimerval *) itv;
	} bap;
	struct itimerval tv, *tvp2 = NULL;
	struct itimerval_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, which) = SCARG(uap, which);
	if (SCARG(uap, itv) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, itv) = tvp2;

	if ((error = sys_getitimer(p, &bap, retval)))
		return error;

	if (SCARG(uap, itv) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.it_interval.tv_sec = __BOUNDLONG(tv.it_interval.tv_sec);
		ctv.it_interval.tv_usec = tv.it_interval.tv_usec;
		ctv.it_value.tv_sec = __BOUNDLONG(tv.it_value.tv_sec);
		ctv.it_value.tv_usec = tv.it_value.tv_usec;
		if ((error = copyout(&ctv, SCARG(uap, itv), sizeof(ctv))))
			return error;
	}

	return error;
}
#endif

#if defined(COMPAT_OPENBSD)
int
compat_time_sys_clock_gettime(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_clock_gettime_args /* {
		syscallarg(clockid_t) clock_id;
		syscallarg(struct timespec_compat *) tp;
	} */ *uap = v;
	struct sys_clock_gettime_args {
		syscallarg(clockid_t) clock_id;
		syscallarg(struct timespec *) tp;
	} bap;
	struct timespec tv, *tvp2 = NULL;
	struct timespec_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, clock_id) = SCARG(uap, clock_id);
	if (SCARG(uap, tp) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, tp) = tvp2;

	if ((error = sys_clock_gettime(p, &bap, retval)))
		return error;

	if (SCARG(uap, tp) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.tv_sec = __BOUNDLONG(tv.tv_sec);
		ctv.tv_nsec = tv.tv_nsec;
		if ((error = copyout(&ctv, SCARG(uap, tp), sizeof(ctv))))
			return error;
	}

	return error;
}

int
compat_time_sys_clock_settime(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_clock_settime_args /* {
		syscallarg(clockid_t) clock_id;
		syscallarg(const struct timespec_compat *) tp;
	} */ *uap = v;
	struct sys_clock_settime_args {
		syscallarg(clockid_t) clock_id;
		syscallarg(const struct timespec *) tp;
	} bap;
	struct timespec tv, *tvp1 = NULL;
	struct timespec_compat ctv;
	int error;

	SCARG(&bap, clock_id) = SCARG(uap, clock_id);

	if (SCARG(uap, tp) != NULL) {
		caddr_t sg = stackgap_init(p->p_emul);
		tvp1 = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, tp),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.tv_sec = ctv.tv_sec;
		tv.tv_nsec = ctv.tv_nsec;
		if ((error = copyout(&tv, tvp1, sizeof(tv))))
			return error;
	}
	SCARG(&bap, tp) = tvp1;

	return sys_clock_settime(p, &bap, retval);
}

int
compat_time_sys_clock_getres(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_clock_getres_args /* {
		syscallarg(clockid_t) clock_id;
		syscallarg(struct timespec_compat *) tp;
	} */ *uap = v;
	struct sys_clock_getres_args {
		syscallarg(clockid_t) clock_id;
		syscallarg(struct timespec *) tp;
	} bap;
	struct timespec tv, *tvp2 = NULL;
	struct timespec_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, clock_id) = SCARG(uap, clock_id);
	if (SCARG(uap, tp) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, tp) = tvp2;

	if ((error = sys_clock_getres(p, &bap, retval)))
		return error;

	if (SCARG(uap, tp) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.tv_sec = __BOUNDLONG(tv.tv_sec);
		ctv.tv_nsec = tv.tv_nsec;
		if ((error = copyout(&ctv, SCARG(uap, tp), sizeof(ctv))))
			return error;
	}

	return error;
}
#endif

#if defined(COMPAT_OPENBSD) || defined(COMPAT_LINUX)
int
compat_time_sys_nanosleep(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_nanosleep_args /* {
		syscallarg(const struct timespec_compat *) rqtp;
		syscallarg(struct timespec_compat *) rmtp;
	} */ *uap = v;
	struct sys_nanosleep_args {
		syscallarg(const struct timespec *) rqtp;
		syscallarg(struct timespec *) rmtp;
	} bap;
	struct timespec tv, *tvp1 = NULL, *tvp2 = NULL;
	struct timespec_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	if (SCARG(uap, rmtp) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, rmtp) = tvp2;

	if (SCARG(uap, rqtp) != NULL) {
		tvp1 = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, rqtp),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.tv_sec = ctv.tv_sec;
		tv.tv_nsec = ctv.tv_nsec;
		if ((error = copyout(&tv, tvp1, sizeof(tv))))
			return error;
	}
	SCARG(&bap, rqtp) = tvp1;

	if ((error = sys_nanosleep(p, &bap, retval)))
		return error;

	if (SCARG(uap, rmtp) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.tv_sec = __BOUNDLONG(tv.tv_sec);
		ctv.tv_nsec = tv.tv_nsec;
		if ((error = copyout(&ctv, SCARG(uap, rmtp), sizeof(ctv))))
			return error;
	}

	return error;
}
#endif

#if defined(COMPAT_OPENBSD)
int
compat_time_sys_kevent(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_kevent_args /* {
		syscallarg(int) fd;
		syscallarg(const struct kevent *) changelist;
		syscallarg(int) nchanges;
		syscallarg(struct kevent *) eventlist;
		syscallarg(int) nevents;
		syscallarg(const struct timespec_compat *) timeout;
	} */ *uap = v;
	struct sys_kevent_args {
		syscallarg(int) fd;
		syscallarg(const struct kevent *) changelist;
		syscallarg(int) nchanges;
		syscallarg(struct kevent *) eventlist;
		syscallarg(int) nevents;
		syscallarg(const struct timespec *) timeout;
	} bap;
	struct timespec tv, *tvp = NULL;
	struct timespec_compat ctv;
	caddr_t sg;
	int error;

	SCARG(&bap,fd ) = SCARG(uap, fd);
	SCARG(&bap,changelist ) = SCARG(uap, changelist);
	SCARG(&bap,nchanges ) = SCARG(uap, nchanges);
	SCARG(&bap,eventlist ) = SCARG(uap, eventlist);
	SCARG(&bap,nevents ) = SCARG(uap, nevents);

	if (SCARG(uap, timeout) != NULL) {
		sg = stackgap_init(p->p_emul);
		tvp = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, timeout),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.tv_sec = ctv.tv_sec;
		tv.tv_nsec = ctv.tv_nsec;
		if ((error = copyout(&tv, tvp, sizeof(tv))))
			return error;
	}
	SCARG(&bap, timeout) = tvp;

	return sys_kevent(p, &bap, retval);
}
#endif
