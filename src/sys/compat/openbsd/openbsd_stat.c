/* $MirOS: src/sys/compat/openbsd/openbsd_stat.c,v 1.1.7.1 2005/03/06 16:33:43 tg Exp $ */

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
#include <sys/stat.h>
#include <compat/common/compat_util.h>
#include <compat/common/kern_gen.h>
#include <compat/openbsd/compat_openbsd.h>
#include <compat/openbsd/openbsd_syscallargs.h>

struct stat_compat {
	dev_t	  st_dev;
	ino_t	  st_ino;
	mode_t	  st_mode;
	nlink_t	  st_nlink;
	uid_t	  st_uid;
	gid_t	  st_gid;
	dev_t	  st_rdev;
	int32_t	  st_lspare0;
	struct	timespec_compat st_atimespec;
	struct	timespec_compat st_mtimespec;
	struct	timespec_compat st_ctimespec;
	off_t	  st_size;
	int64_t	  st_blocks;
	u_int32_t st_blksize;
	u_int32_t st_flags;
	u_int32_t st_gen;
	int32_t	  st_lspare1;
	struct	timespec_compat __st_birthtimespec;
	int64_t	  st_qspare[2];
};

static void cvtstat(struct stat *, struct stat_compat *);
extern int sys_stat(struct proc *, void *, register_t *);
extern int sys_lstat(struct proc *, void *, register_t *);
extern int sys_fstat(struct proc *, void *, register_t *);
extern int sys_fhstat(struct proc *, void *, register_t *);


/*
 * Convert from a new to an old stat structure.
 */
static void
cvtstat(struct stat *st, struct stat_compat *ost)
{
	ost->st_dev = st->st_dev;
	ost->st_ino = st->st_ino;
	ost->st_mode = st->st_mode;
	ost->st_nlink = st->st_nlink;
	ost->st_uid = st->st_uid;
	ost->st_gid = st->st_gid;
	ost->st_rdev = st->st_rdev;
	ost->st_atimespec.tv_sec = __BOUNDLONG(st->st_atimespec.tv_sec);
	ost->st_atimespec.tv_nsec = st->st_atimespec.tv_nsec;
	ost->st_mtimespec.tv_sec = __BOUNDLONG(st->st_mtimespec.tv_sec);
	ost->st_mtimespec.tv_nsec = st->st_mtimespec.tv_nsec;
	ost->st_ctimespec.tv_sec = __BOUNDLONG(st->st_ctimespec.tv_sec);
	ost->st_ctimespec.tv_nsec = st->st_ctimespec.tv_nsec;
	ost->st_size = st->st_size;
	ost->st_blocks = st->st_blocks;
	ost->st_blksize = st->st_blksize;
	ost->st_flags = st->st_flags;
	ost->st_gen = st->st_gen;
	ost->st_lspare0 = st->st_lspare0;
	ost->st_lspare1 = st->st_lspare1;
	ost->st_qspare[0] = st->st_qspare[0];
	ost->st_qspare[1] = st->st_qspare[1];
	ost->__st_birthtimespec.tv_sec =
	    __BOUNDLONG(st->__st_birthtimespec.tv_sec);
	ost->__st_birthtimespec.tv_nsec = st->__st_birthtimespec.tv_nsec;
}

int
compat_36_sys_stat(struct proc *p, void *v, register_t *retval)
{
	struct compat_36_sys_stat_args /* {
		syscallarg(const char *) path;
		syscallarg(struct stat_compat *) ub;
	} */ *uap = v;
	struct sys_stat_args {
		syscallarg(const char *) path;
		syscallarg(struct stat *) ub;
	} bap;
	struct stat sb, *sbp = NULL;
	struct stat_compat osb;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	SCARG(&bap, path) = SCARG(uap, path);
	if (SCARG(uap, ub) != NULL)
		sbp = stackgap_alloc(&sg, sizeof(sb));
	SCARG(&bap, ub) = sbp;

	if ((error = sys_stat(p, &bap, retval)))
		return error;

	if (SCARG(uap, ub) != NULL) {
		if ((error = copyin(sbp, (void *)&sb, sizeof(sb))))
			return error;
		cvtstat(&sb, &osb);
		if ((error = copyout(&osb, SCARG(uap, ub), sizeof(osb))))
			return error;
	}

	return error;
}	

int
compat_36_sys_lstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_36_sys_lstat_args /* {
		syscallarg(const char *) path;
		syscallarg(struct stat_compat *) ub;
	} */ *uap = v;
	struct sys_lstat_args {
		syscallarg(const char *) path;
		syscallarg(struct stat *) ub;
	} bap;
	struct stat sb, *sbp = NULL;
	struct stat_compat osb;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	SCARG(&bap, path) = SCARG(uap, path);
	if (SCARG(uap, ub) != NULL)
		sbp = stackgap_alloc(&sg, sizeof(sb));
	SCARG(&bap, ub) = sbp;

	if ((error = sys_lstat(p, &bap, retval)))
		return error;

	if (SCARG(uap, ub) != NULL) {
		if ((error = copyin(sbp, (void *)&sb, sizeof(sb))))
			return error;
		cvtstat(&sb, &osb);
		if ((error = copyout(&osb, SCARG(uap, ub), sizeof(osb))))
			return error;
	}

	return error;
}

int
compat_36_sys_fstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_36_sys_fstat_args /* {
		syscallarg(int) fd;
		syscallarg(struct stat_compat *) sb;
	} */ *uap = v;
	struct sys_fstat_args {
		syscallarg(int) fd;
		syscallarg(struct stat *) sb;
	} bap;
	struct stat sb, *sbp = NULL;
	struct stat_compat osb;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, fd) = SCARG(uap, fd);
	if (SCARG(uap, sb) != NULL)
		sbp = stackgap_alloc(&sg, sizeof(sb));
	SCARG(&bap, sb) = sbp;

	if ((error = sys_fstat(p, &bap, retval)))
		return error;

	if (SCARG(uap, sb) != NULL) {
		if ((error = copyin(sbp, (void *)&sb, sizeof(sb))))
			return error;
		cvtstat(&sb, &osb);
		if ((error = copyout(&osb, SCARG(uap, sb), sizeof(osb))))
			return error;
	}

	return error;
}

int
compat_36_sys_fhstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_36_sys_fhstat_args /* {
		syscallarg(const fhandle_t *) fhp;
		syscallarg(struct stat *) sb;
	} */ *uap = v;
	struct sys_fstat_args {
		syscallarg(const fhandle_t *) fhp;
		syscallarg(struct stat *) sb;
	} bap;
	struct stat sb, *sbp = NULL;
	struct stat_compat osb;
	caddr_t sg = stackgap_init(p->p_emul);
	int error;

	SCARG(&bap, fhp) = SCARG(uap, fhp);
	if (SCARG(uap, sb) != NULL)
		sbp = stackgap_alloc(&sg, sizeof(sb));
	SCARG(&bap, sb) = sbp;

	if ((error = sys_fhstat(p, &bap, retval)))
		return error;

	if (SCARG(uap, sb) != NULL) {
		if ((error = copyin(sbp, (void *)&sb, sizeof(sb))))
			return error;
		cvtstat(&sb, &osb);
		if ((error = copyout(&osb, SCARG(uap, sb), sizeof(osb))))
			return error;
	}

	return error;
}
