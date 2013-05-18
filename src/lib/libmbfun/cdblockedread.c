/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
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
 * support routine for lseek+read to make 2048-byte aligned I/O
 */

#include <errno.h>
#include <mbfun.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

/* returns len if ok, 0 if ok but lseek to ofs+len failed, -1 otherwise */
ssize_t
cdblockedread(int fd, void *dst, size_t len, off_t ofs)
{
	off_t begsec, nlong;
	size_t begsecofs, n;
	ssize_t res;
	char *buf;

	begsec = ofs & ~2047;			/* start cdsector */
	nlong = (ofs + len + 2047) & ~2047;	/* end+1 cdsector */
	nlong -= begsec;			/* num. bytes to read */
	begsecofs = (size_t)(ofs & 2047);	/* start in sector */
	n = (size_t)nlong;
	if (nlong != (off_t)n) {
		errno = EINVAL;			/* truncation */
		return (-1);
	}
	if ((buf = malloc(n)) == NULL)
		return (-1);
	nlong = lseek(fd, begsec, SEEK_SET);
	if (nlong != begsec)
		goto err;
	if ((res = read(fd, buf, n)) == -1)
		goto err;
	if (n != (size_t)res) {
		errno = EIO;			/* short read */
		goto err;
	}
	memcpy(dst, buf + begsecofs, len);
	free(buf);
	/* correctly position seek pointer */
	ofs += len;
	nlong = lseek(fd, ofs, SEEK_SET);
	return (nlong == ofs ? (ssize_t)len : 0);

 err:
	free(buf);
	return (-1);
}
