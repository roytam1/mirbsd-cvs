/* $MirOS: src/lib/libz/gzfopen.c,v 1.4 2006/01/24 20:59:58 tg Exp $ */

/*-
 * Copyright (c) 2006, 2013
 *	Thorsten Glaser <tg@mirbsd.de>
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

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include "zutil.h"
#include "gzguts.h"

__RCSID("$MirOS: src/lib/libz/gzfopen.c,v 1.4 2006/01/24 20:59:58 tg Exp $");

static FILE *zf_open(const char *, const char *, int);
static int zf_read(void *, char *, int);
static int zf_write(void *, const char *, int);
static fpos_t zf_seek(void *, fpos_t, int);
static int zf_close(void *);

FILE *
gzfopen(const char *path, const char *mode)
{
	if (path == NULL) {
		errno = EINVAL;
		return (NULL);
	}

	return (zf_open(path, mode, -1));
}

FILE *
gzfdopen(int fd, const char *mode)
{
	return (zf_open(NULL, mode, fd));
}

FILE *
zf_open(const char *path, const char *mode, int fd)
{
	gzFile s;
	FILE *f;

	if (mode == NULL) {
		errno = EINVAL;
		return (NULL);
	}

	s = (path == NULL) ? gzdopen(fd, mode) : gzopen(path, mode);
	if (s == (gzFile)Z_NULL) {
		errno = ENXIO;
		return (NULL);
	}

	if ((f = funopen((void *)s,
	    ((gz_statep)s)->mode == GZ_READ ? zf_read : NULL,
	    ((gz_statep)s)->mode == GZ_READ ? NULL : zf_write,
	    zf_seek, zf_close)) == NULL) {
		int e = errno;

		gzclose(s);
		errno = e;
		return (NULL);
	}

	if (path == NULL)
		f->_file = fd;

	return (f);
}

static int
zf_read(void *s, char *buf, int len)
{
	int rv;

	rv = gzread((gzFile)s, buf, len);

	if (rv == Z_STREAM_ERROR) {
		errno = EBADF;
		return (-1);
	}

	if (rv == -1)
		if (((gz_statep)s)->err != Z_ERRNO)
			errno = EIO;

	return (rv);
}

static int
zf_write(void *s, const char *buf, int len)
{
	int rv;

	rv = gzwrite((gzFile)s, buf, len);

	if (rv == Z_STREAM_ERROR) {
		errno = EBADF;
		return (-1);
	}

	if (rv == -1)
		if (((gz_statep)s)->err != Z_ERRNO)
			errno = EIO;

	return (rv);
}

static fpos_t
zf_seek(void *s, fpos_t pos, int how)
{
	z_off_t rv;

	if (s == NULL) {
		errno = EBADF;
		return (-1);
	}

	if (how == SEEK_END) {
		errno = ESPIPE;
		return (-1);
	}

	rv = gzseek((gzFile)s, pos, how);
	if (rv == -1L)
		errno = EINVAL;

	return (rv);
}

static int
zf_close(void *s)
{
	int rv;

	rv = gzclose((gzFile)s);
	if (rv == Z_ERRNO) {
		return (-1);
	} else if (rv == Z_BUF_ERROR) {
		errno = EILSEQ;
		return (-1);
	} else if (rv == Z_STREAM_ERROR) {
		errno = EBADF;
		return (-1);
	} else if (rv == Z_OK) {
		return (0);
	}

	errno = ENOCOFFEE; /* unknown code */
	return (-1);
}
