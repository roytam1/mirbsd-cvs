/*	$OpenBSD: ttyname.c,v 1.12 2005/08/08 08:05:34 espie Exp $ */
/*
 * Copyright © 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <termios.h>
#include <db.h>
#include <string.h>
#include <unistd.h>
#include <paths.h>
#include <limits.h>
#include <errno.h>
#include "thread_private.h"

__RCSID("$MirOS$");

static char buf[TTY_NAME_MAX];
static int oldttyname(int, struct stat *, char *, size_t);
static int __ttyname_r_basic(int, char *, size_t);

int
ttyname_r(int fd, char *buf, size_t buflen)
{
	int ret;

	if ((ret = _FD_LOCK(fd, FD_READ, NULL)) == 0) {
		ret = __ttyname_r_basic(fd, buf, buflen);
		_FD_UNLOCK(fd, FD_READ);
	}
	return ret;
}

char *
ttyname(int fd)
{
	_THREAD_PRIVATE_KEY(ttyname);
	char * bufp = (char*) _THREAD_PRIVATE(ttyname, buf, NULL);
	int err;

	if (bufp == NULL) 
		return NULL;
	err = ttyname_r(fd, bufp, sizeof buf);
	if (err) {
		errno = err;
		return NULL;
	}
	else
	return bufp;
}

static int
__ttyname_r_basic(int fd, char *buf, size_t len)
{
	struct stat sb;
	struct termios ttyb;
	DB *db;
	DBT data, key;
	struct {
		mode_t type;
		dev_t dev;
	} bkey;

	/* Must be a terminal. */
	if (tcgetattr(fd, &ttyb) < 0)
		return (errno);
	/* Must be a character device. */
	if (fstat(fd, &sb))
		return (errno);
	if (!S_ISCHR(sb.st_mode))
		return (ENOTTY);
	if (len < sizeof(_PATH_DEV))
		return (ERANGE);

	memcpy(buf, _PATH_DEV, sizeof(_PATH_DEV));

	if ((db = dbopen(_PATH_DEVDB, O_RDONLY, 0, DB_HASH, NULL))) {
		memset(&bkey, 0, sizeof(bkey));
		bkey.type = S_IFCHR;
		bkey.dev = sb.st_rdev;
		key.data = &bkey;
		key.size = sizeof(bkey);
		if (!(db->get)(db, &key, &data, 0)) {
			if (data.size > len - (sizeof(_PATH_DEV) - 1)) {
				(void)(db->close)(db);
				return (ERANGE);
			}
			memcpy(buf + sizeof(_PATH_DEV) - 1, data.data,
			    data.size);
			(void)(db->close)(db);
			return (0);
		}
		(void)(db->close)(db);
	}
	return (oldttyname(fd, &sb, buf, len));
}

/* ARGSUSED */
static int
oldttyname(int fd __attribute__((__unused__)), struct stat *sb, char *buf,
    size_t len)
{
	struct dirent *dirp;
	DIR *dp;
	struct stat dsb;

	if ((dp = opendir(_PATH_DEV)) == NULL)
		return (errno);

	while ((dirp = readdir(dp))) {
		if (dirp->d_fileno != sb->st_ino)
			continue;
		if (dirp->d_namlen > len - sizeof(_PATH_DEV)) {
			(void)closedir(dp);
			return (ERANGE);
		}
		memcpy(buf + sizeof(_PATH_DEV) - 1, dirp->d_name,
		    dirp->d_namlen + 1);
		if (stat(buf, &dsb) || sb->st_dev != dsb.st_dev ||
		    sb->st_ino != dsb.st_ino)
			continue;
		(void)closedir(dp);
		return (0);
	}
	(void)closedir(dp);
	return (ENOTTY);
}
