/**	$MirOS: src/sys/sys/statvfs.h,v 1.2 2014/02/09 22:35:50 tg Exp $ */
/*	$NetBSD: statvfs.h,v 1.11 2006/07/31 16:34:44 martin Exp $	 */
/*	$NetBSD: statvfs.h,v 1.3 2004/08/23 03:32:13 jlam Exp $	*/

/*-
 * Copyright (c) 2004 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
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
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_SYS_STATVFS_H_
#define	_SYS_STATVFS_H_

#include <sys/param.h>
#include <sys/mount.h>

#define	_VFS_NAMELEN	32
#define	_VFS_MNAMELEN	1024

#ifndef	fsblkcnt_t
typedef	uint64_t	fsblkcnt_t;	/* fs block count (statvfs) */
#define	fsblkcnt_t	fsblkcnt_t
#endif

#ifndef	fsfilcnt_t
typedef	uint64_t	fsfilcnt_t;	/* fs file count */
#define	fsfilcnt_t	fsfilcnt_t
#endif

struct statvfs {
	unsigned long	f_flag;		/* copy of mount exported flags */
	unsigned long	f_bsize;	/* filesystem block size */
	unsigned long	f_frsize;	/* fundamental filesystem block size */
	unsigned long	f_iosize;	/* optimal filesystem block size */

	fsblkcnt_t	f_blocks;	/* number of blocks in filesystem, */
					/*   (in units of f_frsize) */
	fsblkcnt_t	f_bfree;	/* free blocks avail in filesystem */
	fsblkcnt_t	f_bavail;	/* free blocks avail to non-root */
	fsblkcnt_t	f_bresvd;	/* blocks reserved for root */

	fsfilcnt_t	f_files;	/* total file nodes in filesystem */
	fsfilcnt_t	f_ffree;	/* free file nodes in filesystem */
	fsfilcnt_t	f_favail;	/* free file nodes avail to non-root */
	fsfilcnt_t	f_fresvd;	/* file nodes reserved for root */

	uint64_t  	f_syncreads;	/* count of sync reads since mount */
	uint64_t  	f_syncwrites;	/* count of sync writes since mount */

	uint64_t  	f_asyncreads;	/* count of async reads since mount */
	uint64_t  	f_asyncwrites;	/* count of async writes since mount */

	fsid_t		f_fsidx;	/* NetBSD compatible fsid */
	unsigned long	f_fsid;		/* Posix compatible fsid */
	unsigned long	f_namemax;	/* maximum filename length */
	uid_t		f_owner;	/* user that mounted the filesystem */

	uint32_t	f_spare[4];	/* spare space */

	char	f_fstypename[_VFS_NAMELEN]; /* fs type name */
	char	f_mntonname[_VFS_MNAMELEN];  /* directory on which mounted */
	char	f_mntfromname[_VFS_MNAMELEN];  /* mounted filesystem */

};

#if __OPENBSD_VISIBLE
#define	VFS_NAMELEN	_VFS_NAMELEN
#define	VFS_MNAMELEN	_VFS_MNAMELEN
#endif

#define	ST_RDONLY	MNT_RDONLY
#define	ST_SYNCHRONOUS	MNT_SYNCHRONOUS
#define	ST_NOEXEC	MNT_NOEXEC
#define	ST_NOSUID	MNT_NOSUID
#define	ST_NODEV	MNT_NODEV
#define	ST_ASYNC	MNT_ASYNC
#define	ST_NOATIME	MNT_NOATIME
#define	ST_SOFTDEP	MNT_SOFTDEP

#define	ST_EXRDONLY	MNT_EXRDONLY
#define	ST_EXPORTED	MNT_EXPORTED
#define	ST_DEFEXPORTED	MNT_DEFEXPORTED
#define	ST_EXPORTANON	MNT_EXPORTANON
#define	ST_EXKERB	MNT_EXKERB

#define	ST_LOCAL	MNT_LOCAL
#define	ST_QUOTA	MNT_QUOTA
#define	ST_ROOTFS	MNT_ROOTFS

#define	ST_WAIT		MNT_WAIT
#define	ST_NOWAIT	MNT_NOWAIT

#ifdef __DBINTERFACE_PRIVATE
/* building libc */
#define ST_COPYALL	( \
	    ST_RDONLY | ST_SYNCHRONOUS | ST_NOEXEC | ST_NOSUID | ST_NODEV | \
	    ST_ASYNC | ST_NOATIME | ST_SOFTDEP | ST_EXRDONLY | ST_EXPORTED | \
	    ST_DEFEXPORTED | ST_EXPORTANON | ST_EXKERB | ST_LOCAL | \
	    ST_QUOTA | ST_ROOTFS | ST_WAIT | ST_NOWAIT \
	)
#endif

__BEGIN_DECLS
int	statvfs(const char *, struct statvfs *);
int	fstatvfs(int, struct statvfs *);
#ifdef notyet
int	getvfsstat(struct statvfs *, size_t, int);
int	getmntinfo(struct statvfs **, int);
#if __OPENBSD_VISIBLE
int	fhstatvfs(const void *, size_t, struct statvfs *);

int	statvfs1(const char *, struct statvfs *, int);
int	fstatvfs1(int, struct statvfs *, int);
int	fhstatvfs1(const void *, size_t, struct statvfs *, int);
#endif /* _NETBSD_SOURCE */
#endif /* notyet */
__END_DECLS

#endif /* !_SYS_STATVFS_H_ */
