/*-
 * Copyright (c) 2009
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
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/slibkern.h>
#include "libsa.h"
#include "dosfs.h"

__RCSID("$MirOS: src/sys/lib/libsa/lmbmfs.c,v 1.3 2009/08/11 13:40:07 tg Exp $");

extern uint32_t dosfs__stat(void);
extern uint32_t dosfs__open(void);
extern void dosfs__close(uint32_t);
extern uint32_t dosfs__read(uint32_t, void *, uint32_t);
extern int32_t dosfs__seek(uint32_t, uint32_t, int32_t);

struct dosfs_file {
	struct open_file *open_file;	/* our "parent" structure */
#define HANDLE_NOTOPEN	(0xFFFFU)
	uint16_t handle;		/* DOS file descriptor */
#define FLAG_ISDIR	16
	uint16_t flags;
};

int
dosfs_init(void)
{
	if ((i386_biosflags & 3) != 1)
		return (ENXIO);

	printf(" dosfs");
	return (0);
}


int
dosfs_open(char *path, struct open_file *f)
{
	struct dosfs_file *ff;
	unsigned int i;

//printf("D: dosfs_open(%s)", path);
	if ((i386_biosflags & 3) != 1)
//{ printf(" -> nyet\n");
		return (ENXIO);
//}

	twiddle();
	/* stat file or directory */
	strlcpy(bounce_buf, path, sizeof(bounce_buf));
	if ((i = dosfs__stat()) & 0x10000U)
//{ printf(" -> stat %x\n", i);
		/* generic error */
		return (ENOENT);
//}

	/* allocate fs specific data structure */
	ff = alloc(sizeof(struct dosfs_file));
	f->f_fsdata = ff;
	ff->open_file = f;
	ff->handle = HANDLE_NOTOPEN;
	if ((ff->flags = (i & 0xFFFFU)) & FLAG_ISDIR)
//{ printf(" -> isdir\n");
		return (0);
//}

	twiddle();
	/* open file */
	if ((i = dosfs__open()) & 0x10000U) {
//printf(" -> open %x\n", i);
		/* open error */
		free(ff, sizeof(struct dosfs_file));
		f->f_fsdata = NULL;
		return (EIO);
	}
	ff->handle = i & 0xFFFFU;
//printf(" -> ok\n");
	return (0);
}

int
dosfs_close(struct open_file *f)
{
	if (f) {
		struct dosfs_file *ff = f->f_fsdata;

		if (ff->handle != HANDLE_NOTOPEN)
			dosfs__close(ff->handle);
		free(ff, sizeof(struct dosfs_file));
		f->f_fsdata = NULL;
	}

	return (0);
}

int
dosfs_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct dosfs_file *ff = f->f_fsdata;
	uint32_t n;

	if (ff->handle == HANDLE_NOTOPEN)
		return (EISDIR);

	twiddle();
	n = dosfs__read(ff->handle, buf, size > 65280 ? 65280 : size);
	if (n == 0xFFFFU)
		return (EIO);
	if (resid)
		*resid = size - n;
	return (0);
}

int
dosfs_write(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return (EROFS);
}

off_t
dosfs_seek(struct open_file *f, off_t offset, int where)
{
	struct dosfs_file *ff = f->f_fsdata;
	uint32_t i;

	if (ff->handle == HANDLE_NOTOPEN)
		return (EISDIR);

	switch (where) {
	case SEEK_SET:
		i = 0;
		break;
	case SEEK_CUR:
		i = 1;
		break;
	case SEEK_END:
		i = 2;
		break;
	default:
		return (-1);
	}
	return ((off_t)dosfs__seek(ff->handle, i, (int32_t)offset));
}

int
dosfs_stat(struct open_file *f, struct stat *sb)
{
	struct dosfs_file *ff = f->f_fsdata;
	int32_t curofs;

	/* quick and dirty */
	bzero(sb, sizeof(struct stat));
	if (ff->flags & FLAG_ISDIR) {
		sb->st_mode = 040555;
		sb->st_size = 1;
	} else {
		sb->st_mode = 0444;
		curofs = dosfs__seek(ff->handle, 1, 0);
		sb->st_size = dosfs__seek(ff->handle, 2, 0);
		dosfs__seek(ff->handle, 0, curofs);
	}

	return (0);
}

int
dosfs_readdir(struct open_file *f, char *name)
{
	return (ENOSYS);
}
