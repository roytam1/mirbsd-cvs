/**	$MirOS$ */
/*	$OpenBSD: kern_resource.c,v 1.26 2003/12/11 23:02:30 millert Exp $	*/
/*	$NetBSD: kern_resource.c,v 1.38 1996/10/23 07:19:38 matthias Exp $	*/

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this soft-
 *    ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 * 4. Neither the name of the University nor the names of its contributors
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
 *
 *	@(#)kern_resource.c	8.5 (Berkeley) 1/21/94
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/resourcevar.h>
#include <sys/malloc.h>
#include <sys/proc.h>

#include <sys/mount.h>
#include <sys/syscallargs.h>
#include <compat/common/compat_util.h>
#include <compat/common/kern_gen.h>

#include <uvm/uvm_extern.h>

#if defined(COMPAT_OPENBSD) || defined(COMPAT_LINUX)

struct rusage_compat {
	struct timeval_compat ru_utime;
	struct timeval_compat ru_stime;
	long	ru_maxrss;
	long	ru_ixrss;
	long	ru_idrss;
	long	ru_isrss;
	long	ru_minflt;
	long	ru_majflt;
	long	ru_nswap;
	long	ru_inblock;
	long	ru_oublock;
	long	ru_msgsnd;
	long	ru_msgrcv;
	long	ru_nsignals;
	long	ru_nvcsw;
	long	ru_nivcsw;
};

extern void calcru(struct proc *, struct timeval *,
    struct timeval *, struct timeval *);
static void cvt_ru(struct rusage *, struct rusage_compat *);
int compat_time_sys_getrusage(struct proc *, void *, register_t *);
int compat_time_sys_wait4(struct proc *, void *, register_t *);

static void
cvt_ru(struct rusage *n, struct rusage_compat *o)
{
	if (!n || !o)
		return;

	o->ru_utime.tv_sec = __BOUNDLONG(n->ru_utime.tv_sec);
	o->ru_utime.tv_usec = n->ru_utime.tv_usec;
	o->ru_stime.tv_sec = __BOUNDLONG(n->ru_stime.tv_sec);
	o->ru_stime.tv_usec = n->ru_stime.tv_usec;
	o->ru_maxrss = n->ru_maxrss;
	o->ru_ixrss = n->ru_ixrss;
	o->ru_idrss = n->ru_idrss;
	o->ru_isrss = n->ru_isrss;
	o->ru_minflt = n->ru_minflt;
	o->ru_majflt = n->ru_majflt;
	o->ru_nswap = n->ru_nswap;
	o->ru_inblock = n->ru_inblock;
	o->ru_oublock = n->ru_oublock;
	o->ru_msgsnd = n->ru_msgsnd;
	o->ru_msgrcv = n->ru_msgrcv;
	o->ru_nsignals = n->ru_nsignals;
	o->ru_nvcsw = n->ru_nvcsw;
	o->ru_nivcsw = n->ru_nivcsw;
}

/* ARGSUSED */
int
compat_time_sys_getrusage(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_getrusage_args {
		syscallarg(int) who;
		syscallarg(struct rusage_compat *) rusage;
	} *uap = v;
	struct rusage *rup;
	struct rusage_compat cup;

	switch (SCARG(uap, who)) {

	case RUSAGE_SELF:
		rup = &p->p_stats->p_ru;
		calcru(p, &rup->ru_utime, &rup->ru_stime, NULL);
		break;

	case RUSAGE_CHILDREN:
		rup = &p->p_stats->p_cru;
		break;

	default:
		return (EINVAL);
	}

	cvt_ru(rup, &cup);
	return (copyout((caddr_t)&cup, (caddr_t)SCARG(uap, rusage),
	    sizeof (struct rusage_compat)));
}

int
compat_time_sys_wait4(struct proc *p, void *v, register_t *retval)
{
	struct compat_time_sys_wait4_args {
		syscallarg(pid_t) pid;
		syscallarg(int *) status;
		syscallarg(int) options;
		syscallarg(struct rusage_compat *) rusage;
	} *uap = v;
	struct sys_wait4_args {
		syscallarg(pid_t) pid;
		syscallarg(int *) status;
		syscallarg(int) options;
		syscallarg(struct rusage *) rusage;
	} bap;
	struct rusage ru, *rup2 = NULL;
	struct rusage_compat cru;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, pid) = SCARG(uap, pid);
	SCARG(&bap, status) = SCARG(uap, status);
	SCARG(&bap, options) = SCARG(uap, options);
	if (SCARG(uap, rusage) != NULL)
		rup2 = stackgap_alloc(&sg, sizeof(ru));
	SCARG(&bap, rusage) = rup2;

	if ((error = sys_wait4(p, &bap, retval)))
		return error;

	if (SCARG(uap, rusage) != NULL) {
		if ((error = copyin(rup2, (void *)&ru, sizeof(ru))))
			return error;
		cvt_ru(&ru, &cru);
		if ((error = copyout(&cru, SCARG(uap, rusage), sizeof(cru))))
			return error;
	}

	return error;
}
#endif
