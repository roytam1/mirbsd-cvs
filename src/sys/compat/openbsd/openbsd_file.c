/**	$MirOS$ */
/*	$OpenBSD: netbsd_file.c,v 1.5 2003/08/15 20:32:16 tedu Exp $	*/
/*	$NetBSD: freebsd_file.c,v 1.3 1996/05/03 17:03:09 christos Exp $	*/

/*
 * Copyright (c) 1995 Frank van der Linden
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed for the NetBSD Project
 *      by Frank van der Linden
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	from: linux_file.c,v 1.3 1995/04/04 04:21:30 mycroft Exp
 */

#include <sys/param.h>
#include <sys/syscall.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/filedesc.h>
#include <sys/ioctl.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/malloc.h>
#include <compat/common/compat_util.h>
#include <compat/openbsd/compat_openbsd.h>
#include <compat/openbsd/openbsd_syscallargs.h>

#define	ARRAY_LENGTH(array)	(sizeof(array)/sizeof(array[0]))

int sys_mount(struct proc *, void *, register_t *);
int sys_open(struct proc *, void *, register_t *);
int compat_43_sys_creat(struct proc *, void *, register_t *);
int sys_link(struct proc *, void *, register_t *);
int sys_unlink(struct proc *, void *, register_t *);
int sys_chdir(struct proc *, void *, register_t *);
int sys_mknod(struct proc *, void *, register_t *);
int sys_chmod(struct proc *, void *, register_t *);
int sys_chown(struct proc *, void *, register_t *);
int sys_unmount(struct proc *, void *, register_t *);
int sys_access(struct proc *, void *, register_t *);
int sys_chflags(struct proc *, void *, register_t *);
int sys_revoke(struct proc *, void *, register_t *);
int sys_symlink(struct proc *, void *, register_t *);
int sys_readlink(struct proc *, void *, register_t *);
int sys_execve(struct proc *, void *, register_t *);
int sys_chroot(struct proc *, void *, register_t *);
int sys_rename(struct proc *, void *, register_t *);
int compat_43_sys_truncate(struct proc *, void *, register_t *);
int sys_mkfifo(struct proc *, void *, register_t *);
int sys_mkdir(struct proc *, void *, register_t *);
int sys_rmdir(struct proc *, void *, register_t *);
int sys_getfh(struct proc *, void *, register_t *);
int sys_pathconf(struct proc *, void *, register_t *);
int sys_truncate(struct proc *, void *, register_t *);
int compat_43_sys_lstat(struct proc *, void *, register_t *);
int sys_ktrace(struct proc *, void *, register_t *);
int sys_quotactl(struct proc *, void *, register_t *);
int sys_lchown(struct proc *, void *, register_t *);
int sys_statfs(struct proc *, void *, register_t *);


int
openbsd_sys_mount(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_mount_args /* {
		syscallarg(int) type;
		syscallarg(char *) path;
		syscallarg(int) flags;
		syscallarg(caddr_t) data;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_mount(p, uap, retval);
}

/* XXX - UNIX domain: int openbsd_sys_bind(int s, caddr_t name, int namelen); */
/* XXX - UNIX domain: int openbsd_sys_connect(int s, caddr_t name, int namelen); */

int
openbsd_sys_open(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_open_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
		syscallarg(int) mode;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	if (SCARG(uap, flags) & O_CREAT)
		OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, path));
	else
		OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_open(p, uap, retval);
}

int
compat_43_openbsd_sys_creat(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct compat_43_openbsd_sys_creat_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap = v;
	caddr_t sg  = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, path));
	return compat_43_sys_creat(p, uap, retval);
}

int
openbsd_sys_link(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_link_args /* {
		syscallarg(char *) path;
		syscallarg(char *) link;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, link));
	return sys_link(p, uap, retval);
}

int
openbsd_sys_unlink(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_unlink_args /* {
		syscallarg(char *) path;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_unlink(p, uap, retval);
}

int
openbsd_sys_chdir(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_chdir_args /* {
		syscallarg(char *) path;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_chdir(p, uap, retval);
}

int
openbsd_sys_mknod(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_mknod_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
		syscallarg(int) dev;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, path));
	return sys_mknod(p, uap, retval);
}

int
openbsd_sys_chmod(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_chmod_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_chmod(p, uap, retval);
}

int
openbsd_sys_chown(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_chown_args /* {
		syscallarg(char *) path;
		syscallarg(int) uid;
		syscallarg(int) gid;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_chown(p, uap, retval);
}

int
openbsd_sys_unmount(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_unmount_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_unmount(p, uap, retval);
}

int
openbsd_sys_access(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_access_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_access(p, uap, retval);
}

int
openbsd_sys_chflags(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_chflags_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_chflags(p, uap, retval);
}

int
openbsd_sys_revoke(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_revoke_args /* {
		syscallarg(char *) path;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_revoke(p, uap, retval);
}

int
openbsd_sys_symlink(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_symlink_args /* {
		syscallarg(char *) path;
		syscallarg(char *) link;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, link));
	return sys_symlink(p, uap, retval);
}

int
openbsd_sys_readlink(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_readlink_args /* {
		syscallarg(char *) path;
		syscallarg(char *) buf;
		syscallarg(int) count;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_readlink(p, uap, retval);
}

int
openbsd_sys_execve(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_execve_args /* {
		syscallarg(char *) path;
		syscallarg(char *const *) argp;
		syscallarg(char *const *) envp;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_execve(p, uap, retval);
}

int
openbsd_sys_chroot(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_chroot_args /* {
		syscallarg(char *) path;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_chroot(p, uap, retval);
}

int
openbsd_sys_rename(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_rename_args /* {
		syscallarg(char *) from;
		syscallarg(char *) to;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, from));
	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, to));
	return sys_rename(p, uap, retval);
}

int
compat_43_openbsd_sys_truncate(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct compat_43_openbsd_sys_truncate_args /* {
		syscallarg(char *) path;
		syscallarg(long) length;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return compat_43_sys_truncate(p, uap, retval);
}

int
openbsd_sys_mkfifo(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_mkfifo_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, path));
	return sys_mkfifo(p, uap, retval);
}

int
openbsd_sys_mkdir(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_mkdir_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_CREAT(p, &sg, SCARG(uap, path));
	return sys_mkdir(p, uap, retval);
}

int
openbsd_sys_rmdir(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_rmdir_args /* {
		syscallarg(char *) path;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_rmdir(p, uap, retval);
}

int
openbsd_sys_getfh(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_getfh_args /* {
		syscallarg(char *) fname;
		syscallarg(fhandle_t *) fhp;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, fname));
	return sys_getfh(p, uap, retval);
}

int
openbsd_sys_pathconf(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_pathconf_args /* {
		syscallarg(char *) path;
		syscallarg(int) name;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_pathconf(p, uap, retval);
}

int
openbsd_sys_truncate(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	struct openbsd_sys_truncate_args /* {
		syscallarg(char *) path;
		syscallarg(int) pad;
		syscallarg(off_t) length;
	} */ *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_truncate(p, uap, retval);
}

int
compat_43_openbsd_sys_lstat(struct proc *p, void *v, register_t *retval)
{
	struct compat_43_openbsd_sys_lstat_args *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return compat_43_sys_lstat(p, uap, retval);
}

int
openbsd_sys_ktrace(struct proc *p, void *v, register_t *retval)
{
	struct openbsd_sys_ktrace_args *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, fname));
	return sys_ktrace(p, uap, retval);
}

int
openbsd_sys_quotactl(struct proc *p, void *v, register_t *retval)
{
	struct openbsd_sys_quotactl_args *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_quotactl(p, uap, retval);
}

int
openbsd_sys_lchown(struct proc *p, void *v, register_t *retval)
{
	struct openbsd_sys_lchown_args *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_lchown(p, uap, retval);
}

int
openbsd_sys_statfs(struct proc *p, void *v, register_t *retval)
{
	struct openbsd_sys_statfs_args *uap = v;
	caddr_t sg = stackgap_init(p->p_emul);

	OPENBSD_CHECK_ALT_EXIST(p, &sg, SCARG(uap, path));
	return sys_statfs(p, uap, retval);
}
