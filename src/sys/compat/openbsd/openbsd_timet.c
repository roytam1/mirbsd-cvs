/* $MirOS: src/sys/compat/openbsd/openbsd_timet.c,v 1.1.7.1 2005/03/06 16:33:43 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <sys/syscall.h>
#include <sys/signalvar.h>
#include <sys/mount.h>
#include <sys/fcntl.h>
#include <sys/exec.h>
#include <sys/exec_olf.h>
#include <sys/malloc.h>
#include <compat/common/compat_util.h>
#include <compat/common/kern_gen.h>
#include <compat/openbsd/compat_openbsd.h>
#include <compat/openbsd/openbsd_syscallargs.h>


extern int sys_select(struct proc *, void *, register_t *);
extern int sys_utimes(struct proc *, void *, register_t *);
extern int sys_adjtime(struct proc *, void *, register_t *);
extern int sys_futimes(struct proc *, void *, register_t *);


int
compat_35_sys_select(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_select_args /* {
		syscallarg(int) nd;
		syscallarg(fd_set *) in;
		syscallarg(fd_set *) ou;
		syscallarg(fd_set *) ex;
		syscallarg(struct timeval_compat *) tv;
	} */ *uap = v;
	struct sys_select_args {
		syscallarg(int) nd;
		syscallarg(fd_set *) in;
		syscallarg(fd_set *) ou;
		syscallarg(fd_set *) ex;
		syscallarg(struct timeval *) tv;
	} bap;
	struct timeval tv, *tvp = NULL;
	struct timeval_compat ctv;
	caddr_t sg;
	int error;

	SCARG(&bap, nd) = SCARG(uap, nd);
	SCARG(&bap, in) = SCARG(uap, in);
	SCARG(&bap, ou) = SCARG(uap, ou);
	SCARG(&bap, ex) = SCARG(uap, ex);

	if (SCARG(uap, tv) != NULL) {
		sg = stackgap_init(p->p_emul);
		tvp = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, tv),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.tv_sec = ctv.tv_sec;
		tv.tv_usec = ctv.tv_usec;
		if ((error = copyout(&tv, tvp, sizeof(tv))))
			return error;
	}
	SCARG(&bap, tv) = tvp;

	return sys_select(p, &bap, retval);
}

int
compat_35_openbsd_sys_utimes(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_openbsd_sys_utimes_args /* {
		syscallarg(const char *) path;
		syscallarg(const struct timeval_compat *) tptr;
	} */ *uap = v;
	struct sys_utimes_args {
		syscallarg(const char *) path;
		syscallarg(const struct timeval *) tptr;
	} bap;
	struct timeval tv[2], *tvp = NULL;
	struct timeval_compat ctv[2];
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	SCARG(&bap, path) = SCARG(uap, path);
	if (SCARG(uap, tptr) != NULL) {
		tvp = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, tptr),
		    (void *)ctv, sizeof(ctv))))
			return error;
		tv[0].tv_sec = ctv[0].tv_sec;
		tv[0].tv_usec = ctv[0].tv_usec;
		tv[1].tv_sec = ctv[1].tv_sec;
		tv[1].tv_usec = ctv[1].tv_usec;
		if ((error = copyout(tv, tvp, sizeof(tv))))
			return error;
	}
	SCARG(&bap, tptr) = tvp;

	return sys_utimes(p, &bap, retval);
}

int
compat_35_sys_adjtime(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_adjtime_args /* {
		syscallarg(const struct timeval_compat *) delta;
		syscallarg(struct timeval_compat *) olddelta;
	} */ *uap = v;
	struct sys_adjtime_args {
		syscallarg(const struct timeval *) delta;
		syscallarg(struct timeval *) olddelta;
	} bap;
	struct timeval tv, *tvp1 = NULL, *tvp2 = NULL;
	struct timeval_compat ctv;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	if (SCARG(uap, olddelta) != NULL)
		tvp2 = stackgap_alloc(&sg, sizeof(tv));
	SCARG(&bap, olddelta) = tvp2;

	if (SCARG(uap, delta) != NULL) {
		tvp1 = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, delta),
		    (void *)&ctv, sizeof(ctv))))
			return error;
		tv.tv_sec = ctv.tv_sec;
		tv.tv_usec = ctv.tv_usec;
		if ((error = copyout(&tv, tvp1, sizeof(tv))))
			return error;
	}
	SCARG(&bap, delta) = tvp1;

	if ((error = sys_adjtime(p, &bap, retval)))
		return error;

	if (SCARG(uap, olddelta) != NULL) {
		if ((error = copyin(tvp2, (void *)&tv, sizeof(tv))))
			return error;
		ctv.tv_sec = __BOUNDLONG(tv.tv_sec);
		ctv.tv_usec = tv.tv_usec;
		if ((error = copyout(&ctv, SCARG(uap, olddelta), sizeof(ctv))))
			return error;
	}

	return error;
}

int
compat_35_sys_futimes(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_futimes_args /* {
		syscallarg(int) fd;
		syscallarg(const struct timeval_compat *) tptr;
	} */ *uap = v;
	struct sys_futimes_args {
		syscallarg(int) fd;
		syscallarg(const struct timeval *) tptr;
	} bap;
	struct timeval tv[2], *tvp = NULL;
	struct timeval_compat ctv[2];
	caddr_t sg;
	int error;

	SCARG(&bap, fd) = SCARG(uap, fd);
	if (SCARG(uap, tptr) != NULL) {
		sg = stackgap_init(p->p_emul);
		tvp = stackgap_alloc(&sg, sizeof(tv));

		if ((error = copyin((void *)SCARG(uap, tptr),
		    (void *)ctv, sizeof(ctv))))
			return error;
		tv[0].tv_sec = ctv[0].tv_sec;
		tv[0].tv_usec = ctv[0].tv_usec;
		tv[1].tv_sec = ctv[1].tv_sec;
		tv[1].tv_usec = ctv[1].tv_usec;
		if ((error = copyout(tv, tvp, sizeof(tv))))
			return error;
	}
	SCARG(&bap, tptr) = tvp;

	return sys_futimes(p, &bap, retval);
}
