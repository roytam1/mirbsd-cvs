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

#include <sys/statvfs.h>
#include <string.h>

__RCSID("$MirOS$");
__RCSID("$NetBSD: statvfs.c,v 1.3 2004/08/23 03:32:12 jlam Exp $");

static void fs2vfs(struct statvfs *vfs, const struct statfs *sfs);

static void
fs2vfs(struct statvfs *vfs, const struct statfs *sfs)
{
	vfs->f_flag = sfs->f_flags & ST_COPYALL;

	vfs->f_bsize = sfs->f_bsize;
	vfs->f_frsize = sfs->f_bsize;
	vfs->f_iosize = sfs->f_iosize;
	vfs->f_blocks = sfs->f_blocks;
	vfs->f_bfree = sfs->f_bfree;
	vfs->f_bavail = sfs->f_bavail;
	vfs->f_bresvd = 0;		/* XXX */

	vfs->f_files = sfs->f_files;
	vfs->f_ffree = sfs->f_ffree;
	vfs->f_favail = sfs->f_bavail;
	vfs->f_fresvd = 0;		/* XXX */

	vfs->f_syncreads = 0;		/* XXX */
	vfs->f_syncwrites = sfs->f_syncwrites;
	vfs->f_asyncreads = 0;		/* XXX */
	vfs->f_asyncwrites = sfs->f_asyncwrites;

	memcpy(&vfs->f_fsidx, &sfs->f_fsid, sizeof (fsid_t));
	vfs->f_fsid = sfs->f_fsid.val[0];

	vfs->f_namemax = MNAMELEN;
	vfs->f_owner = sfs->f_owner;
	strlcpy(vfs->f_fstypename, sfs->f_fstypename, _VFS_NAMELEN);
	strlcpy(vfs->f_mntonname, sfs->f_mntonname, _VFS_MNAMELEN);
	strlcpy(vfs->f_mntfromname, sfs->f_mntfromname, _VFS_MNAMELEN);
}

int
statvfs(const char *path, struct statvfs *vfs)
{
	struct statfs sfs;

	if (statfs(path, &sfs) == -1)
		return -1;
	fs2vfs(vfs, &sfs);
	return 0;
}

int
fstatvfs(int fd, struct statvfs *vfs)
{
	struct statfs sfs;

	if (fstatfs(fd, &sfs) == -1)
		return -1;

	fs2vfs(vfs, &sfs);
	return 0;
}
