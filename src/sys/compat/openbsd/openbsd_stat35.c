/**	$MirOS$ */
/*	$OpenBSD: vfs_syscalls_35.c,v 1.3 2004/07/14 18:57:57 millert Exp $	*/

/*
 * Copyright (c) 1989, 1993
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
 * 3. Neither the name of the University nor the names of its contributors
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
 *	@(#)vfs_syscalls.c	8.28 (Berkeley) 12/10/94
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/namei.h>
#include <sys/dirent.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>

#include <sys/mount.h>
#include <compat/common/compat_util.h>
#include <compat/common/kern_gen.h>
#include <compat/openbsd/compat_openbsd.h>
#include <compat/openbsd/openbsd_syscallargs.h>

struct stat35 {
	dev_t	  st_dev;		/* inode's device */
	ino_t	  st_ino;		/* inode's number */
	u_int16_t  st_mode;		/* inode protection mode */
	u_int16_t  st_nlink;		/* number of hard links */
	uid_t	  st_uid;		/* user ID of the file's owner */
	gid_t	  st_gid;		/* group ID of the file's group */
	dev_t	  st_rdev;		/* device type */
	struct	timespec_compat st_atimespec;	/* time of last access */
	struct	timespec_compat st_mtimespec;	/* time of last data modification */
	struct	timespec_compat st_ctimespec;	/* time of last file status change */
	off_t	  st_size;		/* file size, in bytes */
	int64_t	  st_blocks;		/* blocks allocated for file */
	u_int32_t st_blksize;		/* optimal blocksize for I/O */
	u_int32_t st_flags;		/* user defined flags for file */
	u_int32_t st_gen;		/* file generation number */
	int32_t	  st_lspare;
	int64_t	  st_qspare[2];
};

#if defined(COMPAT_OPENBSD)
static void cvtstat(struct stat *, struct stat35 *);

/*
 * Convert from a new to an old stat structure.
 */
static void
cvtstat(struct stat *st, struct stat35 *ost)
{

	ost->st_dev = st->st_dev;
	ost->st_ino = st->st_ino;
	ost->st_mode = st->st_mode & 0xffff;
	ost->st_nlink = st->st_nlink & 0xffff;
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
}

/*
 * Get file status; this version follows links.
 */
/* ARGSUSED */
int
compat_35_sys_stat(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_stat_args /* {
		syscallarg(char *) path;
		syscallarg(struct stat35 *) ub;
	} */ *uap = v;
	struct stat sb;
	struct stat35 osb;
	int error;
	struct nameidata nd;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
	if ((error = namei(&nd)) != 0)
		return (error);
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
	if (error)
		return (error);
	/* Don't let non-root see generation numbers (for NFS security) */
	if (suser(p, 0))
		sb.st_gen = 0;
	cvtstat(&sb, &osb);
	error = copyout(&osb, SCARG(uap, ub), sizeof(osb));
	return (error);
}

/*
 * Get file status; this version does not follow links.
 */
/* ARGSUSED */
int
compat_35_sys_lstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_lstat_args /* {
		syscallarg(char *) path;
		syscallarg(struct stat35 *) ub;
	} */ *uap = v;
	struct stat sb;
	struct stat35 osb;
	int error;
	struct nameidata nd;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
	if ((error = namei(&nd)) != 0)
		return (error);
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
	if (error)
		return (error);
	/* Don't let non-root see generation numbers (for NFS security) */
	if (suser(p, 0))
		sb.st_gen = 0;
	cvtstat(&sb, &osb);
	error = copyout(&osb, SCARG(uap, ub), sizeof(osb));
	return (error);
}

/*
 * Return status information about a file descriptor.
 */
/* ARGSUSED */
int
compat_35_sys_fstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_fstat_args /* {
		syscallarg(int) fd;
		syscallarg(struct stat35 *) sb;
	} */ *uap = v;
	int fd = SCARG(uap, fd);
	struct filedesc *fdp = p->p_fd;
	struct file *fp;
	struct stat ub;
	struct stat35 oub;
	int error;

	if ((fp = fd_getfile(fdp, fd)) == NULL)
		return (EBADF);
	FREF(fp);
	error = (*fp->f_ops->fo_stat)(fp, &ub, p);
	FRELE(fp);
	if (error == 0) {
		/* Don't let non-root see generation numbers
		   (for NFS security) */
		if (suser(p, 0))
			ub.st_gen = 0;
		cvtstat(&ub, &oub);
		error = copyout(&oub, SCARG(uap, sb), sizeof(oub));
	}
	return (error);
}

/* ARGSUSED */
int
compat_35_sys_fhstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_35_sys_fhstat_args /* {
		syscallarg(const fhandle_t *) fhp;
		syscallarg(struct stat35 *) sb;
	} */ *uap = v;
	struct stat ub;
	struct stat35 oub;
	int error;
	fhandle_t fh;
	struct mount *mp;
	struct vnode *vp;

	/*
	 * Must be super user
	 */
	if ((error = suser(p, 0)))
		return (error);

	if ((error = copyin(SCARG(uap, fhp), &fh, sizeof(fhandle_t))) != 0)
		return (error);

	if ((mp = vfs_getvfs(&fh.fh_fsid)) == NULL)
		return (ESTALE);
	if ((error = VFS_FHTOVP(mp, &fh.fh_fid, &vp)))
		return (error);
	error = vn_stat(vp, &ub, p);
	vput(vp);
	if (error)
		return (error);
	cvtstat(&ub, &oub);
	error = copyout(&oub, SCARG(uap, sb), sizeof(oub));
	return (error);
}
#endif /* def COMPAT_OPENBSD */
